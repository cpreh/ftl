#include <ftl/parse/path_label.hpp>
#include <ftl/parse/xml/arguments.hpp>
#include <ftl/parse/xml/options_parser.hpp>
#include <ftl/parse/xml/type.hpp>
#include <ftl/parse/xml/type_label.hpp>
#include <libftl/archive/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/input.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/enum/to_string_case.hpp>
#include <fcppt/enum/to_string_impl_fwd.hpp>
#include <fcppt/io/istream.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/base.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/options/base_unique_ptr.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_base.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/pretty_type_enum.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

namespace fcppt::enum_
{
template <>
struct to_string_impl<ftl::parse::xml::type>
{
  static std::string_view get(ftl::parse::xml::type const _type)
  {
#define TO_STRING_CASE(name) FCPPT_ENUM_TO_STRING_CASE(ftl::parse::xml::type, name)
    FCPPT_PP_PUSH_WARNING
    FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
    switch (_type)
    {
      TO_STRING_CASE(achievements);
      TO_STRING_CASE(animations);
      TO_STRING_CASE(blueprints);
      TO_STRING_CASE(events);
      TO_STRING_CASE(sectors);
      TO_STRING_CASE(ship);
    }
    FCPPT_PP_POP_WARNING
    throw fcppt::enum_::make_invalid(_type);
#undef TO_STRING_CASE
  }
};

}

namespace ftl::parse::xml
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wmissing-prototypes)
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

fcppt::io::istream &operator>>(fcppt::io::istream &_stream, ftl::parse::xml::type &_name)
{
  return fcppt::enum_::input(_stream, _name);
}

FCPPT_PP_POP_WARNING

}

fcppt::options::base_unique_ptr<ftl::parse::xml::arguments> ftl::parse::xml::options_parser()
{
  return fcppt::options::make_base<ftl::parse::xml::arguments>(fcppt::options::apply(
      fcppt::options::argument<ftl::parse::xml::type_label, ftl::parse::xml::type>{
          fcppt::options::long_name{FCPPT_TEXT("type")},
          fcppt::options::optional_help_text{
              fcppt::options::help_text{FCPPT_TEXT("Type of the xml file to parse")}}},
      fcppt::options::argument<ftl::parse::path_label, libftl::archive::path>{
          fcppt::options::long_name{FCPPT_TEXT("xml-file")},
          fcppt::options::optional_help_text{
              fcppt::options::help_text{FCPPT_TEXT("Path to the .xml file")}}}));
}
