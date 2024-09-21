#ifndef LIBFTL_XML_SHIP_SLIDE_HPP_INCLUDED
#define LIBFTL_XML_SHIP_SLIDE_HPP_INCLUDED

#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::ship
{
enum class slide : std::uint8_t
{
  left,
  right,
  up,
  down,
  no
};
}
FCPPT_ENUM_DEFINE_MAX_VALUE(libftl::xml::ship::slide::no);

#endif
