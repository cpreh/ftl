#include <libftl/ship/door.hpp>
#include <libftl/ship/ellipse.hpp>
#include <libftl/ship/layout.hpp>
#include <libftl/ship/parse_layout.hpp>
#include <libftl/ship/room.hpp>
#include <libftl/ship/room_id.hpp>
#include <libftl/ship/tile_coordinate.hpp>
#include <sge/parse/install_error_handler.hpp>
#include <sge/parse/make_result.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_eol.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_int.hpp>
#include <boost/spirit/include/qi_kleene.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_sequence.hpp>
#include <boost/spirit/include/qi_rule.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <ios>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::make_signed<
	libftl::ship::room_id::value_type
>::type
room_id_signed;

struct room
{
	libftl::ship::room_id::value_type id_;

	libftl::ship::tile_coordinate::value_type x_;

	libftl::ship::tile_coordinate::value_type y_;

	libftl::ship::tile_coordinate::value_type w_;

	libftl::ship::tile_coordinate::value_type h_;
};

struct door
{
	libftl::ship::tile_coordinate::value_type x_;

	libftl::ship::tile_coordinate::value_type y_;

	room_id_signed left_top_;

	room_id_signed bottom_right_;

	int vertical_;
};

struct layout
{
	libftl::ship::layout::offset_vector::value_type x_;

	libftl::ship::layout::offset_vector::value_type y_;

	int vertical_;

	libftl::ship::ellipse::value_type::value_type ellipse_x_;

	libftl::ship::ellipse::value_type::value_type ellipse_y_;

	libftl::ship::ellipse::value_type::value_type ellipse_w_;

	libftl::ship::ellipse::value_type::value_type ellipse_h_;

	std::vector<
		room
	>
	rooms_;

	std::vector<
		door
	>
	doors_;
};

}

FCPPT_PP_PUSH_WARNING
#if defined(FCPPT_CONFIG_CLANG_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wunused-member-function)
#endif

BOOST_FUSION_ADAPT_STRUCT(
	room,
	(libftl::ship::room_id::value_type, id_)
	(libftl::ship::tile_coordinate::value_type, x_)
	(libftl::ship::tile_coordinate::value_type, y_)
	(libftl::ship::tile_coordinate::value_type, w_)
	(libftl::ship::tile_coordinate::value_type, h_)
)

BOOST_FUSION_ADAPT_STRUCT(
	door,
	(libftl::ship::tile_coordinate::value_type, x_)
	(libftl::ship::tile_coordinate::value_type, y_)
	(room_id_signed, left_top_)
	(room_id_signed, bottom_right_)
	(int, vertical_)
)

BOOST_FUSION_ADAPT_STRUCT(
	layout,
	(libftl::ship::layout::offset_vector::value_type, x_)
	(libftl::ship::layout::offset_vector::value_type, y_)
	(int, vertical_)
	(libftl::ship::ellipse::value_type::value_type, ellipse_x_)
	(libftl::ship::ellipse::value_type::value_type, ellipse_y_)
	(libftl::ship::ellipse::value_type::value_type, ellipse_w_)
	(libftl::ship::ellipse::value_type::value_type, ellipse_h_)
	(std::vector<room>, rooms_)
	(std::vector<door>, doors_)
)

FCPPT_PP_POP_WARNING

namespace
{

template<
	typename In
>
class grammar final
:
	public
	boost::spirit::qi::grammar<
		In,
		::layout()
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar()
	:
		grammar::base_type(
			layout_
		),
		offset_int_{},
		ellipse_int_{},
		room_id_int_{},
		room_id_signed_int_{},
		tile_coordinate_int_{},
		room_{},
		door_{},
		layout_{},
		error_string_{}
	{
		using
		boost::spirit::eol;

		namespace
		qi
		=
		boost::spirit::qi;

		room_ %=
			qi::lit("ROOM") > eol
			>
			room_id_int_ > eol
			>
			tile_coordinate_int_ > eol
			>
			tile_coordinate_int_ > eol
			>
			tile_coordinate_int_ > eol
			>
			tile_coordinate_int_ > eol;

		door_ %=
			qi::lit("DOOR") > eol
			>
			tile_coordinate_int_ > eol
			>
			tile_coordinate_int_ > eol
			>
			room_id_signed_int_ > eol
			>
			room_id_signed_int_ > eol
			>
			qi::int_ > eol;

		layout_ %=
			qi::lit("X_OFFSET") > eol
			>
			offset_int_ > eol
			>
			qi::lit("Y_OFFSET") > eol
			>
			offset_int_ > eol
			>
			qi::lit("VERTICAL") > eol
			>
			qi::int_ > eol
			>
			qi::lit("ELLIPSE") > eol
			>
			ellipse_int_ > eol
			>
			ellipse_int_ > eol
			>
			ellipse_int_ > eol
			>
			ellipse_int_ > eol
			>
			*room_
			>
			*door_;

		sge::parse::install_error_handler(
			fcppt::make_ref(
				layout_
			),
			fcppt::make_ref(
				error_string_
			)
		);
	}

	~grammar()
	{
	}

	sge::parse::optional_error_string const &
	error_string() const
	{
		return
			error_string_;
	}
public:
	boost::spirit::qi::int_parser<
		libftl::ship::layout::offset_vector::value_type
	>
	offset_int_;

	boost::spirit::qi::int_parser<
		libftl::ship::ellipse::value_type::value_type
	>
	ellipse_int_;

	boost::spirit::qi::int_parser<
		libftl::ship::room_id::value_type
	>
	room_id_int_;

	boost::spirit::qi::int_parser<
		room_id_signed
	>
	room_id_signed_int_;

	boost::spirit::qi::int_parser<
		libftl::ship::tile_coordinate::value_type
	>
	tile_coordinate_int_;

	boost::spirit::qi::rule<
		In,
		::room()
	>
	room_;

	boost::spirit::qi::rule<
		In,
		::door()
	>
	door_;

	boost::spirit::qi::rule<
		In,
		::layout()
	>
	layout_;

	sge::parse::optional_error_string error_string_;
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
	};

	throw
		fcppt::exception{
			FCPPT_TEXT("Invalid boolean value ")
			+
			fcppt::insert_to_fcppt_string(
				_value
			)
		};
}

libftl::ship::door::optional_room_id
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
				fcppt::insert_to_fcppt_string(
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
					libftl::ship::room_id{
						fcppt::cast::to_unsigned(
							_id
						)
					};
			}
		);
}

libftl::ship::layout
translate_result(
	layout const &_layout
)
{
	return
		libftl::ship::layout{
			libftl::ship::layout::offset_vector{
				_layout.x_,
				_layout.y_
			},
			libftl::ship::layout::vertical{
				translate_bool(
					_layout.vertical_
				)
			},
			libftl::ship::ellipse{
				libftl::ship::ellipse::value_type{
					libftl::ship::ellipse::value_type::vector{
						_layout.ellipse_x_,
						_layout.ellipse_y_
					},
					libftl::ship::ellipse::value_type::dim{
						_layout.ellipse_w_,
						_layout.ellipse_h_
					}
				}
			},
			fcppt::algorithm::map<
				libftl::ship::layout::room_list
			>(
				_layout.rooms_,
				[](
					room const &_room
				)
				{
					return
						libftl::ship::room{
							libftl::ship::room_id{
								_room.id_
							},
							libftl::ship::tile_rect{
								libftl::ship::tile_rect::vector{
									libftl::ship::tile_coordinate{
										_room.x_
									},
									libftl::ship::tile_coordinate{
										_room.y_
									}
								},
								libftl::ship::tile_rect::dim{
									libftl::ship::tile_coordinate{
										_room.w_
									},
									libftl::ship::tile_coordinate{
										_room.h_
									}
								}
							}
						};
				}
			),
			fcppt::algorithm::map<
				libftl::ship::layout::door_list
			>(
				_layout.doors_,
				[](
					door const &_door
				)
				{
					return
						libftl::ship::door{
							libftl::ship::tile_pos{
								libftl::ship::tile_coordinate{
									_door.x_
								},
								libftl::ship::tile_coordinate{
									_door.y_
								}
							},
							libftl::ship::door::left_top_room{
								translate_optional_door_room(
									_door.left_top_
								)
							},
							libftl::ship::door::bottom_right_room{
								translate_optional_door_room(
									_door.bottom_right_
								)
							},
							libftl::ship::door::vertical(
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
	fcppt::string,
	libftl::ship::layout
>
result_type;

}

fcppt::either::object<
	fcppt::string,
	libftl::ship::layout
>
libftl::ship::parse_layout(
	std::istream &_stream
)
try
{
	_stream.unsetf(
		std::ios_base::skipws
	);

	boost::spirit::istream_iterator begin(
		_stream
	);

	boost::spirit::istream_iterator end{};

	grammar<
		boost::spirit::istream_iterator
	>
	parser{};

	::layout result_layout{};

	sge::parse::result const result{
		sge::parse::make_result(
			boost::spirit::qi::parse(
				begin,
				end,
				parser,
				result_layout
			),
			fcppt::make_cref(
				begin
			),
			end,
			parser
		)
	};

	return
		result.result_code()
		==
		sge::parse::result_code::ok
		?
			result_type{
				translate_result(
					result_layout
				)
			}
		:
			result_type{
				fcppt::optional::from(
					fcppt::optional::map(
						result.error_string(),
						[](
							sge::parse::error_string const &_error
						)
						->
						fcppt::string
						{
							return
								_error.get();
						}
					),
					[]{
						return
							fcppt::string{
								FCPPT_TEXT("Unknown error")
							};
					}
				)
			}
		;
}
catch(
	fcppt::exception const &_error
)
{
	return
		result_type{
			_error.string()
		};
}
