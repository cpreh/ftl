#include <libftl/impl/room/draw.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/room.hpp>
#include <libftl/ship/layout/tile_coordinate.hpp>
#include <libftl/ship/layout/tile_pos.hpp>
#include <libftl/ship/layout/tile_rect.hpp>
#include <libftl/sprite/depth.hpp>
#include <libftl/sprite/depth_role.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/sprite/object.hpp>
#include <libftl/sprite/size_or_texture_size.hpp>
#include <libftl/sprite/white.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/grid/make_min.hpp>
#include <fcppt/container/grid/make_pos_range_start_end.hpp>
#include <fcppt/container/grid/make_sup.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

libftl::sprite::object::unit const tile_size{
	35
};

libftl::sprite::object
tile(
	libftl::sprite::images &_images,
	libftl::sprite::object::vector const _pos
)
{
	return
		libftl::sprite::object{
			sge::sprite::roles::pos{} =
				_pos,
			sge::sprite::roles::size_or_texture_size{} =
				libftl::sprite::size_or_texture_size{
					fcppt::math::dim::fill<
						libftl::sprite::object::dim
					>(tile_size)
				},
			sge::sprite::roles::color{} =
				libftl::sprite::white(),
			sge::sprite::roles::texture0{} =
				libftl::sprite::object::texture_type{
					_images.opaque()
				},
			libftl::sprite::depth_role{} =
				libftl::sprite::depth::tile
		};
}

std::vector<
	libftl::sprite::object
>
room_tiles(
	libftl::sprite::images &_images,
	libftl::xml::generated::ship::ship_root const &_ship_root,
	libftl::ship::layout::tile_rect const _tiles
)
{
	return
		fcppt::algorithm::map<
			std::vector<
				libftl::sprite::object
			>
		>(
			fcppt::container::grid::make_pos_range_start_end(
				fcppt::container::grid::make_min(
					_tiles.pos()
				),
				fcppt::container::grid::make_sup(
					_tiles.max()
				)
			),
			[&_images,&_ship_root]
			(libftl::ship::layout::tile_pos const _pos)
			{
				return
					tile(
						_images,
						fcppt::math::vector::map(
							_pos,
							[](libftl::ship::layout::tile_coordinate const _coord)
							-> libftl::sprite::object::unit
							{
								return
									libftl::sprite::object::unit{
										fcppt::cast::to_signed(
											_coord
										)
										*
										tile_size
									};
							}
						)
						-
						libftl::sprite::object::vector{
							fcppt::cast::size<
								libftl::sprite::object::unit
							>(
								_ship_root.img().x()
							),
							fcppt::cast::size<
								libftl::sprite::object::unit
							>(
								_ship_root.img().y()
							)
						}
					);
			}
		);
}

std::vector<
	libftl::sprite::object
>
draw_tiles(
	libftl::sprite::images &_images,
	libftl::xml::generated::ship::ship_root const &_ship_root,
	libftl::ship::layout::object const &_layout
)
{
	return
		fcppt::algorithm::map_concat<
			std::vector<
				libftl::sprite::object
			>
		>(
			_layout.rooms_,
			[&_images,_ship_root]
			(libftl::ship::layout::room const &_room)
			{
				return
					room_tiles(
						_images,
						_ship_root,
						_room.rect_
					);
			}
		);
}

}

std::vector<
	libftl::sprite::object
>
libftl::impl::room::draw(
	libftl::sprite::images &_images,
	libftl::xml::generated::ship::ship_root const &_ship_root,
	libftl::ship::layout::object const &_layout
)
{
	return
		// TODO!
		draw_tiles(
			_images, _ship_root, _layout
		);
}
