#ifndef FTL_PARSE_ERROR_HPP_INCLUDED
#define FTL_PARSE_ERROR_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace ftl::parse
{
FCPPT_DECLARE_STRONG_TYPEDEF(fcppt::string, error);
}

#endif
