#ifndef FTL_PARSE_SHIP_MAIN_HPP_INCLUDED
#define FTL_PARSE_SHIP_MAIN_HPP_INCLUDED

#include <ftl/parse/ship/arguments_fwd.hpp>
#include <libftl/error.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <fcppt/either/error.hpp>


namespace ftl
{
namespace parse
{
namespace ship
{

fcppt::either::error<
	libftl::error
>
main(
	libftl::archive::base &,
	ftl::parse::ship::arguments const &
);

}
}
}

#endif
