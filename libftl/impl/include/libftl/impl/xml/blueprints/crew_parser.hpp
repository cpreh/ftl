#ifndef LIBFTL_IMPL_XML_BLUEPRINTS_CREW_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_BLUEPRINTS_CREW_PARSER_HPP_INCLUDED

#include <libftl/xml/blueprints/crew.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::blueprints
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::crew, libftl::impl::xml::node>>
crew_parser();
}

#endif
