#ifndef LIBFTL_IMPL_XML_EVENTS_EVENT_PARSER_IMPL_HPP_INCLUDED
#define LIBFTL_IMPL_XML_EVENTS_EVENT_PARSER_IMPL_HPP_INCLUDED

#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/make_construct.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/events/event.hpp>
#include <libftl/xml/labels/load.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::events
{
template <typename ContentParser>
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::events::event, libftl::impl::xml::node>>
event_parser_impl(ContentParser &&_content_parser)
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::make_construct<libftl::xml::events::event>(typed::alternative{
      typed::node_content{
          typed::attribute_set{fcppt::record::make()},
          std::forward<ContentParser>(_content_parser)},
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::load{} = typed::attribute<std::string, required::yes>{"load"})},
          typed::empty{}}}));
}
}

#endif
