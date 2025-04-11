#include <libftl/ship/layout/door.hpp>
#include <libftl/ship/layout/ellipse.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/parse.hpp>
#include <libftl/ship/layout/parse_error.hpp>
#include <libftl/ship/layout/room.hpp>
#include <libftl/ship/layout/room_id.hpp>
#include <libftl/ship/layout/room_id_signed.hpp>
#include <libftl/ship/layout/tile_coordinate.hpp>
#include <libftl/ship/layout/tile_pos.hpp>
#include <libftl/ship/layout/tile_rect.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/construct.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/value_type.hpp>
#include <fcppt/parse/as_struct.hpp>
#include <fcppt/parse/grammar.hpp>
#include <fcppt/parse/grammar_parse_stream.hpp>
#include <fcppt/parse/int.hpp>
#include <fcppt/parse/parse_stream_error.hpp>
#include <fcppt/parse/string.hpp>
#include <fcppt/parse/uint.hpp>
#include <fcppt/parse/operators/optional.hpp>
#include <fcppt/parse/operators/repetition.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/parse/skipper/char_set.hpp>
#include <fcppt/parse/skipper/operators/repetition.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <iosfwd>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
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

  libftl::ship::layout::room_id_signed left_top_;

  libftl::ship::layout::room_id_signed bottom_right_;

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
auto eol() { return *fcppt::parse::skipper::char_set{'\r', '\n'}; }

using offset_int = fcppt::parse::uint<
    fcppt::optional::value_type<libftl::ship::layout::object::offset_vector::value_type>>;

using ellipse_int = fcppt::parse::int_<libftl::ship::layout::ellipse::value_type::value_type>;

using room_id_int = fcppt::parse::uint<libftl::ship::layout::room_id::value_type>;

using room_id_signed_int = fcppt::parse::int_<libftl::ship::layout::room_id_signed>;

using tile_coordinate_int = fcppt::parse::uint<libftl::ship::layout::tile_coordinate>;

class grammar : public fcppt::parse::grammar<::layout, char, decltype(eol())>
{
  FCPPT_NONMOVABLE(grammar);

public:
  grammar()
      : grammar::grammar_base{fcppt::make_cref(this->layout_), eol()},
        room_{grammar_base::make_base(fcppt::parse::as_struct<::room>(
            fcppt::parse::string{"ROOM"} >> room_id_int{} >> tile_coordinate_int{} >>
            tile_coordinate_int{} >> tile_coordinate_int{} >> tile_coordinate_int{}))},
        door_{grammar_base::make_base(fcppt::parse::as_struct<::door>(
            fcppt::parse::string{"DOOR"} >> tile_coordinate_int{} >> tile_coordinate_int{} >>
            room_id_signed_int{} >> room_id_signed_int{} >> fcppt::parse::int_<int>{}))},
        layout_{grammar_base::make_base(fcppt::parse::as_struct<::layout>(
            -(fcppt::parse::string{"X_OFFSET"} >> offset_int{}) >>
            -(fcppt::parse::string{"Y_OFFSET"} >> offset_int{}) >>
            fcppt::parse::string{"VERTICAL"} >> fcppt::parse::int_<int>{} >>
            -(fcppt::parse::string{"HORIZONTAL"} >> fcppt::parse::int_<int>{}) >>
            fcppt::parse::string{"ELLIPSE"} >> ellipse_int{} >> ellipse_int{} >> ellipse_int{} >>
            ellipse_int{} >> *fcppt::make_cref(this->room_) >> *fcppt::make_cref(this->door_)))}
  {
  }

  ~grammar() = default;

private:
  base_type<::room> room_;

  base_type<::door> door_;

  base_type<::layout> layout_;
};

fcppt::either::object<libftl::ship::layout::parse_error::invalid_bool, bool>
translate_bool(int const _value)
{
  switch (_value)
  {
  case 0:
    return fcppt::either::make_success<libftl::ship::layout::parse_error::invalid_bool>(false);
  case 1:
    return fcppt::either::make_success<libftl::ship::layout::parse_error::invalid_bool>(true);
  default:
    break;
  }

  return fcppt::either::make_failure<bool>(libftl::ship::layout::parse_error::invalid_bool{_value});
}

fcppt::either::object<
    libftl::ship::layout::parse_error::invalid_room_id,
    libftl::ship::layout::door::optional_room_id>
translate_optional_door_room(libftl::ship::layout::room_id_signed const _id)
{
  return fcppt::either::construct(
      _id >= -1,
      [_id]
      {
        return fcppt::optional::make_if(
            _id >= 0,
            [_id] { return libftl::ship::layout::room_id{fcppt::cast::to_unsigned(_id)}; });
      },
      [_id] { return libftl::ship::layout::parse_error::invalid_room_id{_id}; });
}

fcppt::either::object<libftl::ship::layout::parse_error, libftl::ship::layout::object>
translate_result(layout const &_layout)
{
  return fcppt::either::map(
      // TODO(philipp): Accumulate all errors?
      fcppt::either::sequence<fcppt::either::object<
          libftl::ship::layout::parse_error,
          libftl::ship::layout::object::door_list>>(
          fcppt::algorithm::map<std::vector<fcppt::either::object<
              libftl::ship::layout::parse_error,
              libftl::ship::layout::door>>>(
              _layout.doors_,
              [](door const &_door)
              {
                auto const convert_room_error{
                    [](libftl::ship::layout::parse_error::invalid_room_id const _error)
                    {
                      return libftl::ship::layout::parse_error{
                          libftl::ship::layout::parse_error::variant{_error}};
                    }};

                auto const convert_bool_error{
                    [](libftl::ship::layout::parse_error::invalid_bool const _error)
                    {
                      return libftl::ship::layout::parse_error{
                          libftl::ship::layout::parse_error::variant{_error}};
                    }};

                return fcppt::either::apply(
                    [&_door](
                        libftl::ship::layout::door::optional_room_id const _left_top,
                        libftl::ship::layout::door::optional_room_id const _bottom_right,
                        bool const _vertical)
                    {
                      return libftl::ship::layout::door{
                          libftl::ship::layout::tile_pos{
                              libftl::ship::layout::tile_coordinate{_door.x_},
                              libftl::ship::layout::tile_coordinate{_door.y_}},
                          libftl::ship::layout::door::left_top_room{_left_top},
                          libftl::ship::layout::door::bottom_right_room{_bottom_right},
                          libftl::ship::layout::door::vertical{_vertical}};
                    },
                    fcppt::either::map_failure(
                        translate_optional_door_room(_door.left_top_), convert_room_error),
                    fcppt::either::map_failure(
                        translate_optional_door_room(_door.bottom_right_), convert_room_error),
                    fcppt::either::map_failure(
                        translate_bool(_door.vertical_), convert_bool_error));
              })),
      [&_layout](libftl::ship::layout::object::door_list &&_doors)
      {
        return libftl::ship::layout::object{
            libftl::ship::layout::object::offset_vector{_layout.offset_x_, _layout.offset_y_},
            libftl::ship::layout::object::vertical{_layout.vertical_},
            libftl::ship::layout::object::horizontal{_layout.horizontal_},
            libftl::ship::layout::ellipse{libftl::ship::layout::ellipse::value_type{
                libftl::ship::layout::ellipse::value_type::vector{
                    _layout.ellipse_x_, _layout.ellipse_y_},
                libftl::ship::layout::ellipse::value_type::dim{
                    _layout.ellipse_w_, _layout.ellipse_h_}}},
            fcppt::algorithm::map<libftl::ship::layout::object::room_list>(
                _layout.rooms_,
                [](room const &_room)
                {
                  return libftl::ship::layout::room{
                      libftl::ship::layout::room_id{_room.id_},
                      libftl::ship::layout::tile_rect{
                          libftl::ship::layout::tile_rect::vector{
                              libftl::ship::layout::tile_coordinate{_room.x_},
                              libftl::ship::layout::tile_coordinate{_room.y_}},
                          libftl::ship::layout::tile_rect::dim{
                              libftl::ship::layout::tile_coordinate{_room.w_},
                              libftl::ship::layout::tile_coordinate{_room.h_}}}};
                }),
            std::move(_doors)};
      });
}
}

fcppt::either::object<libftl::ship::layout::parse_error, libftl::ship::layout::object>
libftl::ship::layout::parse(std::istream &_stream)
{
  _stream.unsetf(std::ios_base::skipws);

  return fcppt::either::bind(
      fcppt::either::map_failure(
          fcppt::parse::grammar_parse_stream(_stream, grammar{}),
          [](fcppt::parse::parse_stream_error<char> &&_error)
          {
            return libftl::ship::layout::parse_error{
                libftl::ship::layout::parse_error::variant{std::move(_error)}};
          }),
      translate_result);
}
