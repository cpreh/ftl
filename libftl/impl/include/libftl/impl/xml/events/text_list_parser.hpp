#ifndef LIBFTL_IMPL_XML_EVENTS_TEXT_LIST_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_EVENTS_TEXT_LIST_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/typed/named_node_base.hpp>
#include <libftl/xml/events/text_list.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::events
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::named_node_base<libftl::xml::events::text_list>>
text_list_parser();
}

#endif
