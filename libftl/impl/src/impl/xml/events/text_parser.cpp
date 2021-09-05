#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/events/text_parser.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/events/text.hpp>
#include <libftl/xml/labels/load.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::events::text, libftl::impl::xml::node>>
libftl::impl::xml::events::text_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "text",
      typed::alternative{
          typed::node_content{
              typed::attribute_set{fcppt::record::make(
                  labels::load{} = typed::attribute<std::string, required::yes>{"load"})},
              typed::empty{}},
          typed::node_content{
              typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}}}});
}
