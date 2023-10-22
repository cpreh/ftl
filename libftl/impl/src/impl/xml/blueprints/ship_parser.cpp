#include <libftl/impl/xml/blueprints/ship_parser.hpp>
#include <libftl/impl/xml/blueprints/system_element_parser.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/optional_inner_node.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <libftl/xml/labels/amount.hpp>
#include <libftl/xml/labels/battery.hpp>
#include <libftl/xml/labels/boarding_ai.hpp>
#include <libftl/xml/labels/class.hpp>
#include <libftl/xml/labels/cloak_image.hpp>
#include <libftl/xml/labels/cloaking.hpp>
#include <libftl/xml/labels/clonebay.hpp>
#include <libftl/xml/labels/count.hpp>
#include <libftl/xml/labels/doors.hpp>
#include <libftl/xml/labels/drone_list.hpp>
#include <libftl/xml/labels/drone_slots.hpp>
#include <libftl/xml/labels/drones.hpp>
#include <libftl/xml/labels/engines.hpp>
#include <libftl/xml/labels/hacking.hpp>
#include <libftl/xml/labels/health.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/layout.hpp>
#include <libftl/xml/labels/max_power.hpp>
#include <libftl/xml/labels/medbay.hpp>
#include <libftl/xml/labels/mind.hpp>
#include <libftl/xml/labels/missiles.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/oxygen.hpp>
#include <libftl/xml/labels/pilot.hpp>
#include <libftl/xml/labels/sensors.hpp>
#include <libftl/xml/labels/shield_image.hpp>
#include <libftl/xml/labels/shields.hpp>
#include <libftl/xml/labels/system_list.hpp>
#include <libftl/xml/labels/teleporter.hpp>
#include <libftl/xml/labels/weapon_list.hpp>
#include <libftl/xml/labels/weapon_slots.hpp>
#include <libftl/xml/labels/weapons.hpp>
#include <fcppt/deref_unique_ptr.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::ship, libftl::impl::xml::node>>
libftl::impl::xml::blueprints::ship_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  namespace blueprints = libftl::impl::xml::blueprints;
  using typed::required;

  return typed::make_derived(typed::node{
      "shipBlueprint",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"},
              labels::layout{} = typed::attribute<std::string, required::yes>{"layout"},
              labels::img{} = typed::attribute<std::string, required::yes>{"img"})},
          typed::inner_node{typed::node_set{fcppt::record::make(
              labels::class_{} = typed::make_node_member<required::yes>(
                  "class",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::name{} = typed::make_node_member<required::yes>(
                  "name",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::system_list{} = typed::make_node_member<required::yes>(
                  "systemList",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{typed::node_set{fcppt::record::make(
                      labels::pilot{} = blueprints::system_element_parser("pilot"),
                      labels::doors{} = blueprints::system_element_parser("doors"),
                      labels::sensors{} = blueprints::system_element_parser("sensors"),
                      labels::medbay{} = blueprints::system_element_parser("medbay"),
                      labels::oxygen{} = blueprints::system_element_parser("oxygen"),
                      labels::shields{} = blueprints::system_element_parser("shields"),
                      labels::engines{} = blueprints::system_element_parser("engines"),
                      labels::weapons{} = blueprints::system_element_parser("weapons"),
                      labels::drones{} = blueprints::system_element_parser("drones"),
                      labels::teleporter{} = blueprints::system_element_parser("teleporter"),
                      labels::cloaking{} = blueprints::system_element_parser("cloaking"),
                      labels::clonebay{} = blueprints::system_element_parser("clonebay"),
                      labels::battery{} = blueprints::system_element_parser("battery"),
                      labels::mind{} = blueprints::system_element_parser("mind"),
                      labels::hacking{} = blueprints::system_element_parser("hacking"))}}),
              labels::weapon_slots{} = typed::make_node_member<required::yes>(
                  "weaponSlots",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::drone_slots{} = typed::make_node_member<required::yes>(
                  "droneSlots",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::weapon_list{} = typed::make_node_member<required::yes>(
                  "weaponList",
                  typed::attribute_set{fcppt::record::make(
                      labels::count{} = typed::attribute<unsigned, required::yes>{"count"},
                      labels::missiles{} = typed::attribute<unsigned, required::yes>{"missiles"})},
                  typed::optional_inner_node{typed::node_list{typed::node{
                      "weapon",
                      typed::node_content{
                          typed::attribute_set{fcppt::record::make(
                              labels::name{} =
                                  typed::attribute<std::string, required::yes>{"name"})},
                          typed::empty{}}}}}),
              labels::drone_list{} = typed::make_node_member<required::yes>(
                  "doneList",
                  typed::attribute_set{fcppt::record::make(
                      labels::count{} = typed::attribute<unsigned, required::yes>{"count"},
                      labels::drones{} = typed::attribute<unsigned, required::yes>{"drones"})},
                  typed::optional_inner_node{typed::node_list{typed::node{
                      "drone",
                      typed::node_content{
                          typed::attribute_set{fcppt::record::make(
                              labels::name{} =
                                  typed::attribute<std::string, required::yes>{"name"})},
                          typed::empty{}}}}}),
              labels::health{} = typed::make_node_member<required::yes>(
                  "health",
                  typed::attribute_set{fcppt::record::make(
                      labels::amount{} = typed::attribute<unsigned, required::yes>{"amount"})},
                  typed::empty{}),
              labels::max_power{} = typed::make_node_member<required::yes>(
                  "maxPower",
                  typed::attribute_set{fcppt::record::make(
                      labels::amount{} = typed::attribute<unsigned, required::yes>{"amount"})},
                  typed::empty{}),
              labels::shield_image{} = typed::make_node_member<required::no>(
                  "shieldImage",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::cloak_image{} = typed::make_node_member<required::no>(
                  "cloakImage",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::boarding_ai{} = typed::make_node_member<required::no>(
                  "boardingAI",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}))}}}});
}
