#ifndef LIBFTL_XML_SECTORS_SECTOR_TYPE_HPP_INCLUDED
#define LIBFTL_XML_SECTORS_SECTOR_TYPE_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/name.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::sectors
{
using sector_type = libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::name, std::string>>,
    std::vector<libftl::xml::node<fcppt::record::object<>, std::string>>>;
}

#endif
