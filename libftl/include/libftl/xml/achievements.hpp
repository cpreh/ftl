#ifndef LIBFTL_XML_ACHIEVEMENTS_HPP_INCLUDED
#define LIBFTL_XML_ACHIEVEMENTS_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/achievements_result.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml
{
[[nodiscard]] LIBFTL_DETAIL_SYMBOL
    fcppt::either::object<libftl::error, libftl::xml::achievements_result>
    achievements(std::istream &);
}

#endif
