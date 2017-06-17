#include <libftl/ship/door.hpp>
#include <libftl/ship/layout.hpp>
#include <libftl/ship/layout_output.hpp>
#include <libftl/ship/room.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/optional/output.hpp>


namespace libftl
{
namespace ship
{

fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	libftl::ship::room const &
);

fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &_stream,
	libftl::ship::room const &_room
)
{
	return
		_stream
		<<
		FCPPT_TEXT("id: ")
		<<
		_room.id_
		<<
		FCPPT_TEXT("tile_rect: ")
		<<
		_room.rect_;
}

fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	libftl::ship::door const &
);

fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &_stream,
	libftl::ship::door const &_door
)
{
	return
		_stream
		<<
		FCPPT_TEXT("pos: ")
		<<
		_door.pos_
		<<
		FCPPT_TEXT("left_top_room: ")
		<<
		_door.left_top_room_
		<<
		FCPPT_TEXT("bottom_right_room: ")
		<<
		_door.bottom_right_room_
		<<
		FCPPT_TEXT("vertical: ")
		<<
		_door.vertical_;
}

}
}

fcppt::io::ostream &
libftl::ship::operator<<(
	fcppt::io::ostream &_stream,
	libftl::ship::layout const &_layout
)
{
	return
		_stream
		<<
		std::boolalpha
		<<
		FCPPT_TEXT("offset: ")
		<<
		_layout.offset_
		<<
		FCPPT_TEXT(", vertical: ")
		<<
		_layout.vertical_
		<<
		FCPPT_TEXT(", ellipse: ")
		<<
		_layout.ellipse_
		<<
		FCPPT_TEXT(", rooms: ")
		<<
		fcppt::container::output(
			_layout.rooms_
		)
		<<
		FCPPT_TEXT(", doors: ")
		<<
		fcppt::container::output(
			_layout.doors_
		);

}
