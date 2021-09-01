#ifndef LIBFTL_XML_BLUEPRINTS_DIRECTION_TO_STRING_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_DIRECTION_TO_STRING_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/blueprints/direction.hpp>
#include <fcppt/enum/to_string_impl_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

namespace fcppt::enum_
{
template <>
struct to_string_impl<libftl::xml::blueprints::direction>
{
  LIBFTL_DETAIL_SYMBOL
  static std::string_view get(libftl::xml::blueprints::direction);
};

}

#endif
