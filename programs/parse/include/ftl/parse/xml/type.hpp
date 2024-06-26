#ifndef FTL_PARSE_XML_TYPE_HPP_INCLUDED
#define FTL_PARSE_XML_TYPE_HPP_INCLUDED

#include <ftl/parse/xml/type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace ftl::parse::xml
{
enum class type : std::uint8_t
{
  achievements,
  animations,
  blueprints,
  events,
  sectors,
  ship,
  fcppt_maximum = ship
};

}

#endif
