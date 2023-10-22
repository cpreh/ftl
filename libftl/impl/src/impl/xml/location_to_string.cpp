#include <libftl/impl/xml/location_to_string.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/location_impl.hpp>
#include <fcppt/parse/location_output.hpp> // NOLINT(misc-include-cleaner)

fcppt::string libftl::impl::xml::location_to_string(
    fcppt::optional::object<fcppt::parse::location> const &_location)
{
  return fcppt::optional::maybe(
    _location,
    []{
      return fcppt::string{FCPPT_TEXT("Unknown location")};
    },
    [](fcppt::parse::location const &_loc)
    {
      return fcppt::output_to_fcppt_string(_loc);
    }
    )
    + FCPPT_TEXT(": ");
}
