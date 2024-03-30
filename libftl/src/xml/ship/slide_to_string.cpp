#include <libftl/xml/ship/slide.hpp>
#include <libftl/xml/ship/slide_to_string.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/enum/to_string_case.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

std::string_view
fcppt::enum_::to_string_impl<libftl::xml::ship::slide>::get(libftl::xml::ship::slide const _slide)
{
#define SLIDE_CASE(slide_name) FCPPT_ENUM_TO_STRING_CASE(libftl::xml::ship::slide, slide_name)
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_slide)
  {
    SLIDE_CASE(left);
    SLIDE_CASE(right);
    SLIDE_CASE(up);
    SLIDE_CASE(down);
    SLIDE_CASE(no);
  }
  FCPPT_PP_POP_WARNING
  throw fcppt::enum_::make_invalid(_slide);
}
