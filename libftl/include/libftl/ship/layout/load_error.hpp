#ifndef LIBFTL_SHIP_LAYOUT_LOAD_ERROR_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_LOAD_ERROR_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/archive/open_path_error.hpp>
#include <libftl/ship/layout/load_error_fwd.hpp> // IWYU pragma: export
#include <libftl/ship/layout/parse_error.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace libftl::ship::layout
{

struct load_error
{
  using variant =
      fcppt::variant::object<libftl::ship::layout::parse_error, libftl::archive::open_path_error>;

  variant value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::ship::layout::load_error const &);
}

#endif
