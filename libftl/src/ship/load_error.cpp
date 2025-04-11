#include <libftl/ship/load_error.hpp>
#include <libftl/ship/images/error.hpp>
#include <libftl/ship/layout/load_error.hpp>
#include <libftl/ship/layout/load_xml_error.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/match.hpp>

fcppt::io::ostream &
libftl::ship::operator<<(fcppt::io::ostream &_stream, libftl::ship::load_error const &_load_error)
{
  _stream << FCPPT_TEXT("Failed to load ship ") << fcppt::from_std_string(_load_error.name_)
          << FCPPT_TEXT(": ");

  fcppt::variant::match(
    _load_error.value_,
    [&_stream](libftl::ship::load_error::not_found)
    {
      _stream << FCPPT_TEXT("It was not found!");
    },
    [&_stream](libftl::ship::layout::load_xml_error const &_error)
    {
      _stream << _error;
    },
    [&_stream](libftl::ship::layout::load_error const &_error)
    {
      _stream << _error;
    },
    [&_stream](libftl::ship::images::error const &_error)
    {
      _stream << _error;
    });

  return _stream;
}
