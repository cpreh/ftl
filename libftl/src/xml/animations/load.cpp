#include <libftl/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/animations/anim_parser.hpp>
#include <libftl/impl/xml/animations/anim_sheet_parser.hpp>
#include <libftl/impl/xml/animations/weapon_anim_parser.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/partition.hpp>
#include <libftl/xml/animations/load.hpp>
#include <libftl/xml/animations/result.hpp>
#include <fcppt/deref_unique_ptr.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, libftl::xml::animations::result>
libftl::xml::animations::load(std::istream &_input)
{
  namespace animations = libftl::impl::xml::animations;
  namespace typed = libftl::impl::xml::typed;

  auto const parser{typed::partition{typed::node_list{typed::alternative{
      animations::anim_parser(),
      animations::anim_sheet_parser(),
      animations::weapon_anim_parser()}}}};

  return fcppt::either::bind(
      libftl::impl::xml::parse(_input),
      [&parser](libftl::impl::xml::document const &_doc)
          -> fcppt::either::object<libftl::error, libftl::xml::animations::result> {
        return parser.parse(_doc.nodes_);
      });
}
