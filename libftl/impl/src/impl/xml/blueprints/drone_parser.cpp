#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/blueprints/drone_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/blueprints/drone.hpp>
#include <libftl/xml/labels/bp.hpp>
#include <libftl/xml/labels/cooldown.hpp>
#include <libftl/xml/labels/cost.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/dodge.hpp>
#include <libftl/xml/labels/drone_image.hpp>
#include <libftl/xml/labels/icon_image.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/power.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/short.hpp>
#include <libftl/xml/labels/speed.hpp>
#include <libftl/xml/labels/tip.hpp>
#include <libftl/xml/labels/title.hpp>
#include <libftl/xml/labels/type.hpp>
#include <libftl/xml/labels/weapon_blueprint.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::drone, libftl::impl::xml::node>>
libftl::impl::xml::blueprints::drone_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "droneBlueprint",
      typed::attribute_set{fcppt::record::make(
          labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
      typed::inner_node{typed::node_set{fcppt::record::make(
          labels::type{} = typed::make_node_member<required::yes>(
              "type", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::tip{} = typed::make_node_member<required::yes>(
              "tip", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::title{} = typed::make_node_member<required::yes>(
              "title", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::short_{} = typed::make_node_member<required::yes>(
              "short", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::desc{} = typed::make_node_member<required::yes>(
              "desc", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::power{} = typed::make_node_member<required::yes>(
              "power", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::cooldown{} = typed::make_node_member<required::yes>(
              "cooldown", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::dodge{} = typed::make_node_member<required::yes>(
              "dodge", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::speed{} = typed::make_node_member<required::yes>(
              "speed", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::cost{} = typed::make_node_member<required::yes>(
              "cost", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::bp{} = typed::make_node_member<required::yes>(
              "bp", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::drone_image{} = typed::make_node_member<required::yes>(
              "droneImage",
              typed::attribute_set{fcppt::record::make()},
              typed::content<std::string>{}),
          labels::weapon_blueprint{} = typed::make_node_member<required::yes>(
              "weaponBlueprint",
              typed::attribute_set{fcppt::record::make()},
              typed::content<std::string>{}),
          labels::rarity{} = typed::make_node_member<required::yes>(
              "rarity", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::icon_image{} = typed::make_node_member<required::no>(
              "iconImage",
              typed::attribute_set{fcppt::record::make()},
              typed::content<std::string>{}))}}});
}
