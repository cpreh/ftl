#ifndef LIBFTL_SHIP_LOAD_ERROR_HPP_INCLUDED
#define LIBFTL_SHIP_LOAD_ERROR_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/load_error_fwd.hpp> // IWYU pragma: export
#include <libftl/ship/images/error.hpp>
#include <libftl/ship/layout/load_error.hpp>
#include <libftl/ship/layout/load_xml_error.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::ship
{
struct load_error
{
  struct not_found {};

  using variant = fcppt::variant::object<
      not_found,
      libftl::ship::layout::load_xml_error,
      libftl::ship::layout::load_error,
      libftl::ship::images::error>;

  std::string name_;
  variant value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::ship::load_error const &);
}

#endif
