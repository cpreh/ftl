#ifndef LIBFTL_IMPL_XML_SECTORS_SECTOR_TYPE_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_SECTORS_SECTOR_TYPE_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/typed/named_node_base.hpp>
#include <libftl/xml/sectors/sector_type.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::sectors
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::named_node_base<libftl::xml::sectors::sector_type>>
sector_type_parser();
}

#endif
