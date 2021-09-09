#ifndef LIBFTL_XML_EVENTS_TOP_EVENT_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_TOP_EVENT_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/events/event_content.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/unique.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
using top_event = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::name, std::string>,
        fcppt::record::element<libftl::xml::labels::unique, fcppt::optional::object<bool>>>,
    libftl::xml::events::event_content>;
}

#endif
