#ifndef LIBFTL_IMPL_XML_BLUEPRINTS_AUG_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_BLUEPRINTS_AUG_PARSER_HPP_INCLUDED

#include <libftl/xml/blueprints/aug.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::blueprints
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::aug, libftl::impl::xml::node>>
aug_parser();
}

#endif
