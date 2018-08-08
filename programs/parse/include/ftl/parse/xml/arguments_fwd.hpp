#ifndef FTL_PARSE_XML_ARGUMENTS_FWD_HPP_INCLUDED
#define FTL_PARSE_XML_ARGUMENTS_FWD_HPP_INCLUDED

#include <ftl/parse/path_label.hpp>
#include <ftl/parse/xml/type_fwd.hpp>
#include <ftl/parse/xml/type_label.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/record/variadic_fwd.hpp>


namespace ftl
{
namespace parse
{
namespace xml
{

typedef
fcppt::record::variadic<
	fcppt::record::element<
		ftl::parse::xml::type_label,
		ftl::parse::xml::type
	>,
	fcppt::record::element<
		ftl::parse::path_label,
		libftl::archive::path
	>
>
arguments;

}
}
}

#endif
