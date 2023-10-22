#include <libftl/impl/xml/events/text_list_parser.hpp>
#include <libftl/impl/xml/events/text_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_named_node_derived.hpp>
#include <libftl/impl/xml/typed/named_node.hpp>
#include <libftl/impl/xml/typed/named_node_base.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/events/text_list.hpp>
#include <libftl/xml/labels/name.hpp>
#include <fcppt/deref_unique_ptr.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<libftl::impl::xml::typed::named_node_base<libftl::xml::events::text_list>>
libftl::impl::xml::events::text_list_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_named_node_derived(typed::named_node{
      "textList",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
          typed::inner_node{typed::node_list{libftl::impl::xml::events::text_parser()}}}});
}
