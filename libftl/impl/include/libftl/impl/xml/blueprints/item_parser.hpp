#ifndef LIBFTL_IMPL_XML_BLUEPRINTS_ITEM_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_BLUEPRINTS_ITEM_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/xml/blueprints/item.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::blueprints
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::item, libftl::impl::xml::node>>
item_parser();
}

#endif
