#ifndef LIBFTL_IMPL_XML_LOCATION_TO_STRING_HPP_INCLUDED
#define LIBFTL_IMPL_XML_LOCATION_TO_STRING_HPP_INCLUDED

#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/parse/location_impl.hpp>
#include <fcppt/parse/location_output.hpp>

namespace libftl::impl::xml
{
[[nodiscard]] fcppt::string inline location_to_string(
    fcppt::optional::object<fcppt::parse::location> const &_location)
{
  return fcppt::output_to_fcppt_string(_location) + FCPPT_TEXT(": ");
}
}

#endif
