#include <libftl/xml/blueprints/crew.hpp>
#include <libftl/xml/labels/bp.hpp>
#include <libftl/xml/labels/color_list.hpp>
#include <libftl/xml/labels/cost.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/power_list.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/short.hpp>
#include <libftl/xml/labels/title.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/blueprints/crew_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::crew, libftl::impl::xml::node>>
libftl::impl::xml::blueprints::crew_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "crewBlueprint",
      typed::attribute_set{fcppt::record::make(
          labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
      typed::inner_node{typed::node_set{fcppt::record::make(
          labels::desc{} = typed::make_node_member<required::yes>(
              "desc", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::cost{} = typed::make_node_member<required::yes>(
              "cost", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::bp{} = typed::make_node_member<required::yes>(
              "bp", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::title{} = typed::make_node_member<required::yes>(
              "title", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::short_{} = typed::make_node_member<required::yes>(
              "short", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::rarity{} = typed::make_node_member<required::yes>(
              "rarity", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
          labels::power_list{} = typed::make_node_member<required::yes>(
              "powerList",
              typed::attribute_set{fcppt::record::make()},
              typed::inner_node{typed::node_list{typed::node{
                  "power",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}}}}),
          labels::color_list{} = typed::make_node_member<required::no>(
              "colorList",
              typed::attribute_set{fcppt::record::make()},
              typed::inner_node{typed::node_list{typed::node{
                  "layer",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{typed::node_list{typed::node{
                      "color",
                      typed::attribute_set{fcppt::record::make(
                          labels::r{} = typed::attribute<std::uint8_t, required::yes>{"r"},
                          labels::g{} = typed::attribute<std::uint8_t, required::yes>{"g"},
                          labels::b{} = typed::attribute<std::uint8_t, required::yes>{"b"},
                          labels::a{} = typed::attribute<double, required::yes>{"a"})},
                      typed::empty{}}}}}}}))}}});
}
