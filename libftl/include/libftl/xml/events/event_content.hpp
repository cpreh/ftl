#ifndef LIBFTL_XML_EVENTS_EVENT_CONTENT_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_EVENT_CONTENT_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/events/choice.hpp>
#include <libftl/xml/events/text.hpp>
#include <libftl/xml/labels/choice_list.hpp>
#include <libftl/xml/labels/store.hpp>
#include <libftl/xml/labels/text.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
using event_content = fcppt::record::object<
    fcppt::record::element<libftl::xml::labels::text, libftl::xml::events::text>,
    fcppt::record::element<
        libftl::xml::labels::choice_list,
        fcppt::optional::object<std::vector<libftl::xml::events::choice>>>,
    fcppt::record::element<
        libftl::xml::labels::store,
        fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, fcppt::unit>>>>;
}

#endif
