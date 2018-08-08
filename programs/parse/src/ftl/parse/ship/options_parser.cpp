#include <ftl/parse/path_label.hpp>
#include <ftl/parse/ship/arguments.hpp>
#include <ftl/parse/ship/options_parser.hpp>
#include <libftl/archive/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/base.hpp>
#include <fcppt/options/base_unique_ptr.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_base.hpp>
#include <fcppt/options/optional_help_text.hpp>


fcppt::options::base_unique_ptr<
	ftl::parse::ship::arguments
>
ftl::parse::ship::options_parser()
{
	return
		fcppt::options::make_base<
			ftl::parse::ship::arguments
		>(
			fcppt::options::argument<
				ftl::parse::path_label,
				libftl::archive::path
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("ship-file")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Name of the ship .txt file")
					}
				}
			}
		);
}
