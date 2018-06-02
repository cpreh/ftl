#include <libftl/impl/xml/encoding.hpp>
#include <libftl/impl/xml/grammar_impl.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/types/document.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


#include <sge/parse/error_string.hpp>
#include <fcppt/optional/maybe.hpp>
#include <iostream>

libftl::impl::xml::types::document
libftl::impl::xml::parse(
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

	fcppt::optional::maybe(
		parser.error_string(),
		[
			&begin,
			&_input
		]{
			// TODO: Install erroer handler and return either
			if(
				begin
				!=
				_input.end()
			)
				std::cout <<
					"FAILED TO PARSE\n"
					<<
					std::string{
						begin,
						_input.end()
					}
					<<
					"\n";


		},
		[](
			sge::parse::error_string const &_error
		)
		{
			std::cout << _error.get() << '\n';
		}
	);

	return
		result;
}
