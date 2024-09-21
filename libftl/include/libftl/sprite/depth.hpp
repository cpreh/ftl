#ifndef LIBFTL_SPRITE_DEPTH_HPP_INCLUDED
#define LIBFTL_SPRITE_DEPTH_HPP_INCLUDED

#include <libftl/sprite/depth_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace libftl::sprite
{
enum class depth : std::uint8_t
{
  background,
  base,
  floor,
  tile_background,
  tile,
  crew,
  something
};

}
FCPPT_ENUM_DEFINE_MAX_VALUE(libftl::sprite::depth::something);

#endif
