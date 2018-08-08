#ifndef FTL_PARSE_SHIP_OPTIONS_PARSER_HPP_INCLUDED
#define FTL_PARSE_SHIP_OPTIONS_PARSER_HPP_INCLUDED

#include <ftl/parse/ship/arguments.hpp>
#include <fcppt/options/base_unique_ptr.hpp>


namespace ftl
{
namespace parse
{
namespace ship
{

fcppt::options::base_unique_ptr<
	ftl::parse::ship::arguments
>
options_parser();

}
}
}

#endif
