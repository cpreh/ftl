#ifndef LIBFTL_XML_SHIP_OFFSET_HPP_INCLUDED
#define LIBFTL_XML_SHIP_OFFSET_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>

namespace libftl::xml::ship
{
using offset = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::x, int>,
        fcppt::record::element<libftl::xml::labels::y, int>>,
    fcppt::unit>;
}

#endif
