#ifndef LIBFTL_IMPL_XML_EVENTS_TOP_EVENT_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_EVENTS_TOP_EVENT_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/xml/events/top_event.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::events
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::events::top_event, libftl::impl::xml::node>>
top_event_parser();
}

#endif
