#ifndef LIBFTL_SHIP_LAYOUT_OUTPUT_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_OUTPUT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/layout/object_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>


namespace libftl
{
namespace ship
{
namespace layout
{

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	libftl::ship::layout::object const &
);

}
}
}

#endif
