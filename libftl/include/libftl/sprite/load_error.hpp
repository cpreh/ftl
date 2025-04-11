#ifndef LIBFTL_SPRITE_LOAD_ERROR_HPP_INCLUDED
#define LIBFTL_SPRITE_LOAD_ERROR_HPP_INCLUDED

#include <libftl/archive/open_path_error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/sprite/load_error_fwd.hpp> // IWYU pragma: export
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace libftl::sprite
{
struct load_error
{
  FCPPT_DECLARE_STRONG_TYPEDEF(libftl::archive::path, decode_error);
  using variant = fcppt::variant::object<libftl::archive::open_path_error, decode_error>;

  variant value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::sprite::load_error const &);
}

#endif
