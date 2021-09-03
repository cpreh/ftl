#include <libftl/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/blueprints/aug_parser.hpp>
#include <libftl/impl/xml/blueprints/crew_parser.hpp>
#include <libftl/impl/xml/blueprints/drone_parser.hpp>
#include <libftl/impl/xml/blueprints/item_parser.hpp>
#include <libftl/impl/xml/blueprints/list_parser.hpp>
#include <libftl/impl/xml/blueprints/ship_parser.hpp>
#include <libftl/impl/xml/blueprints/system_parser.hpp>
#include <libftl/impl/xml/blueprints/weapon_parser.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/partition.hpp>
#include <libftl/xml/blueprints/load.hpp>
#include <libftl/xml/blueprints/result.hpp>
#include <fcppt/deref_unique_ptr.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, libftl::xml::blueprints::result>
libftl::xml::blueprints::load(std::istream &_input)
{
  namespace blueprints = libftl::impl::xml::blueprints;
  namespace typed = libftl::impl::xml::typed;

  auto const parser{typed::partition{typed::node_list{typed::alternative{
      blueprints::aug_parser(),
      blueprints::crew_parser(),
      blueprints::drone_parser(),
      blueprints::item_parser(),
      blueprints::list_parser(),
      blueprints::ship_parser(),
      blueprints::system_parser(),
      blueprints::weapon_parser()}}}};

  return fcppt::either::bind(
      libftl::impl::xml::parse(_input),
      [&parser](libftl::impl::xml::document const &_doc)
          -> fcppt::either::object<libftl::error, libftl::xml::blueprints::result> {
        return parser.parse(_doc.nodes_);
      });
}
