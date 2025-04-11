#include <libftl/archive/open_path_error.hpp>
#include <libftl/blueprints/error.hpp>
#include <libftl/xml/error.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/match.hpp>


fcppt::io::ostream &
libftl::blueprints::operator<<(fcppt::io::ostream &_stream, libftl::blueprints::error const &_bp_error)
{
  _stream << FCPPT_TEXT("In file " ) << fcppt::from_std_string(_bp_error.file_) << FCPPT_TEXT(": ");

  fcppt::variant::match(
      _bp_error.value_,
      [&_stream](libftl::archive::open_path_error const &_error) { _stream << _error; },
      [&_stream](libftl::xml::error const &_error) { _stream << _error; });

  return _stream;
}
