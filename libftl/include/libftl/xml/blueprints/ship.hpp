#ifndef LIBFTL_XML_BLUEPRINTS_SHIP_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_SHIP_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/blueprints/ship_system_list.hpp>
#include <libftl/xml/labels/amount.hpp>
#include <libftl/xml/labels/boarding_ai.hpp>
#include <libftl/xml/labels/class.hpp>
#include <libftl/xml/labels/cloak_image.hpp>
#include <libftl/xml/labels/count.hpp>
#include <libftl/xml/labels/drone_list.hpp>
#include <libftl/xml/labels/drone_slots.hpp>
#include <libftl/xml/labels/drones.hpp>
#include <libftl/xml/labels/health.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/layout.hpp>
#include <libftl/xml/labels/max_power.hpp>
#include <libftl/xml/labels/missiles.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/shield_image.hpp>
#include <libftl/xml/labels/system_list.hpp>
#include <libftl/xml/labels/weapon_list.hpp>
#include <libftl/xml/labels/weapon_slots.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using ship = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::name, std::string>,
        fcppt::record::element<libftl::xml::labels::layout, std::string>,
        fcppt::record::element<libftl::xml::labels::img, std::string>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::class_,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::name,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::system_list,
            libftl::xml::blueprints::ship_system_list>,
        fcppt::record::element<
            libftl::xml::labels::weapon_slots,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::drone_slots,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::weapon_list,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::count, unsigned>,
                    fcppt::record::element<libftl::xml::labels::missiles, unsigned>>,
                fcppt::optional::object<std::vector<libftl::xml::node<
                    fcppt::record::object<
                        fcppt::record::element<libftl::xml::labels::name, std::string>>,
                    fcppt::unit>>>>>,
        fcppt::record::element<
            libftl::xml::labels::drone_list,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::count, unsigned>,
                    fcppt::record::element<libftl::xml::labels::drones, unsigned>>,
                fcppt::optional::object<std::vector<libftl::xml::node<
                    fcppt::record::object<
                        fcppt::record::element<libftl::xml::labels::name, std::string>>,
                    fcppt::unit>>>>>,
        fcppt::record::element<
            libftl::xml::labels::health,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::amount, unsigned>>,
                fcppt::unit>>,
        fcppt::record::element<
            libftl::xml::labels::max_power,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::amount, unsigned>>,
                fcppt::unit>>,
        fcppt::record::element<
            libftl::xml::labels::shield_image,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, std::string>>>,
        fcppt::record::element<
            libftl::xml::labels::cloak_image,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, std::string>>>,
        fcppt::record::element<
            libftl::xml::labels::boarding_ai,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, std::string>>>>>;
}

#endif
