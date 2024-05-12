#ifndef LIBFTL_IMPL_XML_EVENTS_EVENT_PARSER_IMPL_HPP_INCLUDED
#define LIBFTL_IMPL_XML_EVENTS_EVENT_PARSER_IMPL_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/events/load_record.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/make_construct.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/xml/events/event.hpp>
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

  return typed::make_derived(typed::make_construct<libftl::xml::events::event>(typed::alternative{
      typed::node_content{
          typed::attribute_set{fcppt::record::make()},
          std::forward<ContentParser>(_content_parser)},
      typed::node_content{
          typed::attribute_set{libftl::impl::xml::events::load_record()}, typed::empty{}}}));
}
}

#endif
