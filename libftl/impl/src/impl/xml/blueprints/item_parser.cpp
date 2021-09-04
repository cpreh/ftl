#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/blueprints/item_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/blueprints/item.hpp>
#include <libftl/xml/labels/cost.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/title.hpp>
#include <libftl/xml/labels/type.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::item, libftl::impl::xml::node>>
libftl::impl::xml::blueprints::item_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "itemBlueprint",
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
              labels::cost{} = typed::make_node_member<required::yes>(
                  "cost", typed::attribute_set{fcppt::record::make()}, typed::content<unsigned>{}),
              labels::rarity{} = typed::make_node_member<required::yes>(
                  "rarity",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}))}}}});
}
