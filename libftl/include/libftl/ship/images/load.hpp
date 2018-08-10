#ifndef LIBFTL_SHIP_IMAGES_LOAD_HPP_INCLUDED
#define LIBFTL_SHIP_IMAGES_LOAD_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/ship/images/name_fwd.hpp>
#include <libftl/ship/images/object.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/xml/generated/ship_fwd.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/either/object_impl.hpp>


namespace libftl
{
namespace ship
{
namespace images
{

LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
	libftl::error,
	libftl::ship::images::object
>
load(
	libftl::sprite::images &,
	fcppt::reference<
		libftl::xml::generated::ship::ship_root const
	>,
	libftl::ship::images::name const &
);

}
}
}

#endif
