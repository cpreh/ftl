#ifndef LIBFTL_XML_BLUEPRINTS_COLOR_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_COLOR_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/blueprints/color_channel.hpp>
#include <libftl/xml/labels/a.hpp>
#include <libftl/xml/labels/b.hpp>
#include <libftl/xml/labels/g.hpp>
#include <libftl/xml/labels/r.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>

namespace libftl::xml::blueprints
{
using color = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::r, libftl::xml::blueprints::color_channel>,
        fcppt::record::element<libftl::xml::labels::g, libftl::xml::blueprints::color_channel>,
        fcppt::record::element<libftl::xml::labels::b, libftl::xml::blueprints::color_channel>,
        fcppt::record::element<libftl::xml::labels::a, double>>,
    fcppt::unit>;
}

#endif
