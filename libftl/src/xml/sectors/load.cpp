#include <libftl/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/sectors/sector_description_parser.hpp>
#include <libftl/impl/xml/sectors/sector_type_parser.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/partition.hpp>
#include <libftl/xml/sectors/load.hpp>
#include <libftl/xml/sectors/result.hpp>
#include <fcppt/deref_unique_ptr.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, libftl::xml::sectors::result>
libftl::xml::sectors::load(std::istream &_input)
{
  namespace sectors = libftl::impl::xml::sectors;
  namespace typed = libftl::impl::xml::typed;

  auto const parser{typed::partition{typed::node_list{typed::alternative{
      sectors::sector_description_parser(),
      sectors::sector_type_parser()}}}};

  return fcppt::either::bind(
      libftl::impl::xml::parse(_input),
      [&parser](libftl::impl::xml::document const &_doc)
          -> fcppt::either::object<libftl::error, libftl::xml::sectors::result> {
        return parser.parse(_doc.nodes_);
      });
}
