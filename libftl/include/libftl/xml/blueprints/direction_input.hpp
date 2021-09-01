#ifndef LIBFTL_XML_BLUEPRINTS_DIRECTION_INPUT_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_DIRECTION_INPUT_HPP_INCLUDED

#include <libftl/xml/blueprints/direction.hpp>
#include <libftl/xml/blueprints/direction_to_string.hpp>
#include <fcppt/enum/input.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
template <typename Ch, typename Traits>
inline std::basic_istream<Ch, Traits> &
operator>>(std::basic_istream<Ch, Traits> &_stream, libftl::xml::blueprints::direction &_direction)
{
  return fcppt::enum_::input(_stream, _direction);
}
}

#endif
