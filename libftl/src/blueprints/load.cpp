#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/blueprints/data.hpp>
#include <libftl/blueprints/load.hpp>
#include <libftl/xml/blueprints.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


fcppt::either::object<
	libftl::error,
	libftl::blueprints::data
>
libftl::blueprints::load(
	libftl::archive::base &_archive
)
{
	auto const load_blueprint(
		[
			&_archive
		](
			std::string &&_file
		)
		->
		fcppt::either::object<
			libftl::error,
			fcppt::unique_ptr<
				libftl::xml::generated::blueprints::blueprints_root
			>
		>
		{
			return
				fcppt::either::bind(
					_archive.open(
						libftl::archive::path{
							"data"
						}
						/
						std::move(
							_file
						)
					),
					[](
						fcppt::unique_ptr<
							std::istream
						> &&_stream
					)
					{
						return
							libftl::xml::blueprints(
								*_stream
							);
					}
				);
		}
	);

	return
		fcppt::either::apply(
			[](
				fcppt::unique_ptr<
					libftl::xml::generated::blueprints::blueprints_root
				> &&_auto_blueprints,
				fcppt::unique_ptr<
					libftl::xml::generated::blueprints::blueprints_root
				> &&_blueprints,
				fcppt::unique_ptr<
					libftl::xml::generated::blueprints::blueprints_root
				> &&_dlc_blueprints,
				fcppt::unique_ptr<
					libftl::xml::generated::blueprints::blueprints_root
				> &&_dlc_pirate_blueprints,
				fcppt::unique_ptr<
					libftl::xml::generated::blueprints::blueprints_root
				> &&_dlc_blueprints_overwrites
			)
			{
				return
					libftl::blueprints::data{
						fcppt::container::make<
							std::vector<
								libftl::blueprints::data::normal_blueprints
							>
						>(
							libftl::blueprints::data::normal_blueprints{
								std::move(
									_auto_blueprints
								)
							},
							libftl::blueprints::data::normal_blueprints{
								std::move(
									_blueprints
								)
							}
						),
						fcppt::container::make<
							std::vector<
								libftl::blueprints::data::dlc_blueprints
							>
						>(
							libftl::blueprints::data::dlc_blueprints{
								std::move(
									_dlc_blueprints
								)
							},
							libftl::blueprints::data::dlc_blueprints{
								std::move(
									_dlc_pirate_blueprints
								)
							}
						),
						fcppt::container::make<
							std::vector<
								libftl::blueprints::data::dlc_blueprints_overwrites
							>
						>(
							libftl::blueprints::data::dlc_blueprints_overwrites{
								std::move(
									_dlc_blueprints_overwrites
								)
							}
						)
					};
			},
			load_blueprint(
				"autoBlueprints.xml"
			),
			load_blueprint(
				"blueprints.xml"
			),
			load_blueprint(
				"dlcBlueprints.xml"
			),
			load_blueprint(
				"dlcPirateBlueprints.xml"
			),
			load_blueprint(
				"dlcBlueprintsOverwrites.xml"
			)
		);
}
