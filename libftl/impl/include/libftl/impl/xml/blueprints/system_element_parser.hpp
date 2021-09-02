#ifndef LIBFTL_IMPL_XML_BLUEPRINTS_SYSTEM_ELEMENT_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_BLUEPRINTS_SYSTEM_ELEMENT_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/xml/blueprints/system_element.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::blueprints
{
[[nodiscard]] fcppt::unique_ptr<libftl::impl::xml::typed::base<
    libftl::xml::blueprints::system_element,
    std::vector<fcppt::reference<libftl::impl::xml::node const>>>>
system_element_parser(std::string &&);
}

#endif
