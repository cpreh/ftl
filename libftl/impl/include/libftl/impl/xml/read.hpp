#ifndef LIBFTL_IMPL_XML_READ_HPP_INCLUDED
#define LIBFTL_IMPL_XML_READ_HPP_INCLUDED

#include <libftl/archive/entry_output.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/archive/extract.hpp>
#include <libftl/impl/xml/make_closing_tag.hpp>
#include <libftl/impl/xml/make_opening_tag.hpp>
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
#include <fcppt/algorithm/map.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/exceptions.hxx>
#include <xsd/cxx/tree/exceptions.hxx>
#include <memory>
#include <regex>
#include <string>
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
	libftl::impl::xml::root_name const &_root_name
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
				&_file
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

				std::regex const regex{
					"<!--[^]*?-->"
				};

				std::string const replaced{
					std::regex_replace(
						input,
						regex,
						""
					)
				};

				typedef
				libftl::xml::result<
					Result
				>
				result_type;

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
					xsd::cxx::tree::exception<
						char
					> const &_error
				)
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
							fcppt::from_std_string(
								fcppt::insert_to_std_string(
									_error
								)
							)
						};
				}
				catch(
					xsd::cxx::exception const &_error
				)
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
							fcppt::from_std_string(
								_error.what()
							)
						};
				}
			}
		);
}

}
}
}

#endif
