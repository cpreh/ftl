#ifndef LIBFTL_IMPL_XML_LOCATION_TO_STRING_HPP_INCLUDED
#define LIBFTL_IMPL_XML_LOCATION_TO_STRING_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/parse/location_fwd.hpp>

namespace libftl::impl::xml
{
[[nodiscard]] fcppt::string
location_to_string(fcppt::optional::object<fcppt::parse::location> const &);
}

#endif
