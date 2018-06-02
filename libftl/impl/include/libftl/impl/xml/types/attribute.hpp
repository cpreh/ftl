#ifndef LIBFTL_IMPL_XML_TYPES_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_ATTRIBUTE_HPP_INCLUDED

#include <libftl/impl/xml/types/attribute_fwd.hpp>
#include <libftl/impl/xml/types/string.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace types
{

class attribute
{
public:
	libftl::impl::xml::types::string name;

	libftl::impl::xml::types::string value;
};

}
}
}
}

#endif
