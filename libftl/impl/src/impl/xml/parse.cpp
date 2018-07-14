#include <libftl/archive/entry_output.hpp>
#include <libftl/archive/extract.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/impl/xml/encoding.hpp>
#include <libftl/impl/xml/grammar_impl.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/remove_comments.hpp>
#include <libftl/impl/xml/types/document.hpp>
#include <libftl/xml/error.hpp>
#include <sge/parse/error_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/identity.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::either::object<
	libftl::xml::error,
	libftl::impl::xml::types::document
>
parse_string(
	std::string const &_input
)
{
	libftl::impl::xml::grammar<
		std::string::const_iterator
	>
	parser{};

	std::string::const_iterator begin{
		_input.begin()
	};

	libftl::impl::xml::types::document result{};

	boost::spirit::qi::phrase_parse(
		begin,
		_input.end(),
		parser,
		libftl::impl::xml::encoding::space,
		result
	);

	return
		fcppt::optional::maybe(
			parser.error_string(),
			[
				begin,
				&result,
				&_input
			]{
				return
					begin
					==
					_input.end()
					?
						fcppt::either::make_success<
							libftl::xml::error
						>(
							std::move(
								result
							)
						)
					:
						fcppt::either::make_failure<
							libftl::impl::xml::types::document
						>(
							libftl::xml::error{
								fcppt::from_std_string(
									std::string{
										begin,
										_input.end()
									}
								)
							}
						)
					;
			},
			[](
				sge::parse::error_string const &_error
			)
			{
				return
					fcppt::either::make_failure<
						libftl::impl::xml::types::document
					>(
						libftl::xml::error{
							_error.get()
						}
					);
			}
		);

}

}

fcppt::either::object<
	libftl::xml::error,
	libftl::impl::xml::types::document
>
libftl::impl::xml::parse(
	libftl::archive::file const &_file
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
						libftl::xml::error{
							FCPPT_TEXT("Failed to read ")
							+
							fcppt::output_to_fcppt_string(
								_file.entry_
							)
						};
				}
			),
			[](
				fcppt::io::buffer &&_buffer
			)
			{
				return
					parse_string(
						libftl::impl::xml::remove_comments(
							fcppt::algorithm::map<
								std::string
							>(
								_buffer,
								fcppt::identity{}
							)
						)
					);
			}
		);
}
