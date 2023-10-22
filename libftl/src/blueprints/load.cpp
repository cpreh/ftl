#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/blueprints/data.hpp>
#include <libftl/blueprints/load.hpp>
#include <libftl/xml/blueprints/load.hpp>
#include <libftl/xml/blueprints/result.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, libftl::blueprints::data>
libftl::blueprints::load(libftl::archive::base const &_archive)
{
  auto const load_blueprint(
      [&_archive](std::string const &_file)
          -> fcppt::either::object<libftl::error, libftl::xml::blueprints::result> {
        return fcppt::either::map_failure(
            fcppt::either::bind(
                _archive.open(libftl::archive::path{"data"} / std::string{_file}),
                // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
                [](fcppt::unique_ptr<std::istream> &&_stream)
                { return libftl::xml::blueprints::load(*_stream); }),
            // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
            [&_file](libftl::error &&_error)
            {
              return libftl::error{
                  FCPPT_TEXT("In blueprint file \"") + fcppt::from_std_string(_file) +
                  FCPPT_TEXT("\": ") + std::move(_error.get())};
            });
      });

  return fcppt::either::apply(
      [](libftl::xml::blueprints::result &&_auto_blueprints,
         libftl::xml::blueprints::result &&_blueprints,
         libftl::xml::blueprints::result &&_dlc_blueprints,
         libftl::xml::blueprints::result &&_dlc_pirate_blueprints,
         libftl::xml::blueprints::result &&_dlc_blueprints_overwrites)
      {
        return libftl::blueprints::data{
            libftl::blueprints::data::normal_blueprints{
                fcppt::container::make<libftl::blueprints::data::blueprint_vector>(
                    std::move(_auto_blueprints), std::move(_blueprints))},
            libftl::blueprints::data::dlc_blueprints{
                fcppt::container::make<libftl::blueprints::data::blueprint_vector>(
                    std::move(_dlc_blueprints), std::move(_dlc_pirate_blueprints))},
            libftl::blueprints::data::dlc_blueprints_overwrites{
                fcppt::container::make<libftl::blueprints::data::blueprint_vector>(
                    std::move(_dlc_blueprints_overwrites))}};
      },
      load_blueprint("autoBlueprints.xml"),
      load_blueprint("blueprints.xml"),
      load_blueprint("dlcBlueprints.xml"),
      load_blueprint("dlcPirateBlueprints.xml"),
      load_blueprint("dlcBlueprintsOverwrite.xml"));
}
