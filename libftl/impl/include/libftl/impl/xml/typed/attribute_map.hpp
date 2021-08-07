#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_MAP_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_MAP_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
using attribute_map = std::unordered_map<std::string, std::string>;

}

#endif
