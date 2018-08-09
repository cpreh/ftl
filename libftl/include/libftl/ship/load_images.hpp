#ifndef LIBFTL_SHIP_LOAD_IMAGES_HPP_INCLUDED
#define LIBFTL_SHIP_LOAD_IMAGES_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/ship/images.hpp>
#include <libftl/ship/name_fwd.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/xml/generated/ship_fwd.hpp>
#include <fcppt/either/object_impl.hpp>


namespace libftl
{
namespace ship
{

LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
	libftl::error,
	libftl::ship::images
>
load_images(
	libftl::sprite::images &,
	libftl::xml::generated::ship::ship_root const &,
	libftl::ship::name const &
);

}
}

#endif
