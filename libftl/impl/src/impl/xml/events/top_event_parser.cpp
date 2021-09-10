#include <libftl/impl/xml/events/event_content_parser.hpp>
#include <libftl/impl/xml/events/top_event_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/make_named_node_derived.hpp>
#include <libftl/impl/xml/typed/named_node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/events/event.hpp>
#include <libftl/xml/events/top_event.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/unique.hpp>
#include <fcppt/deref_unique_ptr.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<libftl::impl::xml::typed::named_node_base<libftl::xml::events::top_event>>
libftl::impl::xml::events::top_event_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_named_node_derived(typed::named_node{
      "event",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"},
              labels::unique{} = typed::attribute<bool, required::no>{"unique"})},
          libftl::impl::xml::events::event_content_parser()}});
}
