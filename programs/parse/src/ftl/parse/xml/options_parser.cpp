#include <ftl/parse/path_label.hpp>
#include <ftl/parse/xml/arguments.hpp>
#include <ftl/parse/xml/options_parser.hpp>
#include <ftl/parse/xml/type.hpp>
#include <ftl/parse/xml/type_label.hpp>
#include <libftl/archive/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/input.hpp>
#include <fcppt/enum/names_array.hpp>
#include <fcppt/enum/names_impl_fwd.hpp>
#include <fcppt/io/istream.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/base.hpp>
#include <fcppt/options/base_unique_ptr.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_base.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/pretty_type_enum.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace
{

typedef
fcppt::enum_::names_array<
	ftl::parse::xml::type
>
xml_type_array;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

xml_type_array const xml_types{{{
	FCPPT_TEXT("achievements"),
	FCPPT_TEXT("animations"),
	FCPPT_TEXT("blueprints"),
	FCPPT_TEXT("events"),
	FCPPT_TEXT("sectors"),
	FCPPT_TEXT("ship")
}}};

FCPPT_PP_POP_WARNING

}

namespace fcppt
{
namespace enum_
{

template<>
struct names_impl<
	ftl::parse::xml::type
>
{
	static
	xml_type_array const &
	get()
	{
		return
			xml_types;
	}
};

}
}

namespace ftl
{
namespace parse
{
namespace xml
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wmissing-prototypes)
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

fcppt::io::istream &
operator>>(
	fcppt::io::istream &_stream,
	ftl::parse::xml::type &_name
)
{
	return
		fcppt::enum_::input(
			_stream,
			_name
		);
}

FCPPT_PP_POP_WARNING

}
}
}

fcppt::options::base_unique_ptr<
	ftl::parse::xml::arguments
>
ftl::parse::xml::options_parser()
{
	return
		fcppt::options::make_base<
			ftl::parse::xml::arguments
		>(
			fcppt::options::apply(
				fcppt::options::argument<
					ftl::parse::xml::type_label,
					ftl::parse::xml::type
				>{
					fcppt::options::long_name{
						FCPPT_TEXT("type")
					},
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("Type of the xml file to parse")
						}
					}
				},
				fcppt::options::argument<
					ftl::parse::path_label,
					libftl::archive::path
				>{
					fcppt::options::long_name{
						FCPPT_TEXT("xml-file")
					},
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("Path to the .xml file")
						}
					}
				}
			)
		);
}
