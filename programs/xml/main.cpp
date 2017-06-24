#include <libftl/archive/entry.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/archive/length.hpp>
#include <libftl/archive/offset.hpp>
#include <libftl/xml/achievements.hpp>
#include <libftl/xml/animations.hpp>
#include <libftl/xml/blueprints.hpp>
#include <libftl/xml/sectors.hpp>
#include <libftl/xml/ship.hpp>
#include <libftl/xml/generated/achievements.hpp>
#include <libftl/xml/generated/animations.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <libftl/xml/generated/sectors.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/enum/input.hpp>
#include <fcppt/enum/names_array.hpp>
#include <fcppt/enum/names_impl_fwd.hpp>
#include <fcppt/filesystem/file_size.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/size_to_size_t.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/istream.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/pretty_type_enum.hpp>
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

enum class xml_type
{
	achievements,
	animations,
	blueprints,
	sectors,
	ship,
	fcppt_maximum = ship
};

typedef
fcppt::enum_::names_array<
	xml_type
>
xml_type_array;

xml_type_array const xml_types{{{
	FCPPT_TEXT("achievements"),
	FCPPT_TEXT("animations"),
	FCPPT_TEXT("blueprints"),
	FCPPT_TEXT("sectors"),
	FCPPT_TEXT("ship")
}}};

}

namespace fcppt
{
namespace enum_
{

template<>
struct names_impl<
	xml_type
>
{
	static
	xml_type_array const &
	get()
	{
		return
			xml_types;
	}
};

}
}

namespace
{

fcppt::io::istream &
operator>>(
	fcppt::io::istream &_stream,
	xml_type &_name
)
{
	return
		fcppt::enum_::input(
			_stream,
			_name
		);
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
			libftl::xml::generated::achievements_root
		>,
		fcppt::unique_ptr<
			libftl::xml::generated::animations_root
		>,
		fcppt::unique_ptr<
			libftl::xml::generated::blueprints_root
		>,
		fcppt::unique_ptr<
			libftl::xml::generated::sectors_root
		>,
		fcppt::unique_ptr<
			libftl::xml::generated::ship_root
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
					case xml_type::achievements:
						return
							fcppt::either::map(
								libftl::xml::achievements(
									_file
								),
								wrap_result
							);
					case xml_type::animations:
						return
							fcppt::either::map(
								libftl::xml::animations(
									_file
								),
								wrap_result
							);
					case xml_type::blueprints:
						return
							fcppt::either::map(
								libftl::xml::blueprints(
									_file
								),
								wrap_result
							);
					case xml_type::sectors:
						return
							fcppt::either::map(
								libftl::xml::sectors(
									_file
								),
								wrap_result
							);
					case xml_type::ship:
						return
							fcppt::either::map(
								libftl::xml::ship(
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
