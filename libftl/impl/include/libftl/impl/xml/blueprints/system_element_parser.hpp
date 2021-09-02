#ifndef LIBFTL_IMPL_XML_BLUEPRINTS_SYSTEM_ELEMENT_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_BLUEPRINTS_SYSTEM_ELEMENT_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/typed/node_member_base.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/blueprints/system_element.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::blueprints
{
[[nodiscard]] fcppt::unique_ptr<libftl::impl::xml::typed::node_member_base<
    libftl::impl::xml::typed::required::no,
    libftl::xml::blueprints::system_element>>
system_element_parser(std::string &&);
}

#endif
