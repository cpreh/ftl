#include <libftl/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/events/event_parser.hpp>
#include <libftl/impl/xml/events/event_list_parser.hpp>
#include <libftl/impl/xml/events/text_list_parser.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/partition.hpp>
#include <libftl/xml/events/event.hpp>
#include <libftl/xml/events/load.hpp>
#include <libftl/xml/events/result.hpp>
#include <fcppt/deref_unique_ptr.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, libftl::xml::events::result>
libftl::xml::events::load(std::istream &_input)
{
  namespace events = libftl::impl::xml::events;
  namespace typed = libftl::impl::xml::typed;

  auto const parser{typed::partition{typed::node_list{typed::alternative{
      events::event_parser(),
      events::event_list_parser(),
      events::text_list_parser()}}}};

  return fcppt::either::bind(
      libftl::impl::xml::parse(_input),
      [&parser](libftl::impl::xml::document const &_doc)
          -> fcppt::either::object<libftl::error, libftl::xml::events::result> {
        return parser.parse(_doc.nodes_);
      });
}
