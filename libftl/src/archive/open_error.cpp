#include <libftl/archive/index_error.hpp>
#include <libftl/archive/open_error.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

fcppt::io::ostream &libftl::archive::operator<<(
    fcppt::io::ostream &_stream, libftl::archive::open_error const &_open_error)
{
  std::filesystem::path const &path{_open_error.path_};

  fcppt::variant::match(
      _open_error.value_,
      [&_stream, &path](libftl::archive::open_error::failed_to_open)
      {
        _stream << FCPPT_TEXT("Failed to open ") << fcppt::filesystem::path_to_string(path)
                << FCPPT_TEXT('.');
      },
      [&_stream, &path](libftl::archive::index_error const &_error)
      {
        _stream << FCPPT_TEXT("Failed to read index of ") << fcppt::filesystem::path_to_string(path)
                << FCPPT_TEXT(": ") << _error;
      });

  return _stream;
}
