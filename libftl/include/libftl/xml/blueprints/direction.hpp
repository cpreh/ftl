#ifndef LIBFTL_XML_BLUEPRINTS_DIRECTION_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_DIRECTION_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
enum class direction : std::uint8_t
{
  left,
  right,
  up,
  down,
  fcppt_maximum = down
};
}
#endif
