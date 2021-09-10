#ifndef LIBFTL_XML_EVENTS_RESULT_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_RESULT_HPP_INCLUDED

#include <libftl/xml/events/event_list.hpp>
#include <libftl/xml/events/text_list.hpp>
#include <libftl/xml/events/top_event.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
using result = fcppt::tuple::object<
    std::vector<libftl::xml::events::top_event>,
    std::vector<libftl::xml::events::event_list>,
    std::vector<libftl::xml::events::text_list>>;
}

#endif
