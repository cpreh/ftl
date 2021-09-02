#ifndef LIBFTL_XML_BLUEPRINTS_WEAPON_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_WEAPON_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/blueprints/sound_list.hpp>
#include <libftl/xml/labels/bp.hpp>
#include <libftl/xml/labels/breach_chance.hpp>
#include <libftl/xml/labels/cooldown.hpp>
#include <libftl/xml/labels/cost.hpp>
#include <libftl/xml/labels/damage.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/explosion.hpp>
#include <libftl/xml/labels/fire_chance.hpp>
#include <libftl/xml/labels/hit_shield_sounds.hpp>
#include <libftl/xml/labels/hit_ship_sounds.hpp>
#include <libftl/xml/labels/icon_image.hpp>
#include <libftl/xml/labels/image.hpp>
#include <libftl/xml/labels/ion.hpp>
#include <libftl/xml/labels/launch_sounds.hpp>
#include <libftl/xml/labels/length.hpp>
#include <libftl/xml/labels/miss_sounds.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/power.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/short.hpp>
#include <libftl/xml/labels/shots.hpp>
#include <libftl/xml/labels/sp.hpp>
#include <libftl/xml/labels/speed.hpp>
#include <libftl/xml/labels/stun_chance.hpp>
#include <libftl/xml/labels/title.hpp>
#include <libftl/xml/labels/tooltip.hpp>
#include <libftl/xml/labels/type.hpp>
#include <libftl/xml/labels/weapon_art.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using weapon = libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::name, std::string>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::type,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::title,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::short_,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::desc,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::tooltip,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::damage,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::ion,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, unsigned>>>,
        fcppt::record::element<
            libftl::xml::labels::speed,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, unsigned>>>,
        fcppt::record::element<
            libftl::xml::labels::shots,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::
            element<libftl::xml::labels::sp, libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::fire_chance,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::breach_chance,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::stun_chance,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, unsigned>>>,
        fcppt::record::element<
            libftl::xml::labels::cooldown,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::power,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::cost,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::
            element<libftl::xml::labels::bp, libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::rarity,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::length,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, unsigned>>>,
        fcppt::record::element<
            libftl::xml::labels::image,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::
            element<libftl::xml::labels::launch_sounds, libftl::xml::blueprints::sound_list>,
        fcppt::record::element<
            libftl::xml::labels::hit_ship_sounds,
            fcppt::optional::object<libftl::xml::blueprints::sound_list>>,
        fcppt::record::element<
            libftl::xml::labels::hit_shield_sounds,
            fcppt::optional::object<libftl::xml::blueprints::sound_list>>,
        fcppt::record::element<
            libftl::xml::labels::miss_sounds,
            fcppt::optional::object<libftl::xml::blueprints::sound_list>>,
        fcppt::record::element<
            libftl::xml::labels::weapon_art,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::explosion,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, std::string>>>,
        fcppt::record::element<
            libftl::xml::labels::icon_image,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, std::string>>>>>;
}

#endif
