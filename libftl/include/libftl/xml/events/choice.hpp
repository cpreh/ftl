#ifndef LIBFTL_XML_EVENTS_CHOICE_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_CHOICE_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/events/event.hpp>
#include <libftl/xml/labels/event.hpp>
#include <libftl/xml/labels/hidden.hpp>
#include <libftl/xml/labels/lvl.hpp>
#include <libftl/xml/labels/req.hpp>
#include <libftl/xml/labels/text.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
using choice = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::hidden, fcppt::optional::object<bool>>,
        fcppt::record::element<libftl::xml::labels::req, fcppt::optional::object<std::string>>,
        fcppt::record::element<libftl::xml::labels::lvl, fcppt::optional::object<unsigned>>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::text,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<libftl::xml::labels::event, libftl::xml::events::event>>>;
}

#endif
