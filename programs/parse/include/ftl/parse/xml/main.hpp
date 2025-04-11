#ifndef FTL_PARSE_XML_MAIN_HPP_INCLUDED
#define FTL_PARSE_XML_MAIN_HPP_INCLUDED

#include <ftl/parse/error.hpp>
#include <ftl/parse/xml/arguments_fwd.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <fcppt/either/error.hpp>

namespace ftl::parse::xml
{
[[nodiscard]] fcppt::either::error<ftl::parse::error>
main(libftl::archive::base const &, ftl::parse::xml::arguments const &); // NOLINT(bugprone-exception-escape)
}

#endif
