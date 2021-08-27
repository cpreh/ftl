#include <libftl/xml/ship/slide.hpp>
#include <libftl/xml/ship/slide_to_string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/enum/to_string_case.hpp>
#include <fcppt/enum/to_string_impl_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

std::string_view
fcppt::enum_::to_string_impl<libftl::xml::ship::slide>::get(libftl::xml::ship::slide const _slide)
{
#define SLIDE_CASE(slide_name) FCPPT_ENUM_TO_STRING_CASE(libftl::xml::ship::slide, slide_name)
  switch (_slide)
  {
    SLIDE_CASE(left);
    SLIDE_CASE(right);
  }
  FCPPT_ASSERT_UNREACHABLE;
}
