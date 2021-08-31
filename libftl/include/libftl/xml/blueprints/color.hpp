#ifndef LIBFTL_XML_BLUEPRINTS_COLOR_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_COLOR_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/a.hpp>
#include <libftl/xml/labels/b.hpp>
#include <libftl/xml/labels/g.hpp>
#include <libftl/xml/labels/r.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using color = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::r, std::uint8_t>,
        fcppt::record::element<libftl::xml::labels::g, std::uint8_t>,
        fcppt::record::element<libftl::xml::labels::b, std::uint8_t>,
        fcppt::record::element<libftl::xml::labels::a, double>>,
    fcppt::unit>;
}

#endif
