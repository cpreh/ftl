#ifndef LIBFTL_SHIP_PARSE_LAYOUT_HPP_INCLUDED
#define LIBFTL_SHIP_PARSE_LAYOUT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/layout.hpp>
#include <fcppt/string.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace ship
{

LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
	fcppt::string,
	libftl::ship::layout
>
parse_layout(
	std::istream &
);

}
}

#endif