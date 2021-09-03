#ifndef LIBFTL_IMPL_XML_ANIMATIONS_ANIM_SHEET_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_ANIMATIONS_ANIM_SHEET_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/xml/animations/anim_sheet.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::animations
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::animations::anim_sheet, libftl::impl::xml::node>>
anim_sheet_parser();
}

#endif
