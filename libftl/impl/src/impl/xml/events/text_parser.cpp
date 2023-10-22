#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/events/text_parser.hpp>
#include <libftl/impl/xml/events/text_parser_impl.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/xml/events/text.hpp>
#include <fcppt/deref_unique_ptr.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/unique_ptr.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::events::text, libftl::impl::xml::node>>
libftl::impl::xml::events::text_parser()
{
  return typed::make_derived(typed::node{
      "text",
      libftl::impl::xml::events::text_parser_impl()});
}
