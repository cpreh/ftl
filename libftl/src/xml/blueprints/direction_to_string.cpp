#include <libftl/xml/blueprints/direction.hpp>
#include <libftl/xml/blueprints/direction_to_string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/enum/to_string_case.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

std::string_view fcppt::enum_::to_string_impl<libftl::xml::blueprints::direction>::get(
    libftl::xml::blueprints::direction const _direction)
{
#define SLIDE_CASE(direction_name) \
  FCPPT_ENUM_TO_STRING_CASE(libftl::xml::blueprints::direction, direction_name)
  switch (_direction)
  {
    SLIDE_CASE(left);
    SLIDE_CASE(right);
    SLIDE_CASE(up);
    SLIDE_CASE(down);
  }
  FCPPT_ASSERT_UNREACHABLE;
}
