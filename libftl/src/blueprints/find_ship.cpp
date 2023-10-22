#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/blueprints/find_ship.hpp>
#include <libftl/impl/blueprints/find.hpp>
#include <libftl/xml/blueprints/result.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <libftl/xml/labels/name.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <vector>
#include <fcppt/config/external_end.hpp>

fcppt::optional::reference<libftl::xml::blueprints::ship const>
libftl::blueprints::find_ship(
    fcppt::reference<libftl::blueprints::data const> const _data, std::string_view const _name)
{
  return libftl::impl::blueprints::find(
      fcppt::function<std::vector<libftl::xml::blueprints::ship> const &(
          libftl::xml::blueprints::result const &)>{
          [](libftl::xml::blueprints::result const &_blueprints)
              -> std::vector<libftl::xml::blueprints::ship> const & {
            return _blueprints.ships;
          }},
      fcppt::function<bool(libftl::xml::blueprints::ship const &)>{
          [&_name](libftl::xml::blueprints::ship const &_blueprint)
          { return _blueprint.attributes_.get<libftl::xml::labels::name>() == _name; }},
      _data);
}
