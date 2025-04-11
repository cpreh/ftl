#include <libftl/archive/open_path_error.hpp>
#include <libftl/archive/path.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::archive::open_path_error::chain::chain(open_path_error &&_error1, open_path_error &&_error2)
    : error1_{std::move(_error1)}, error2_{std::move(_error2)}
{
}

fcppt::io::ostream &libftl::archive::operator<<(
    fcppt::io::ostream &_stream, libftl::archive::open_path_error const &_open_error)
{
  fcppt::variant::match(
      _open_error.value_,
      [&_stream](libftl::archive::open_path_error::failed_to_open const &_error)
      {
        _stream << FCPPT_TEXT("Unable to open ") << fcppt::filesystem::path_to_string(_error.get());
      },
      [&_stream](libftl::archive::open_path_error::missing_path const &_error)
      {
        _stream << FCPPT_TEXT("Missing path ") << fcppt::from_std_string(_error.archive_path_.rep())
                << FCPPT_TEXT(" in ") << fcppt::filesystem::path_to_string(_error.file_path_);
      },
      [&_stream](libftl::archive::open_path_error::read_error const &_error)
      {
        _stream << FCPPT_TEXT("Failed to read ")
                << fcppt::from_std_string(_error.archive_path_.rep()) << FCPPT_TEXT(" in ")
                << fcppt::filesystem::path_to_string(_error.file_path_);
      },
      [&_stream](libftl::archive::open_path_error::chain const &_error)
      { _stream << _error.error1_.get() << FCPPT_TEXT('\n') << _error.error2_.get(); });

  return _stream;
}
