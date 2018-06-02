#include <libftl/xml/parse.hpp>
#include <fcppt/string.hpp>
#include <fcppt/filesystem/file_to_string.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


#include <string>
#include <iostream>

int
main(
	int argc,
	char **argv
)
{
	// TODO: fcppt::options
	if(
		argc
		!=
		2
	)
	{
		std::cout << "Invalid parameter count\n";

		return
			EXIT_FAILURE;
	}

	std::string const file{
		argv[1]
	};

	fcppt::optional::maybe(
		fcppt::filesystem::file_to_string(
			file
		),
		[
			&file
		]{
			std::cout << "failed to open " << file << '\n';
		},
		[](
			fcppt::string const &_file
		)
		{
			libftl::xml::parse(
				_file
			);
		}
	);

	return
		EXIT_SUCCESS;
}
