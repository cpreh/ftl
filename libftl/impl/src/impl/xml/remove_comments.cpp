#include <libftl/impl/xml/remove_comments.hpp>
#include <fcppt/config/external_begin.hpp>
#include <regex>
#include <string>
#include <fcppt/config/external_end.hpp>


std::string
libftl::impl::xml::remove_comments(
	std::string const &_input
)
{
	return
		std::regex_replace(
			_input,
			std::regex{
				"<!--[^]*?-->"
			},
			std::string{}
		);
}
