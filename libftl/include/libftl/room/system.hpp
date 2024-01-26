#ifndef LIBFTL_ROOM_SYSTEM_HPP_INCLUDED
#define LIBFTL_ROOM_SYSTEM_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/room/system_fwd.hpp> // IWYU pragma: keep
#include <libftl/room/type.hpp>
#include <libftl/ship/layout/room_id.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep
#include <fcppt/optional/object_impl.hpp>

namespace libftl::room
{
struct system
{
  FCPPT_DECLARE_STRONG_TYPEDEF(unsigned, power);

  FCPPT_DECLARE_STRONG_TYPEDEF(unsigned, max_power);

  FCPPT_DECLARE_STRONG_TYPEDEF(bool, available);

  LIBFTL_DETAIL_SYMBOL
  system(
      libftl::room::type,
      fcppt::optional::object<sge::texture::const_part_shared_ptr>,
      power,
      fcppt::optional::object<max_power>,
      libftl::ship::layout::room_id,
      fcppt::optional::object<available>);

  libftl::room::type type_;

  fcppt::optional::object<sge::texture::const_part_shared_ptr> background_;

  power power_;

  fcppt::optional::object<max_power> max_power_;

  libftl::ship::layout::room_id room_;

  fcppt::optional::object<available> available_;
};

}

#endif
