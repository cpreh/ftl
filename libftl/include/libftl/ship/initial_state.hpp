#ifndef LIBFTL_SHIP_INITIAL_STATE_HPP_INCLUDED
#define LIBFTL_SHIP_INITIAL_STATE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/ship/state.hpp>
#include <libftl/ship/layout/object_fwd.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/xml/generated/blueprints_fwd.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace ship
{

LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
	libftl::error,
	libftl::ship::state
>
initial_state(
	libftl::xml::generated::blueprints::ship_blueprint const &,
	libftl::ship::layout::object const &,
	libftl::sprite::images const &
);

}
}

#endif
