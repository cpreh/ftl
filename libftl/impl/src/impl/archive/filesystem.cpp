#include <libftl/archive/base.hpp>
#include <libftl/archive/open_path_error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/impl/archive/filesystem.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iosfwd>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::impl::archive::filesystem::filesystem(std::filesystem::path &&_path)
    : libftl::archive::base{}, directory_{std::move(_path)}
{
}

libftl::impl::archive::filesystem::~filesystem() = default;

fcppt::either::object<libftl::archive::open_path_error, fcppt::unique_ptr<std::istream>>
libftl::impl::archive::filesystem::open(libftl::archive::path const &_path) const
{
  std::filesystem::path const full_path{
      std::filesystem::path{this->directory_} /
      _path.rep() // NOLINT(fuchsia-default-arguments-calls)
  };

  return fcppt::either::map(
      fcppt::either::from_optional(
          fcppt::filesystem::open<std::ifstream>(full_path, std::ios_base::binary),
          [&full_path]
          {
            return libftl::archive::open_path_error{libftl::archive::open_path_error::variant{
                libftl::archive::open_path_error::failed_to_open{full_path}}};
          }),
      [](std::ifstream &&_stream)
      {
        return fcppt::unique_ptr_to_base<std::istream>(
            fcppt::make_unique_ptr<std::ifstream>(std::move(_stream)));
      });
}
