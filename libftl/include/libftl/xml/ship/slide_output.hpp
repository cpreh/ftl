#ifndef LIBFTL_XML_SHIP_SLIDE_OUTPUT_HPP_INCLUDED
#define LIBFTL_XML_SHIP_SLIDE_OUTPUT_HPP_INCLUDED

#include <libftl/xml/ship/slide.hpp>
#include <libftl/xml/ship/slide_to_string.hpp>
#include <fcppt/enum/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::ship
{
template <typename Ch, typename Traits>
inline std::basic_ostream<Ch, Traits> &
operator<<(std::basic_ostream<Ch, Traits> &_stream, libftl::xml::ship::slide const _slide)
{
  return fcppt::enum_::output(_stream, _slide);
}
}

#endif
