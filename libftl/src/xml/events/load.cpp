#include <libftl/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/events/event_parser.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/xml/events/event_members.hpp>
#include <libftl/xml/events/load.hpp>
#include <libftl/xml/events/result.hpp>
#include <fcppt/deref_unique_ptr.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>

fcppt::either::object<libftl::error, libftl::xml::events::result>
libftl::xml::events::load(std::istream &_input)
{
  namespace typed = libftl::impl::xml::typed;

  auto const parser{
    typed::node_list{libftl::impl::xml::events::event_parser()}};

  return fcppt::either::bind(
      libftl::impl::xml::parse(_input),
      [&parser](libftl::impl::xml::document const &_doc)
          -> fcppt::either::object<libftl::error, libftl::xml::events::result> {
        return parser.parse(_doc.nodes_);
      });
}
