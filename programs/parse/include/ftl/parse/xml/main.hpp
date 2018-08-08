#ifndef FTL_PARSE_XML_MAIN_HPP_INCLUDED
#define FTL_PARSE_XML_MAIN_HPP_INCLUDED

#include <ftl/parse/xml/arguments_fwd.hpp>
#include <libftl/error.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <fcppt/either/error.hpp>


namespace ftl
{
namespace parse
{
namespace xml
{

fcppt::either::error<
	libftl::error
>
main(
	libftl::archive::base &,
	ftl::parse::xml::arguments const &
);

}
}
}

#endif
