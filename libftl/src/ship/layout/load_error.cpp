#include <libftl/archive/open_path_error.hpp>
#include <libftl/ship/layout/load_error.hpp>
#include <libftl/ship/layout/parse_error.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/match.hpp>

fcppt::io::ostream &libftl::ship::layout::operator<<(fcppt::io::ostream &_stream, libftl::ship::layout::load_error const &_load_error)
{
  fcppt::variant::match(
      _load_error.value_,
      [&_stream](libftl::ship::layout::parse_error const &_error) { _stream << _error; },
      [&_stream](libftl::archive::open_path_error const &_error) { _stream << _error; });

  return _stream;
}
