#ifndef FTL_PARSE_XML_TYPE_HPP_INCLUDED
#define FTL_PARSE_XML_TYPE_HPP_INCLUDED

#include <ftl/parse/xml/type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
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
  ship
};

}
FCPPT_ENUM_DEFINE_MAX_VALUE(ftl::parse::xml::type::ship);

#endif
