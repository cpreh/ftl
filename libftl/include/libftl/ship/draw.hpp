#ifndef LIBFTL_SHIP_DRAW_HPP_INCLUDED
#define LIBFTL_SHIP_DRAW_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/resources_fwd.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/sprite/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace ship
{
LIBFTL_DETAIL_SYMBOL
std::vector<libftl::sprite::object>
draw(libftl::sprite::images const &, libftl::ship::resources const &);

}
}

#endif
