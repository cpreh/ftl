#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/blueprints/weapon_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/blueprints/weapon.hpp>
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
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{
template <libftl::impl::xml::typed::required Required>
auto sound_parser(std::string &&_name)
{
  namespace typed = libftl::impl::xml::typed;
  return typed::make_node_member<Required>(
      std::move(_name),
      typed::attribute_set{fcppt::record::make()},
      typed::inner_node{typed::node_list{typed::node{
          "sound",
          typed::node_content{
              typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}}}}});
}
}

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::weapon, libftl::impl::xml::node>>
libftl::impl::xml::blueprints::weapon_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "weaponBlueprint",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
          typed::inner_node{typed::node_set{fcppt::record::make(
              labels::type{} = typed::make_node_member<required::yes>(
                  "type",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::title{} = typed::make_node_member<required::yes>(
                  "title",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::short_{} = typed::make_node_member<required::yes>(
                  "short",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::desc{} = typed::make_node_member<required::yes>(
                  "desc",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::tooltip{} = typed::make_node_member<required::yes>(
                  "tooltip",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::damage{} = typed::make_node_member<required::yes>(
                  "damage",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::ion{} = typed::make_node_member<required::no>(
                  "ion", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::speed{} = typed::make_node_member<required::no>(
                  "speed", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::shots{} = typed::make_node_member<required::yes>(
                  "shots", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::sp{} = typed::make_node_member<required::yes>(
                  "sp", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::fire_chance{} = typed::make_node_member<required::yes>(
                  "fireChance",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::breach_chance{} = typed::make_node_member<required::yes>(
                  "breachChance",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::stun_chance{} = typed::make_node_member<required::no>(
                  "stunChance",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::cooldown{} = typed::make_node_member<required::yes>(
                  "cooldown",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::power{} = typed::make_node_member<required::yes>(
                  "power", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::cost{} = typed::make_node_member<required::yes>(
                  "cost", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::bp{} = typed::make_node_member<required::yes>(
                  "bp", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::rarity{} = typed::make_node_member<required::yes>(
                  "rarity",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::length{} = typed::make_node_member<required::no>(
                  "length",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::image{} = typed::make_node_member<required::yes>(
                  "image",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::launch_sounds{} = sound_parser<required::yes>("launchSounds"),
              labels::hit_ship_sounds{} = sound_parser<required::no>("hitShipSounds"),
              labels::hit_shield_sounds{} = sound_parser<required::no>("hitShieldSounds"),
              labels::miss_sounds{} = sound_parser<required::no>("missSounds"),
              labels::weapon_art{} = typed::make_node_member<required::yes>(
                  "weaponArt",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::explosion{} = typed::make_node_member<required::no>(
                  "explosion",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::icon_image{} = typed::make_node_member<required::no>(
                  "iconImage",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}))}}}});
}
