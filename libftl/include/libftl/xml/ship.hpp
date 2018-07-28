#ifndef LIBFTL_XML_SHIP_HPP_INCLUDED
#define LIBFTL_XML_SHIP_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace xml
{

LIBFTL_DETAIL_SYMBOL
libftl::xml::result<
	libftl::xml::generated::ship::ship_root
>
ship(
	std::istream &
);

}
}

#endif
