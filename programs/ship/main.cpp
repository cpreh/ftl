#include <libftl/error.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/output.hpp>
#include <libftl/ship/layout/parse.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/record/variadic.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <fcppt/config/external_end.hpp>


namespace
{

FCPPT_RECORD_MAKE_LABEL(
	path_label
);

typedef
fcppt::record::variadic<
	fcppt::record::element<
		path_label,
		fcppt::string
	>
>
argument_record;

bool
main_program(
	argument_record const &_arguments
)
{
	boost::filesystem::path const path{
		fcppt::record::get<
			path_label
		>(
			_arguments
		)
	};

	return
		fcppt::either::match(
			fcppt::either::bind(
				fcppt::either::from_optional(
					fcppt::filesystem::open<
						std::ifstream
					>(
						path,
						std::ios_base::openmode{}
					),
					[
						&path
					]{
						return
							libftl::error{
								FCPPT_TEXT("Cannot open ")
								+
								fcppt::filesystem::path_to_string(
									path
								)
							};
					}
				),
				[](
					std::ifstream &&_stream
				)
				{
					return
						libftl::ship::layout::parse(
							_stream
						);
				}
			),
			[](
				libftl::error const &_error
			)
			{
				fcppt::io::cerr()
					<<
					_error
					<<
					FCPPT_TEXT('\n');

				return
					false;
			},
			[](
				libftl::ship::layout::object const &_layout
			)
			{
				fcppt::io::cout()
					<<
					_layout
					<<
					FCPPT_TEXT('\n');

				return
					true;
			}
		);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

int
FCPPT_MAIN(
	int argc,
	fcppt::args_char **argv
)
try
{
	fcppt::options::argument<
		path_label,
		fcppt::string
	> const parser{
		fcppt::options::long_name{
			FCPPT_TEXT("Path")
		},
		fcppt::options::optional_help_text{
			fcppt::options::help_text{
				FCPPT_TEXT("Path to the .txt file")
			}
		}
	};

	typedef
	decltype(
		parser
	)
	parser_type;

	return
		fcppt::variant::match(
			fcppt::options::parse_help(
				fcppt::options::default_help_switch(),
				parser,
				fcppt::args_from_second(
					argc,
					argv
				)
			),
			[](
				fcppt::options::result<
					fcppt::options::result_of<
						parser_type
					>
				> const &_result
			)
			{
				return
					fcppt::either::match(
						_result,
						[](
							fcppt::options::error const &_error
						)
						{
							fcppt::io::cerr()
								<<
								_error
								<<
								FCPPT_TEXT('\n');

							return
								false;
						},
						[](
							fcppt::options::result_of<
								parser_type
							> const &_arguments
						)
						{
							return
								main_program(
									fcppt::record::permute<
										argument_record
									>(
										_arguments
									)
								);
						}
					);
			},
			[](
				fcppt::options::help_text const &_help_text
			)
			{
				fcppt::io::cout()
					<<
					_help_text
					<<
					FCPPT_TEXT('\n');

				return
					true;
			}
		)
		?
			EXIT_SUCCESS
		:
			EXIT_FAILURE
		;

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
