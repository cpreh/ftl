#include <libftl/impl/xml/sectors/sector_type_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_named_node_derived.hpp>
#include <libftl/impl/xml/typed/named_node.hpp>
#include <libftl/impl/xml/typed/named_node_base.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/sectors/sector_type.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<libftl::impl::xml::typed::named_node_base<libftl::xml::sectors::sector_type>>
libftl::impl::xml::sectors::sector_type_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_named_node_derived(typed::named_node{
      "sectorType",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
          typed::inner_node{typed::node_list{typed::node{
              "sector",
              typed::node_content{
                  typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}}}}}}});
}
