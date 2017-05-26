#ifndef LIBFTL_XML_SECTOR_HPP_INCLUDED
#define LIBFTL_XML_SECTOR_HPP_INCLUDED

#include <libftl/archive/entry_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/generated/sector.hxx>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace xml
{

LIBFTL_DETAIL_SYMBOL
libftl::xml::result<
	libftl::xml::generated::sector_root
>
sector(
	std::istream &,
	libftl::archive::entry const &
);

}
}

#endif
