#ifndef LIBFTL_XML_EVENTS_EVENT_LIST_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_EVENT_LIST_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/events/event.hpp>
#include <libftl/xml/labels/name.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
using event_list = libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::name, std::string>>,
    std::vector<libftl::xml::events::event>>;
}

#endif
