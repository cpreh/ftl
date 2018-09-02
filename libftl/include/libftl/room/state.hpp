#ifndef LIBFTL_ROOM_STATE_HPP_INCLUDED
#define LIBFTL_ROOM_STATE_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/room/state_fwd.hpp>
#include <libftl/room/system.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace libftl
{
namespace room
{

struct state
{
	LIBFTL_DETAIL_SYMBOL
	explicit
	state(
		fcppt::optional::object<
			libftl::room::system
		> &&
	);

	fcppt::optional::object<
		libftl::room::system
	> system_;

	// TODO: fire, oxygen, breach, etc.
};

}
}

#endif
