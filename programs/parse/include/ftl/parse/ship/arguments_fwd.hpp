#ifndef FTL_PARSE_SHIP_ARGUMENTS_FWD_HPP_INCLUDED
#define FTL_PARSE_SHIP_ARGUMENTS_FWD_HPP_INCLUDED

#include <ftl/parse/path_label.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/record/variadic_fwd.hpp>


namespace ftl
{
namespace parse
{
namespace ship
{

typedef
fcppt::record::variadic<
	fcppt::record::element<
		ftl::parse::path_label,
		libftl::archive::path
	>
>
arguments;

}
}
}

#endif
