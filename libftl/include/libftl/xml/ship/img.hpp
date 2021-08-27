#ifndef LIBFTL_XML_SHIP_IMG_HPP_INCLUDED
#define LIBFTL_XML_SHIP_IMG_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/h.hpp>
#include <libftl/xml/labels/w.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>

namespace libftl::xml::ship
{
using img = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::x, int>,
        fcppt::record::element<libftl::xml::labels::y, int>,
        fcppt::record::element<libftl::xml::labels::w, unsigned>,
        fcppt::record::element<libftl::xml::labels::h, unsigned>>,
    fcppt::unit>;
}

#endif
