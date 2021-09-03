#ifndef LIBFTL_XML_SECTORS_RESULT_HPP_INCLUDED
#define LIBFTL_XML_SECTORS_RESULT_HPP_INCLUDED

#include <libftl/xml/sectors/sector_description.hpp>
#include <libftl/xml/sectors/sector_type.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::sectors
{
using result = fcppt::tuple::object<
  std::vector<libftl::xml::sectors::sector_description>,
  std::vector<libftl::xml::sectors::sector_type>
>;

}

#endif
