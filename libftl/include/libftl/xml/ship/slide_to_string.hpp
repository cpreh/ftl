#ifndef LIBFTL_XML_SHIP_SLIDE_TO_STRING_HPP_INCLUDED
#define LIBFTL_XML_SHIP_SLIDE_TO_STRING_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/ship/slide.hpp>
#include <fcppt/enum/to_string_impl_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

namespace fcppt::enum_
{
template <>
struct to_string_impl<libftl::xml::ship::slide>
{
  LIBFTL_DETAIL_SYMBOL
  static std::string_view get(libftl::xml::ship::slide);
};

}

#endif
