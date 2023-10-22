#include <libftl/error.hpp>
#include <libftl/impl/xml/load.hpp>
#include <libftl/impl/xml/events/event_list_parser.hpp>
#include <libftl/impl/xml/events/text_list_parser.hpp>
#include <libftl/impl/xml/events/top_event_parser.hpp>
#include <libftl/impl/xml/typed/named_alternative.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/partition.hpp>
#include <libftl/xml/events/load.hpp>
#include <libftl/xml/events/result.hpp>
#include <fcppt/deref_unique_ptr.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, libftl::xml::events::result>
libftl::xml::events::load(std::istream &_input)
{
  namespace events = libftl::impl::xml::events;
  namespace typed = libftl::impl::xml::typed;

  auto const parser{typed::partition{typed::node_list{typed::named_alternative{
      events::top_event_parser(), events::event_list_parser(), events::text_list_parser()}}}};

  return libftl::impl::xml::load(_input, parser);
}
