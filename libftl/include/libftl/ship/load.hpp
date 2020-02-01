#ifndef LIBFTL_SHIP_LOAD_HPP_INCLUDED
#define LIBFTL_SHIP_LOAD_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/ship/resources.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace ship
{

LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
	libftl::error,
	libftl::ship::resources
>
load(
	libftl::archive::base &,
	fcppt::reference<
		libftl::blueprints::data const
	>,
	libftl::sprite::images const &,
	std::string const &
);

}
}

#endif
