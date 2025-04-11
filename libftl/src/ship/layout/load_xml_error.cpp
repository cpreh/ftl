#include <libftl/archive/open_path_error.hpp>
#include <libftl/ship/layout/load_xml_error.hpp>
#include <libftl/xml/error.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/match.hpp>

fcppt::io::ostream &libftl::ship::layout::operator<<(
    fcppt::io::ostream &_stream, libftl::ship::layout::load_xml_error const &_xml_error)
{
  fcppt::variant::match(
      _xml_error.value_,
      [&_stream](libftl::archive::open_path_error const &_error) { _stream << _error; },
      [&_stream](libftl::xml::error const &_error) { _stream << _error; });
  return _stream;
}
