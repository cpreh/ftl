#ifndef LIBFTL_IMPL_XML_SECTORS_SECTOR_TYPE_PARSER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_SECTORS_SECTOR_TYPE_PARSER_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/xml/sectors/sector_type.hpp>
#include <fcppt/unique_ptr.hpp>

namespace libftl::impl::xml::sectors
{
[[nodiscard]] fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::sectors::sector_type, libftl::impl::xml::node>>
sector_type_parser();
}

#endif
