#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/events/event_content_parser.hpp>
#include <libftl/impl/xml/events/event_parser.hpp>
#include <libftl/impl/xml/events/event_parser_impl.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/xml/events/event.hpp>
#include <fcppt/deref_unique_ptr.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/unique_ptr.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::events::event, libftl::impl::xml::node>>
libftl::impl::xml::events::event_parser()
{
  namespace typed = libftl::impl::xml::typed;

  return libftl::impl::xml::typed::make_derived(typed::node{
      "event",
      libftl::impl::xml::events::event_parser_impl(
          libftl::impl::xml::events::event_content_parser())});
}
