#ifndef LIBFTL_BLUEPRINTS_ERROR_HPP_INCLUDED
#define LIBFTL_BLUEPRINTS_ERROR_HPP_INCLUDED

#include <libftl/archive/open_path_error.hpp>
#include <libftl/blueprints/error_fwd.hpp> // IWYU pragma: export
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/error.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::blueprints
{
struct error
{
  using variant = fcppt::variant::object<libftl::archive::open_path_error, libftl::xml::error>;

  variant value_;

  std::string file_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::blueprints::error const &);
}

#endif
