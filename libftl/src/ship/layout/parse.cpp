#include <libftl/error.hpp>
#include <libftl/ship/layout/door.hpp>
#include <libftl/ship/layout/ellipse.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/parse.hpp>
#include <libftl/ship/layout/room.hpp>
#include <libftl/ship/layout/room_id.hpp>
#include <libftl/ship/layout/tile_coordinate.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/value_type.hpp>
#include <fcppt/parse/as_struct.hpp>
#include <fcppt/parse/char_set.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/parse/grammar.hpp>
#include <fcppt/parse/grammar_parse_stream.hpp>
#include <fcppt/parse/int.hpp>
#include <fcppt/parse/make_skipper.hpp>
#include <fcppt/parse/string.hpp>
#include <fcppt/parse/operators/optional.hpp>
#include <fcppt/parse/operators/repetition.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <type_traits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::make_signed_t<
	libftl::ship::layout::room_id::value_type
>
room_id_signed;

struct room
{
	libftl::ship::layout::room_id::value_type id_;

	libftl::ship::layout::tile_coordinate x_;

	libftl::ship::layout::tile_coordinate y_;

	libftl::ship::layout::tile_coordinate w_;

	libftl::ship::layout::tile_coordinate h_;
};

struct door
{
	libftl::ship::layout::tile_coordinate x_;

	libftl::ship::layout::tile_coordinate y_;

	room_id_signed left_top_;

	room_id_signed bottom_right_;

	int vertical_;
};

struct layout
{
	libftl::ship::layout::object::offset_vector::value_type offset_x_;

	libftl::ship::layout::object::offset_vector::value_type offset_y_;

	int vertical_;

	fcppt::optional::object<int> horizontal_;

	libftl::ship::layout::ellipse::value_type::value_type ellipse_x_;

	libftl::ship::layout::ellipse::value_type::value_type ellipse_y_;

	libftl::ship::layout::ellipse::value_type::value_type ellipse_w_;

	libftl::ship::layout::ellipse::value_type::value_type ellipse_h_;

	std::vector<room> rooms_;

	std::vector<door> doors_;
};

}

namespace
{

auto
eol()
{
	return
		fcppt::parse::make_skipper(
			fcppt::parse::char_set{'\r', '\n'}
		);
}

typedef
fcppt::parse::int_<
	fcppt::optional::value_type<
		libftl::ship::layout::object::offset_vector::value_type
	>
>
offset_int;

typedef
fcppt::parse::int_<
	libftl::ship::layout::ellipse::value_type::value_type
>
ellipse_int;

typedef
fcppt::parse::int_<
	libftl::ship::layout::room_id::value_type
>
room_id_int;

typedef
fcppt::parse::int_<
	room_id_signed
>
room_id_signed_int;

typedef
fcppt::parse::int_<
	libftl::ship::layout::tile_coordinate
>
tile_coordinate_int;

class grammar
:
public
	fcppt::parse::grammar<
		::layout,
		char,
		decltype(
			eol()
		)
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar()
	:
		grammar::grammar_base(
			fcppt::make_cref(
				this->layout_
			),
			eol()
		),
		room_{
			this->make_base(
				fcppt::parse::as_struct<
					::room
				>(
					fcppt::parse::string{"ROOM"}
					>>
					room_id_int{}
					>>
					tile_coordinate_int{}
					>>
					tile_coordinate_int{}
					>>
					tile_coordinate_int{}
					>>
					tile_coordinate_int{}
				)
			)
		},
		door_{
			this->make_base(
				fcppt::parse::as_struct<
					::door
				>(
					fcppt::parse::string{"DOOR"}
					>>
					tile_coordinate_int{}
					>>
					tile_coordinate_int{}
					>>
					room_id_signed_int{}
					>>
					room_id_signed_int{}
					>>
					fcppt::parse::int_<int>{}
				)
			)
		},
		layout_{
			this->make_base(
				fcppt::parse::as_struct<
					::layout
				>(
					-(
						fcppt::parse::string{"X_OFFSET"}
						>>
						offset_int{}
					)
					>>
					-(
						fcppt::parse::string{"Y_OFFSET"}
						>>
						offset_int{}
					)
					>>
					fcppt::parse::string{"VERTICAL"}
					>>
					fcppt::parse::int_<int>{}
					>>
					-(
						fcppt::parse::string{"HORIZONTAL"}
						>>
						fcppt::parse::int_<int>{}
					)
					>>
					fcppt::parse::string{"ELLIPSE"}
					>>
					ellipse_int{}
					>>
					ellipse_int{}
					>>
					ellipse_int{}
					>>
					ellipse_int{}
					>>
					*fcppt::make_cref(
						this->room_
					)
					>>
					*fcppt::make_cref(
						this->door_
					)
				)
			)
		}
	{
	}

	~grammar()
	{
	}
public:
	base_type<
		::room
	>
	room_;

	base_type<
		::door
	>
	door_;

	base_type<
		::layout
	>
	layout_;
};

bool
translate_bool(
	int const _value
)
{
	switch(
		_value
	)
	{
	case 0:
		return
			false;
	case 1:
		return
			true;
	}

	throw
		fcppt::exception{
			FCPPT_TEXT("Invalid boolean value ")
			+
			fcppt::output_to_fcppt_string(
				_value
			)
		};
}

libftl::ship::layout::door::optional_room_id
translate_optional_door_room(
	room_id_signed const _id
)
{
	if(
		_id
		<
		-1
	)
		throw
			fcppt::exception{
				FCPPT_TEXT("Invalid door room ")
				+
				fcppt::output_to_fcppt_string(
					_id
				)
			};

	return
		fcppt::optional::make_if(
			_id
			>=
			0,
			[
				_id
			]{
				return
					libftl::ship::layout::room_id{
						fcppt::cast::to_unsigned(
							_id
						)
					};
			}
		);
}

libftl::ship::layout::object
translate_result(
	layout const &_layout
)
{
	return
		libftl::ship::layout::object{
			libftl::ship::layout::object::offset_vector{
				_layout.offset_x_,
				_layout.offset_y_
			},
			libftl::ship::layout::object::vertical{
				_layout.vertical_
			},
			libftl::ship::layout::object::horizontal{
				_layout.horizontal_
			},
			libftl::ship::layout::ellipse{
				libftl::ship::layout::ellipse::value_type{
					libftl::ship::layout::ellipse::value_type::vector{
						_layout.ellipse_x_,
						_layout.ellipse_y_
					},
					libftl::ship::layout::ellipse::value_type::dim{
						_layout.ellipse_w_,
						_layout.ellipse_h_
					}
				}
			},
			fcppt::algorithm::map<
				libftl::ship::layout::object::room_list
			>(
				_layout.rooms_,
				[](
					room const &_room
				)
				{
					return
						libftl::ship::layout::room{
							libftl::ship::layout::room_id{
								_room.id_
							},
							libftl::ship::layout::tile_rect{
								libftl::ship::layout::tile_rect::vector{
									libftl::ship::layout::tile_coordinate{
										_room.x_
									},
									libftl::ship::layout::tile_coordinate{
										_room.y_
									}
								},
								libftl::ship::layout::tile_rect::dim{
									libftl::ship::layout::tile_coordinate{
										_room.w_
									},
									libftl::ship::layout::tile_coordinate{
										_room.h_
									}
								}
							}
						};
				}
			),
			fcppt::algorithm::map<
				libftl::ship::layout::object::door_list
			>(
				_layout.doors_,
				[](
					door const &_door
				)
				{
					return
						libftl::ship::layout::door{
							libftl::ship::layout::tile_pos{
								libftl::ship::layout::tile_coordinate{
									_door.x_
								},
								libftl::ship::layout::tile_coordinate{
									_door.y_
								}
							},
							libftl::ship::layout::door::left_top_room{
								translate_optional_door_room(
									_door.left_top_
								)
							},
							libftl::ship::layout::door::bottom_right_room{
								translate_optional_door_room(
									_door.bottom_right_
								)
							},
							libftl::ship::layout::door::vertical(
								translate_bool(
									_door.vertical_
								)
							)
						};
				}
			)
		};
}

typedef
fcppt::either::object<
	libftl::error,
	libftl::ship::layout::object
>
result_type;

}

fcppt::either::object<
	libftl::error,
	libftl::ship::layout::object
>
libftl::ship::layout::parse(
	std::istream &_stream
)
try
{
	_stream.unsetf(
		std::ios_base::skipws
	);

	return
		fcppt::either::map_failure(
			fcppt::either::map(
				fcppt::parse::grammar_parse_stream(
					_stream,
					grammar{}
				),
				translate_result
			),
			[](
				fcppt::parse::error<
					char
				> &&_error
			)
			{
				return
					libftl::error{
						FCPPT_TEXT("Parsing failed: ")
						+
						fcppt::from_std_string(
							std::move(
								_error.get()
							)
						)
					};
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	return
		result_type{
			libftl::error{
				_error.string()
			}
		};
}
