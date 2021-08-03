#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/blueprints/find_ship.hpp>
#include <libftl/impl/blueprints/find.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/tree/containers.hxx>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::optional::reference<libftl::xml::generated::blueprints::ship_blueprint const>
libftl::blueprints::find_ship(
    fcppt::reference<libftl::blueprints::data const> const _data, std::string const &_name)
{
  return libftl::impl::blueprints::find(
      fcppt::function<
          ::xsd::cxx::tree::sequence<libftl::xml::generated::blueprints::ship_blueprint> const &(
              libftl::xml::generated::blueprints::blueprints_root const &)>{
          [](libftl::xml::generated::blueprints::blueprints_root const &_root)
              -> ::xsd::cxx::tree::sequence<
                  libftl::xml::generated::blueprints::ship_blueprint> const & {
            return _root.shipBlueprint();
          }},
      fcppt::function<bool(libftl::xml::generated::blueprints::ship_blueprint const &)>{
          [&_name](libftl::xml::generated::blueprints::ship_blueprint const &_blueprint)
          { return _blueprint.name1() == _name; }},
      _data);
}
