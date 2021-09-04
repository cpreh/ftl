#ifndef LIBFTL_XML_EVENTS_BOARDERS_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_BOARDERS_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/class.hpp>
#include <libftl/xml/labels/max.hpp>
#include <libftl/xml/labels/min.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
using boarders = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::min, unsigned>,
        fcppt::record::element<libftl::xml::labels::max, unsigned>,
        fcppt::record::element<libftl::xml::labels::class_, std::string>>,
    fcppt::unit>;
}
#endif
