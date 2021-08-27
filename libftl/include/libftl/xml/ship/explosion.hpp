#ifndef LIBFTL_XML_SHIP_EXPLOSION_HPP_INCLUDED
#define LIBFTL_XML_SHIP_EXPLOSION_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/gib1.hpp>
#include <libftl/xml/labels/gib2.hpp>
#include <libftl/xml/labels/gib3.hpp>
#include <libftl/xml/labels/gib4.hpp>
#include <libftl/xml/labels/gib5.hpp>
#include <libftl/xml/labels/gib6.hpp>
#include <libftl/xml/ship/gib.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>

namespace libftl::xml::ship
{
using explosion = libftl::xml::node<
    fcppt::record::object<>,
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::gib1, libftl::xml::ship::gib>,
        fcppt::record::element<libftl::xml::labels::gib2, libftl::xml::ship::gib>,
        fcppt::record::element<libftl::xml::labels::gib3, libftl::xml::ship::gib>,
        fcppt::record::element<libftl::xml::labels::gib4, libftl::xml::ship::gib>,
        fcppt::record::
            element<libftl::xml::labels::gib5, fcppt::optional::object<libftl::xml::ship::gib>>,
        fcppt::record::
            element<libftl::xml::labels::gib6, fcppt::optional::object<libftl::xml::ship::gib>>>>;
}

#endif
