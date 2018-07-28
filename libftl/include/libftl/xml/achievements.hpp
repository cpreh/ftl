#ifndef LIBFTL_XML_ACHIEVEMENTS_HPP_INCLUDED
#define LIBFTL_XML_ACHIEVEMENTS_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/generated/achievements.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace xml
{

LIBFTL_DETAIL_SYMBOL
libftl::xml::result<
	libftl::xml::generated::achievements::achievements_root
>
achievements(
	std::istream &
);

}
}

#endif
