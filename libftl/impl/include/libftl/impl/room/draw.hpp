#ifndef LIBFTL_IMPL_ROOM_DRAW_HPP_INCLUDED
#define LIBFTL_IMPL_ROOM_DRAW_HPP_INCLUDED

#include <libftl/ship/layout/object_fwd.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/sprite/object.hpp>
#include <libftl/xml/ship/result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::room
{
[[nodiscard]] std::vector<libftl::sprite::object> draw(
    libftl::sprite::images const &,
    libftl::xml::ship::result const &,
    libftl::ship::layout::object const &);
}

#endif
