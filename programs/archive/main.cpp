#include <libftl/archive/entry_output.hpp>
#include <libftl/archive/index.hpp>
#include <libftl/archive/read_index.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iostream>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

// FIXME
namespace std
{

fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &_stream,
	libftl::archive::index::value_type const &_pair
)
{
	return
		_stream
		<<
		FCPPT_TEXT('(')
		<<
		fcppt::from_std_string(
			_pair.first
		)
		<<
		FCPPT_TEXT(',')
		<<
		_pair.second
		<<
		FCPPT_TEXT(')');
}

}

int
FCPPT_MAIN(
	int argc,
	fcppt::args_char **argv
)
try
{
	FCPPT_RECORD_MAKE_LABEL(
		path_label
	);

	typedef
	fcppt::options::argument<
		path_label,
		fcppt::string
	>
	parser_type;

	parser_type const parser{
		fcppt::options::long_name{
			FCPPT_TEXT("Path")
		},
		fcppt::options::optional_help_text{
			fcppt::options::help_text{
				FCPPT_TEXT("Path to the .dat file")
			}
		}
	};

	return
		fcppt::either::match(
			fcppt::options::parse(
				parser,
				fcppt::args_from_second(
					argc,
					argv
				)
			),
			[
				&parser
			](
				fcppt::options::error const &_error
			)
			{
				fcppt::io::cerr()
					<<
					_error
					<<
					FCPPT_TEXT("\nUsage: ")
					<<
					parser.usage()
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_FAILURE;
			},
			[](
				fcppt::options::result_of<
					parser_type
				> const &_result
			)
			{
				boost::filesystem::path const path{
					fcppt::record::get<
						path_label
					>(
						_result
					)
				};

				boost::filesystem::ifstream stream{
					path,
					std::ios_base::binary
				};

				if(
					!stream.is_open()
				)
				{
					fcppt::io::cerr()
						<<
						FCPPT_TEXT("Cannot open ")
						<<
						fcppt::filesystem::path_to_string(
							path
						)
						<<
						FCPPT_TEXT('\n');

					return
						EXIT_FAILURE;
				}

				return
					fcppt::either::match(
						libftl::archive::read_index(
							stream
						),
						[](
							fcppt::string const &_error
						)
						{
							fcppt::io::cerr()
								<<
								_error
								<<
								FCPPT_TEXT('\n');

							return
								EXIT_FAILURE;
						},
						[](
							libftl::archive::index const &_index
						)
						{
							fcppt::io::cout()
								<<
								fcppt::container::output(
									_index
								)
								<<
								FCPPT_TEXT('\n');

							return
								EXIT_SUCCESS;
						}
					);
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<<
		_error.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<<
		_error.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}

FCPPT_PP_POP_WARNING
