#ifndef LIBFTL_IMPL_XML_EVENTS_TEXT_LIST_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_EVENTS_TEXT_LIST_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/xml/events/text_list.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::events
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::events::text_list, libftl::impl::xml::node>>
text_list_parser();
}

#endif
