#ifndef LIBFTL_XML_EVENTS_TEXT_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_TEXT_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/load.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
using text = fcppt::variant::object<
    libftl::xml::node<
        fcppt::record::object<fcppt::record::element<libftl::xml::labels::load, std::string>>,
        fcppt::unit>,
    libftl::xml::node<fcppt::record::object<>, std::string>>;
}

#endif
