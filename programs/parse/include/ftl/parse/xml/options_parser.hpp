#ifndef FTL_PARSE_XML_OPTIONS_PARSER_HPP_INCLUDED
#define FTL_PARSE_XML_OPTIONS_PARSER_HPP_INCLUDED

#include <ftl/parse/xml/arguments.hpp>
#include <fcppt/options/base_unique_ptr.hpp>

namespace ftl::parse::xml
{
fcppt::options::base_unique_ptr<ftl::parse::xml::arguments> options_parser();

}

#endif
