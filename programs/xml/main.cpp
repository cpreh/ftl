#include <libftl/archive/entry.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/archive/length.hpp>
#include <libftl/archive/offset.hpp>
#include <libftl/xml/blueprints.hpp>
#include <libftl/xml/sector.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <libftl/xml/generated/sector.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/algorithm/find_opt.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/int_to_enum.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/enum_array.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/filesystem/file_size.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/size_to_size_t.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/extract.hpp>
#include <fcppt/io/istream.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/options/apply.hpp>
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
#include <fcppt/variant/variadic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <boost/filesystem/path.hpp>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::either::object<
	fcppt::string,
	libftl::archive::file
>
make_file(
	boost::filesystem::path const &_path,
	std::istream &_stream
)
{
	return
		fcppt::either::bind(
			fcppt::either::from_optional(
				fcppt::filesystem::file_size(
					_path
				),
				[
					&_path
				]{
					return
						FCPPT_TEXT("Cannot read file size of \"")
						+
						fcppt::filesystem::path_to_string(
							_path
						)
						+
						FCPPT_TEXT("\".");
				}
			),
			[
				&_stream,
				&_path
			](
				boost::uintmax_t const _size
			)
			{
				return
					fcppt::either::map(
						fcppt::either::from_optional(
							fcppt::filesystem::size_to_size_t(
								_size
							),
							[
								&_path,
								_size
							]{
								return
									FCPPT_TEXT("File size ")
									+
									fcppt::insert_to_fcppt_string(
										_size
									)
									+
									FCPPT_TEXT(" of \"")
									+
									fcppt::filesystem::path_to_string(
										_path
									)
									+
									FCPPT_TEXT("\" too large.");
							}
						),
						[
							&_stream
						](
							std::size_t const _std_size
						)
						{
							return
								libftl::archive::file{
									fcppt::make_ref(
										_stream
									),
									libftl::archive::entry{
										libftl::archive::offset{
											0
										},
										libftl::archive::length{
											fcppt::cast::size<
												std::streamsize
											>(
												fcppt::cast::to_signed(
													_std_size
												)
											)
										}
									}
								};
						}
					);
			}
		);
}

FCPPT_RECORD_MAKE_LABEL(
	type_label
);

FCPPT_RECORD_MAKE_LABEL(
	path_label
);

// TODO: Better pretty type for fcppt.options
enum class xml_type
{
	blueprints,
	sector_data,
	fcppt_maximum = sector_data
};

typedef
fcppt::container::enum_array<
	xml_type,
	fcppt::string
>
xml_type_array;

xml_type_array const xml_types{{{
	FCPPT_TEXT("blueprints"),
	FCPPT_TEXT("sector_data")
}}};

/*
fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &_stream,
	xml_type const _name
)
{
	return
		_stream
		<<
		xml_types[
			_name
		];
}*/

fcppt::io::istream &
operator>>(
	fcppt::io::istream &_stream,
	xml_type &_name
)
{
	fcppt::optional::maybe_void(
		fcppt::io::extract<
			fcppt::string
		>(
			_stream
		),
		[
			&_stream,
			&_name
		](
			fcppt::string const &_value
		)
		{
			fcppt::optional::maybe(
				fcppt::algorithm::find_opt(
					xml_types,
					_value
				),
				[
					&_stream
				]{
					_stream.setstate(
						std::ios_base::failbit
					);
				},
				[
					&_name
				](
					xml_type_array::const_iterator const _it
				)
				{
					_name =
						fcppt::cast::int_to_enum<
							xml_type
						>(
							std::distance(
								xml_types.begin(),
								_it
							)
						);
				}
			);
		}
	);

	return
		_stream;
}

typedef
fcppt::record::variadic<
	fcppt::record::element<
		type_label,
		xml_type
	>,
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

	typedef
	fcppt::variant::variadic<
		fcppt::unique_ptr<
			libftl::xml::generated::blueprints_root
		>,
		fcppt::unique_ptr<
			libftl::xml::generated::sector_root
		>
	>
	result_type;

	return
		fcppt::either::match(
			fcppt::either::bind(
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
								FCPPT_TEXT("Cannot open ")
								+
								fcppt::filesystem::path_to_string(
									path
								);
						}
					),
					[
						&path
					](
						std::ifstream &&_stream
					)
					{
						return
							make_file(
								path,
								_stream
							);
					}
				),
				[
					&_arguments
				](
					libftl::archive::file const &_file
				)
				->
				fcppt::either::object<
					fcppt::string,
					result_type
				>
				{
					auto const wrap_result(
						[](
							auto &&_result
						)
						{
							return
								result_type{
									std::move(
										_result
									)
								};
						}
					);

					switch(
						fcppt::record::get<
							type_label
						>(
							_arguments
						)
					)
					{
					case xml_type::blueprints:
						return
							fcppt::either::map(
								libftl::xml::blueprints(
									_file
								),
								wrap_result
							);
					case xml_type::sector_data:
						return
							fcppt::either::map(
								libftl::xml::sector(
									_file
								),
								wrap_result
							);
					}

					FCPPT_ASSERT_UNREACHABLE;
				}
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
					false;
			},
			[](
				result_type const &_result
			)
			{
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
	auto const parser{
		fcppt::options::apply(
			fcppt::options::argument<
				type_label,
				xml_type
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("Type")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Type of the XML file to parse")
					}
				}
			},
			fcppt::options::argument<
				path_label,
				fcppt::string
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("Path")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Path to the .xml file")
					}
				}
			}
		)
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
