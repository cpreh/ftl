#include <libftl/xml/error.hpp>
#include <libftl/xml/type_error.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/parse/parse_stream_error.hpp>
#include <fcppt/parse/parse_stream_error_output.hpp> // IWYU pragma: keep
#include <fcppt/variant/match.hpp>

fcppt::io::ostream &
libftl::xml::operator<<(fcppt::io::ostream &_stream, libftl::xml::error const &_xml_error)
{
  fcppt::variant::match(
      _xml_error.value_,
      [&_stream](fcppt::parse::parse_stream_error<char> const &_error)
      { _stream << fcppt::from_std_string(fcppt::output_to_std_string(_error)); },
      [&_stream](libftl::xml::type_error const &_error) { _stream << _error; });
  return _stream;
}
