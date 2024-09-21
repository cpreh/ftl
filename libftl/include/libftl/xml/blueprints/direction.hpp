#ifndef LIBFTL_XML_BLUEPRINTS_DIRECTION_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_DIRECTION_HPP_INCLUDED

#include <fcppt/enum/define_max_value.hpp>
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
  down
};
}
FCPPT_ENUM_DEFINE_MAX_VALUE(libftl::xml::blueprints::direction::down);

#endif
