#ifndef LIBFTL_IMPL_XML_READ_HPP_INCLUDED
#define LIBFTL_IMPL_XML_READ_HPP_INCLUDED

#include <libftl/archive/entry_output.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/archive/extract.hpp>
#include <libftl/impl/xml/make_closing_tag.hpp>
#include <libftl/impl/xml/make_opening_tag.hpp>
#include <libftl/impl/xml/replace.hpp>
#include <libftl/impl/xml/replace_list.hpp>
#include <libftl/impl/xml/root_name.hpp>
#include <libftl/xml/result.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/identity.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_from_std.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/exceptions.hxx>
#include <xsd/cxx/tree/exceptions.hxx>
#include <memory>
#include <regex>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{

template<
	typename Result
>
libftl::xml::result<
	Result
>
read(
	libftl::archive::file const &_file,
	fcppt::function<
		std::unique_ptr<
			Result
		>(
			std::string const &
		)
	> const &_function,
	libftl::impl::xml::root_name const &_root_name,
	libftl::impl::xml::replace_list const &_replace_list
)
{
	return
		fcppt::either::bind(
			fcppt::either::from_optional(
				libftl::archive::extract(
					_file
				),
				[
					&_file
				]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to read ")
							+
							fcppt::insert_to_fcppt_string(
								_file.entry
							)
							+
							FCPPT_TEXT(": Invalid read.")
						};
				}
			),
			[
				&_function,
				&_root_name,
				&_file,
				&_replace_list
			](
				fcppt::io::buffer const &_buffer
			)
			{
				std::string const input{
					libftl::impl::xml::make_opening_tag(
						_root_name
					)
					+
					'\n'
					+
					fcppt::algorithm::map<
						std::string
					>(
						_buffer,
						fcppt::identity{}
					)
					+
					libftl::impl::xml::make_closing_tag(
						_root_name
					)
					+
					'\n'
				};

				std::string const replaced{
					fcppt::algorithm::fold(
						fcppt::algorithm::join(
							libftl::impl::xml::replace_list{
								libftl::impl::xml::replace{
									std::regex{
										"<\\?xml.*\\?>"
									},
									""
								},
								libftl::impl::xml::replace{
									std::regex{
										"<!--[^]*?-->"
									},
									""
								}
							},
							_replace_list
						),
						input,
						[](
							libftl::impl::xml::replace const &_replace,
							std::string &&_string
						)
						{
							return
								std::regex_replace(
									std::move(
										_string
									),
									_replace.regex_,
									_replace.replace_string_
								);
						}
					)
				};

				typedef
				libftl::xml::result<
					Result
				>
				result_type;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
				auto const make_error(
					[
						&_file
					](
						fcppt::string &&_value
					)
					->
					result_type
					{
						return
							result_type{
								FCPPT_TEXT("Failed to read ")
								+
								fcppt::insert_to_fcppt_string(
									_file.entry
								)
								+
								FCPPT_TEXT(": ")
								+
								std::move(
									_value
								)
							};
					}
				);
FCPPT_PP_POP_WARNING

				try
				{
					return
						result_type{
							FCPPT_ASSERT_OPTIONAL_ERROR(
								fcppt::unique_ptr_from_std(
									_function(
										replaced
									)
								)
							)
						};
				}
				catch(
					xsd::cxx::tree::expected_element<
						char
					> const &_error
				)
				{
					return
						make_error(
							FCPPT_TEXT("Expected element ")
							+
							fcppt::from_std_string(
								_error.name()
							)
							+
							FCPPT_TEXT(" in namespace ")
							+
							fcppt::from_std_string(
								_error.namespace_()
							)
							+
							FCPPT_TEXT(": ")
							+
							fcppt::from_std_string(
								fcppt::insert_to_std_string(
									_error
								)
							)
						);

				}
				catch(
					xsd::cxx::tree::exception<
						char
					> const &_error
				)
				{
					return
						make_error(
							fcppt::from_std_string(
								fcppt::insert_to_std_string(
									_error
								)
							)
						);
				}
				catch(
					xsd::cxx::exception const &_error
				)
				{
					return
						make_error(
							fcppt::from_std_string(
								_error.what()
							)
						);
				}
			}
		);
}

}
}
}

#endif
