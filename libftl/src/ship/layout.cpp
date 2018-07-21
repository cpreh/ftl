#include <libftl/ship/ellipse.hpp>
#include <libftl/ship/layout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


libftl::ship::layout::layout(
	offset_vector const _offset,
	vertical const _vertical,
	horizontal const _horizontal,
	libftl::ship::ellipse const _ellipse,
	room_list &&_rooms,
	door_list &&_doors
)
:
	offset_{
		_offset
	},
	vertical_{
		_vertical
	},
	horizontal_{
		_horizontal
	},
	ellipse_{
		_ellipse
	},
	rooms_{
		std::move(
			_rooms
		)
	},
	doors_{
		std::move(
			_doors
		)
	}
{
}
