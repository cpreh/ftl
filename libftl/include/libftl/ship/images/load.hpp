#ifndef LIBFTL_SHIP_IMAGES_LOAD_HPP_INCLUDED
#define LIBFTL_SHIP_IMAGES_LOAD_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/images/error.hpp>
#include <libftl/ship/images/name_fwd.hpp>
#include <libftl/ship/images/object.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <libftl/xml/ship/result.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/either/object_impl.hpp>

namespace libftl::ship::images
{
[[nodiscard]] LIBFTL_DETAIL_SYMBOL
fcppt::either::object<libftl::ship::images::error, libftl::ship::images::object>
load(
    libftl::sprite::images const &,
    libftl::xml::blueprints::ship const &,
    fcppt::reference<libftl::xml::ship::result const>,
    libftl::ship::images::name const &);
}

#endif
