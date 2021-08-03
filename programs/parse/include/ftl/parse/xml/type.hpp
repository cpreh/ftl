#ifndef FTL_PARSE_XML_TYPE_HPP_INCLUDED
#define FTL_PARSE_XML_TYPE_HPP_INCLUDED

#include <ftl/parse/xml/type_fwd.hpp>

namespace ftl
{
namespace parse
{
namespace xml
{
enum class type
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
}
}

#endif
