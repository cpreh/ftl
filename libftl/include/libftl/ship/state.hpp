#ifndef LIBFTL_SHIP_STATE_HPP_INCLUDED
#define LIBFTL_SHIP_STATE_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/room/state.hpp>
#include <libftl/ship/state_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace ship
{

struct state
{
	LIBFTL_DETAIL_SYMBOL
	explicit
	state(
		std::vector<
			libftl::room::state
		> &&
	);

	std::vector<
		libftl::room::state
	> rooms_;
};

}
}

#endif
