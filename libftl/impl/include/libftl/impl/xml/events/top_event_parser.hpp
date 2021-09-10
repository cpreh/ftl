#ifndef LIBFTL_IMPL_XML_EVENTS_TOP_EVENT_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_EVENTS_TOP_EVENT_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/typed/named_node_base.hpp>
#include <libftl/xml/events/top_event.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::events
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::named_node_base<libftl::xml::events::top_event>>
top_event_parser();
}

#endif
