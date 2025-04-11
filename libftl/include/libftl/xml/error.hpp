#ifndef LIBFTL_XML_ERROR_HPP_INCLUDED
#define LIBFTL_XML_ERROR_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/error_fwd.hpp> // IWYU pragma: export
#include <libftl/xml/type_error.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/parse/parse_stream_error.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace libftl::xml
{
struct error
{
  using variant =
      fcppt::variant::object<fcppt::parse::parse_stream_error<char>, libftl::xml::type_error>;

  variant value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::xml::error const &);
}

#endif
