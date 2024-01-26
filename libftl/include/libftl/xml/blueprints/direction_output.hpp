#ifndef LIBFTL_XML_BLUEPRINTS_DIRECTION_OUTPUT_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_DIRECTION_OUTPUT_HPP_INCLUDED

#include <libftl/xml/blueprints/direction.hpp>
#include <libftl/xml/blueprints/direction_to_string.hpp> // IWYU pragma: keep
#include <fcppt/enum/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
template <typename Ch, typename Traits>
inline std::basic_ostream<Ch, Traits> &
operator<<(std::basic_ostream<Ch, Traits> &_stream, libftl::xml::blueprints::direction const _direction)
{
  return fcppt::enum_::output(_stream, _direction);
}
}

#endif
