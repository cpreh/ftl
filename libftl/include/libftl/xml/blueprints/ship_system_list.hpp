#ifndef LIBFTL_XML_BLUEPRINTS_SHIP_SYSTEM_LIST_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_SHIP_SYSTEM_LIST_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/blueprints/system_element.hpp>
#include <libftl/xml/labels/battery.hpp>
#include <libftl/xml/labels/cloaking.hpp>
#include <libftl/xml/labels/clonebay.hpp>
#include <libftl/xml/labels/doors.hpp>
#include <libftl/xml/labels/drones.hpp>
#include <libftl/xml/labels/engines.hpp>
#include <libftl/xml/labels/hacking.hpp>
#include <libftl/xml/labels/medbay.hpp>
#include <libftl/xml/labels/mind.hpp>
#include <libftl/xml/labels/oxygen.hpp>
#include <libftl/xml/labels/pilot.hpp>
#include <libftl/xml/labels/sensors.hpp>
#include <libftl/xml/labels/shields.hpp>
#include <libftl/xml/labels/teleporter.hpp>
#include <libftl/xml/labels/weapons.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>

namespace libftl::xml::blueprints
{
using ship_system_list = libftl::xml::node<
    fcppt::record::object<>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::pilot,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::doors,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::sensors,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::medbay,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::oxygen,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::shields,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::engines,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::weapons,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::drones,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::teleporter,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::cloaking,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::clonebay,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::battery,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::mind,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>,
        fcppt::record::element<
            libftl::xml::labels::hacking,
            fcppt::optional::object<libftl::xml::blueprints::system_element>>>>;
}

#endif
