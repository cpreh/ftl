#ifndef LIBFTL_XML_SHIP_OFFSETS_HPP_INCLUDED
#define LIBFTL_XML_SHIP_OFFSETS_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/cloak.hpp>
#include <libftl/xml/labels/floor.hpp>
#include <libftl/xml/ship/offset.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>

namespace libftl::xml::ship
{
using offsets = libftl::xml::node<
    fcppt::record::object<>,
    fcppt::record::object<
        fcppt::record::
            element<libftl::xml::labels::cloak, fcppt::optional::object<libftl::xml::ship::offset>>,
        fcppt::record::element<
            libftl::xml::labels::floor,
            fcppt::optional::object<libftl::xml::ship::offset>>>>;
}

#endif
