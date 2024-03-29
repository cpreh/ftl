#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/blueprints/list_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/blueprints/list.hpp>
#include <libftl/xml/labels/name.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::list, libftl::impl::xml::node>>
libftl::impl::xml::blueprints::list_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "blueprintList",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
          typed::inner_node{typed::node_list{typed::node{
              "name",
              typed::node_content{
                  typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}}}}}}});
}
