#include <libftl/impl/room/draw.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/room.hpp>
#include <libftl/ship/layout/tile_coordinate.hpp>
#include <libftl/ship/layout/tile_pos.hpp>
#include <libftl/ship/layout/tile_rect.hpp>
#include <libftl/sprite/color_format.hpp>
#include <libftl/sprite/depth.hpp>
#include <libftl/sprite/depth_role.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/sprite/object.hpp>
#include <libftl/sprite/rect.hpp>
#include <libftl/sprite/size_or_texture_size.hpp>
#include <libftl/sprite/white.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <libftl/xml/ship/img.hpp>
#include <libftl/xml/ship/result.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/grid/make_min.hpp>
#include <fcppt/container/grid/make_pos_range_start_end.hpp>
#include <fcppt/container/grid/make_sup.hpp>
#include <fcppt/math/box/init_max.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/at.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
constexpr libftl::sprite::object::unit const tile_size{
    35 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
};

libftl::sprite::object
tile_background(libftl::sprite::images const &_images, libftl::sprite::object::vector const &_pos)
{
  return libftl::sprite::object{
      sge::sprite::roles::pos{} = _pos,
      sge::sprite::roles::size_or_texture_size{} =
          libftl::sprite::size_or_texture_size{
              fcppt::math::dim::fill<libftl::sprite::object::dim>(tile_size)},
      sge::sprite::roles::color{} = sge::image::color::convert<libftl::sprite::color_format>(
          sge::image::color::predef::black()),
      sge::sprite::roles::texture0{} = libftl::sprite::object::texture_type{_images.opaque()},
      libftl::sprite::depth_role{} = libftl::sprite::depth::tile_background};
}

libftl::sprite::object
tile_foreground(libftl::sprite::images const &_images, libftl::sprite::rect const &_rect)
{
  return libftl::sprite::object{
      sge::sprite::roles::pos{} = _rect.pos(),
      sge::sprite::roles::size_or_texture_size{} =
          libftl::sprite::size_or_texture_size{_rect.size()},
      sge::sprite::roles::color{} = libftl::sprite::white(),
      sge::sprite::roles::texture0{} = libftl::sprite::object::texture_type{_images.opaque()},
      libftl::sprite::depth_role{} = libftl::sprite::depth::tile};
}

libftl::sprite::rect foreground_rect(
    libftl::ship::layout::tile_pos const &_pos, libftl::ship::layout::tile_rect const &_tiles)
{
  return fcppt::math::box::init_max<libftl::sprite::rect>(
      [_pos, _tiles](auto const _index)
      {
        auto const coord(fcppt::math::vector::at<_index()>(_pos));

        libftl::sprite::object::unit const sprite_coord{fcppt::cast::to_signed(coord) * tile_size};

        libftl::sprite::object::unit const sprite_max{sprite_coord + tile_size};

        libftl::sprite::object::unit const gap{2};

        return fcppt::tuple::make(
            coord == fcppt::math::vector::at<_index()>(_tiles.pos()) ? sprite_coord + gap
                                                                     : sprite_coord,
            coord == fcppt::math::vector::at<_index()>(_tiles.max()) - 1 ? sprite_max - gap
                                                                         : sprite_max);
      });
}

std::vector<libftl::sprite::object> room_tiles(
    libftl::sprite::images const &_images,
    libftl::xml::ship::result const &_ship,
    libftl::ship::layout::tile_rect const &_tiles)
{
  return fcppt::algorithm::map_concat<std::vector<libftl::sprite::object>>(
      fcppt::container::grid::make_pos_range_start_end(
          fcppt::container::grid::make_min(_tiles.pos()),
          fcppt::container::grid::make_sup(_tiles.max())),
      [&_images, &_ship, _tiles](libftl::ship::layout::tile_pos const &_pos)
      {
        libftl::xml::ship::img const &img{fcppt::record::get<libftl::xml::labels::img>(_ship)};

        libftl::sprite::object::vector const offset{
            fcppt::cast::size<libftl::sprite::object::unit>(
                fcppt::record::get<libftl::xml::labels::x>(img.attributes_)),
            fcppt::cast::size<libftl::sprite::object::unit>(
                fcppt::record::get<libftl::xml::labels::y>(img.attributes_))};

        libftl::sprite::rect const foreground{foreground_rect(_pos, _tiles)};

        return std::vector<libftl::sprite::object>{
            tile_foreground(
                _images, libftl::sprite::rect{foreground.pos() - offset, foreground.size()}),
            tile_background(
                _images,
                fcppt::math::vector::map(
                    _pos,
                    [](libftl::ship::layout::tile_coordinate const _coord)
                        -> libftl::sprite::object::unit {
                      return libftl::sprite::object::unit{
                          fcppt::cast::to_signed(_coord) * tile_size};
                    }) -
                    offset)};
      });
}

std::vector<libftl::sprite::object> draw_tiles(
    libftl::sprite::images const &_images,
    libftl::xml::ship::result const &_ship,
    libftl::ship::layout::object const &_layout)
{
  return fcppt::algorithm::map_concat<std::vector<libftl::sprite::object>>(
      _layout.rooms_,
      [&_images, _ship](libftl::ship::layout::room const &_room)
      { return room_tiles(_images, _ship, _room.rect_); });
}

}

std::vector<libftl::sprite::object> libftl::impl::room::draw(
    libftl::sprite::images const &_images,
    libftl::xml::ship::result const &_ship,
    libftl::ship::layout::object const &_layout)
{
  return draw_tiles(_images, _ship, _layout);
}
