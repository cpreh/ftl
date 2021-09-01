#ifndef LIBFTL_IMPL_XML_BLUEPRINTS_SHIP_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_BLUEPRINTS_SHIP_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::blueprints
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::ship, libftl::impl::xml::node>>
ship_parser();
}

#endif
