#ifndef LIBFTL_SHIP_IMAGES_ERROR_HPP_INCLUDED
#define LIBFTL_SHIP_IMAGES_ERROR_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/images/error_fwd.hpp> // IWYU pragma: export
#include <libftl/sprite/load_error.hpp>
#include <fcppt/io/ostream_fwd.hpp>

namespace libftl::ship::images
{
struct error
{
  libftl::sprite::load_error error1_;
  libftl::sprite::load_error error2_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::ship::images::error const &);
}

#endif
