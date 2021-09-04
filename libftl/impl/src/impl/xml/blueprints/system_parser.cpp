#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/blueprints/system_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/blueprints/system.hpp>
#include <libftl/xml/labels/cost.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/locked.hpp>
#include <libftl/xml/labels/max_power.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/start_power.hpp>
#include <libftl/xml/labels/title.hpp>
#include <libftl/xml/labels/type.hpp>
#include <libftl/xml/labels/upgrade_cost.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::system, libftl::impl::xml::node>>
libftl::impl::xml::blueprints::system_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "systemBlueprint",
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
              labels::desc{} = typed::make_node_member<required::yes>(
                  "desc",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::start_power{} = typed::make_node_member<required::yes>(
                  "startPower",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::max_power{} = typed::make_node_member<required::yes>(
                  "maxPower",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::rarity{} = typed::make_node_member<required::yes>(
                  "rarity",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}),
              labels::upgrade_cost{} = typed::make_node_member<required::yes>(
                  "upgradeCost",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{typed::node_list{typed::node{
                      "level",
                      typed::node_content{
                          typed::attribute_set{fcppt::record::make()},
                          typed::content<unsigned>{}}}}}),
              labels::cost{} = typed::make_node_member<required::yes>(
                  "cost", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::locked{} = typed::make_node_member<required::no>(
                  "locked",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}))}}}});
}
