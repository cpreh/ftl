#ifndef LIBFTL_IMPL_XML_EVENTS_EVENT_CONTENT_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_EVENTS_EVENT_CONTENT_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/xml/events/event_content.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/optional/object.hpp>

namespace libftl::impl::xml::events
{
[[nodiscard]] fcppt::unique_ptr<libftl::impl::xml::typed::base<
    libftl::xml::events::event_content,
    fcppt::optional::object<libftl::impl::xml::inner_node>>>
event_content_parser();
}

#endif
