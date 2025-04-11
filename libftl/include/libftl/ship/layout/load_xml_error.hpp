#ifndef LIBFTL_SHIP_LAYOUT_LOAD_XML_ERROR_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_LOAD_XML_ERROR_HPP_INCLUDED

#include <libftl/archive/open_path_error.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/ship/layout/load_xml_error_fwd.hpp> // IWYU pragma: export
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace libftl::ship::layout
{

struct load_xml_error
{
  using variant = fcppt::variant::object<libftl::archive::open_path_error, libftl::xml::error>;

  variant value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::ship::layout::load_xml_error const &);
}

#endif
