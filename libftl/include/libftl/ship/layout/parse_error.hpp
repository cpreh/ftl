#ifndef LIBFTL_SHIP_LAYOUT_PARSE_ERROR_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_PARSE_ERROR_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/layout/parse_error_fwd.hpp> // IWYU pragma: export
#include <libftl/ship/layout/room_id_signed.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/parse/parse_stream_error_impl.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace libftl::ship::layout
{
struct parse_error
{
  FCPPT_DECLARE_STRONG_TYPEDEF(libftl::ship::layout::room_id_signed, invalid_room_id);

  FCPPT_DECLARE_STRONG_TYPEDEF(int, invalid_bool);

  using variant =
      fcppt::variant::object<invalid_room_id, invalid_bool, fcppt::parse::parse_stream_error<char>>;

  variant value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::ship::layout::parse_error const &);
}

#endif
