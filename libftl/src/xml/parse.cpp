#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/types/document.hpp>
#include <libftl/impl/xml/types/document_output.hpp>
#include <libftl/xml/parse.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iostream>
#include <regex>
#include <string>
#include <fcppt/config/external_end.hpp>


// FIXME
#include <libftl/impl/xml/types/node.hpp>

void
libftl::xml::parse(
	std::string const &_input
)
{
	std::string const removed_comments(
		std::regex_replace(
			_input,
			std::regex{
				"<!--[^]*?-->"
			},
			std::string{}
		)
	);

	libftl::impl::xml::types::document const result(
		libftl::impl::xml::parse(
			removed_comments
		)
	);

	std::cout << result << '\n';
}
