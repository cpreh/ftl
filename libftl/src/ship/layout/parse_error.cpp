#include <libftl/ship/layout/parse_error.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/parse/parse_stream_error.hpp>
#include <fcppt/parse/parse_stream_error_output.hpp> // IWYU pragma: keep
#include <fcppt/variant/match.hpp>

fcppt::io::ostream &libftl::ship::layout::operator<<(fcppt::io::ostream &_stream, libftl::ship::layout::parse_error const &_parse_error)
{
  fcppt::variant::match(
      _parse_error.value_,
      [&_stream](libftl::ship::layout::parse_error::invalid_room_id const _id)
      { _stream << FCPPT_TEXT("Invalid room id ") << _id << FCPPT_TEXT('.'); },
      [&_stream](libftl::ship::layout::parse_error::invalid_bool const _b)
      { _stream << FCPPT_TEXT("Invalid bool ") << _b << FCPPT_TEXT('.'); },
      [&_stream](fcppt::parse::parse_stream_error<char> const &_error)
      { _stream << fcppt::from_std_string(fcppt::output_to_std_string(_error)); });
  return _stream;
}
