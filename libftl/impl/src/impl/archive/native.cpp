#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/entry.hpp>
#include <libftl/archive/extract.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/archive/index.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/impl/archive/native.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <istream>
#include <sstream>
#include <streambuf>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{
class io_buf : public std::streambuf
{
  FCPPT_NONMOVABLE(io_buf);

public:
  explicit io_buf(fcppt::io::buffer &&_buffer) : std::streambuf{}, buffer_{std::move(_buffer)}
  {
    this->set_pos_impl(0);
  }

  ~io_buf() override = default;

private:
  void set_pos_impl(pos_type const _pos)
  {
    this->setg(this->buffer_.data(), this->buffer_.data() + _pos, this->buffer_.data_end());
  }

  [[nodiscard]] pos_type set_pos(pos_type const _pos)
  {
    if (_pos < 0 || _pos > (this->egptr() - this->eback()))
    {
      return pos_type{-1};
    }

    this->set_pos_impl(_pos);

    return _pos;
  }

  static void check_mode(std::ios_base::openmode const _mode)
  {
    if ((_mode & std::ios_base::out) != 0)
    {
      throw fcppt::exception{FCPPT_TEXT("ios_base::out specified in seekoff of readonly stream")};
    }

    if ((_mode & std::ios_base::in) == 0)
    {
      throw fcppt::exception{FCPPT_TEXT("ios_base::in missing in seekoff of readonly stream")};
    }
  }

  [[nodiscard]] pos_type seekoff(
      off_type const _off,
      std::ios_base::seekdir const _dir,
      std::ios_base::openmode const _mode) override
  {
    check_mode(_mode);

    return this->set_pos(
        [this, _off, _dir]() -> pos_type
        {
          FCPPT_PP_PUSH_WARNING
          FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch)
          switch (_dir)
          {
          case std::ios_base::beg:
            return _off;
          case std::ios_base::cur:
            return (this->gptr() - this->eback()) + _off;
          case std::ios_base::end:
            return (this->egptr() - this->eback()) + _off;
          }
          FCPPT_PP_POP_WARNING

          throw fcppt::exception{FCPPT_TEXT("Invalid ios_base::seekdir")};
        }());
  }

  [[nodiscard]] pos_type seekpos(pos_type const _pos, std::ios_base::openmode const _mode) override
  {
    check_mode(_mode);

    return this->set_pos(_pos);
  }

  fcppt::io::buffer buffer_;
};

// NOLINTNEXTLINE(fuchsia-multiple-inheritance)
class io_istream : public std::istream
{
  FCPPT_NONMOVABLE(io_istream);

public:
  explicit io_istream(fcppt::io::buffer &&_buffer) : std::istream{&buf_}, buf_{std::move(_buffer)}
  {
  }

  ~io_istream() override = default;

private:
  io_buf buf_;
};

}

libftl::impl::archive::native::native(
    std::filesystem::path &&_file_path, libftl::archive::index &&_index)
    : libftl::archive::base{}, file_path_{std::move(_file_path)}, index_{std::move(_index)}
{
}

libftl::impl::archive::native::~native() = default;

fcppt::either::object<libftl::error, fcppt::unique_ptr<std::istream>>
libftl::impl::archive::native::open(libftl::archive::path const &_path) const
{
  return fcppt::either::bind(
      fcppt::either::from_optional(
          fcppt::filesystem::open<std::ifstream>(this->file_path_, std::ios_base::binary),
          [this]
          {
            return libftl::error{
                FCPPT_TEXT("Unable to open ") +
                fcppt::filesystem::path_to_string(this->file_path_)};
          }),
      [&_path, this](std::ifstream &&_stream)
      {
        return fcppt::either::bind(
            fcppt::either::from_optional(
                fcppt::container::find_opt_mapped(this->index_, _path.rep()),
                [&_path, this]
                {
                  return libftl::error{
                      FCPPT_TEXT("Missing path ") + fcppt::from_std_string(_path.rep()) +
                      FCPPT_TEXT(" in ") + fcppt::filesystem::path_to_string(this->file_path_)};
                }),
            [&_path, this, &_stream](fcppt::reference<libftl::archive::entry const> const _entry)
            {
              return fcppt::either::map(
                  fcppt::either::from_optional(
                      libftl::archive::extract(libftl::archive::file{
                          fcppt::reference_to_base<std::istream>(fcppt::make_ref(_stream)),
                          _entry.get()}),
                      [&_path, this]
                      {
                        return libftl::error{
                            FCPPT_TEXT("Failed to read ") + fcppt::from_std_string(_path.rep()) +
                            FCPPT_TEXT(" in ") +
                            fcppt::filesystem::path_to_string(this->file_path_)};
                      }),
                  [](fcppt::io::buffer &&_buffer)
                  {
                    return fcppt::unique_ptr_to_base<std::istream>(
                        fcppt::make_unique_ptr<io_istream>(std::move(_buffer)));
                  });
            });
      });
}
