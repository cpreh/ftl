#ifndef LIBFTL_SHIP_LAYOUT_OBJECT_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_OBJECT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/layout/door.hpp>
#include <libftl/ship/layout/ellipse.hpp>
#include <libftl/ship/layout/object_fwd.hpp>
#include <libftl/ship/layout/room.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::ship::layout
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wnull-dereference)

struct object
{
  using offset_vector = fcppt::math::vector::static_<fcppt::optional::object<unsigned>, 2>;

  FCPPT_MAKE_STRONG_TYPEDEF(int, vertical);

  FCPPT_MAKE_STRONG_TYPEDEF(fcppt::optional::object<int>, horizontal);

  using room_list = std::vector<libftl::ship::layout::room>;

  using door_list = std::vector<libftl::ship::layout::door>;

  LIBFTL_DETAIL_SYMBOL
  object(
      offset_vector,
      vertical,
      horizontal,
      libftl::ship::layout::ellipse,
      room_list &&,
      door_list &&);

  offset_vector offset_;

  vertical vertical_;

  horizontal horizontal_;

  libftl::ship::layout::ellipse ellipse_;

  room_list rooms_;

  door_list doors_;
};

FCPPT_PP_POP_WARNING

}

#endif
