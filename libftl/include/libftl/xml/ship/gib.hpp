#ifndef LIBFTL_XML_SHIP_GIB_HPP_INCLUDED
#define LIBFTL_XML_SHIP_GIB_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/angular.hpp>
#include <libftl/xml/labels/direction.hpp>
#include <libftl/xml/labels/glow_offset.hpp>
#include <libftl/xml/labels/max.hpp>
#include <libftl/xml/labels/min.hpp>
#include <libftl/xml/labels/velocity.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>

namespace libftl::xml::ship
{
using gib = libftl::xml::node<
    fcppt::record::object<>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::velocity,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::min, float>,
                    fcppt::record::element<libftl::xml::labels::max, float>>,
                fcppt::unit>>,
        fcppt::record::element<
            libftl::xml::labels::direction,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::min, int>,
                    fcppt::record::element<libftl::xml::labels::max, int>>,
                fcppt::unit>>,
        fcppt::record::element<
            libftl::xml::labels::angular,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::min, float>,
                    fcppt::record::element<libftl::xml::labels::max, float>>,
                fcppt::unit>>,
        fcppt::record::element<
            libftl::xml::labels::glow_offset,
            fcppt::optional::object<libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::x, int>,
                    fcppt::record::element<libftl::xml::labels::y, int>>,
                fcppt::unit>>>,
        fcppt::record::
            element<libftl::xml::labels::x, libftl::xml::node<fcppt::record::object<>, int>>,
        fcppt::record::
            element<libftl::xml::labels::y, libftl::xml::node<fcppt::record::object<>, int>>>>;
}

#endif
