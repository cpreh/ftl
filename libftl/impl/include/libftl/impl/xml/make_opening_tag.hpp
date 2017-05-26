#ifndef LIBFTL_IMPL_XML_MAKE_OPENING_TAG_HPP_INCLUDED
#define LIBFTL_IMPL_XML_MAKE_OPENING_TAG_HPP_INCLUDED

#include <libftl/impl/xml/root_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{

inline
std::string
make_opening_tag(
	libftl::impl::xml::root_name const &_name
)
{
	return
		"<"
		+
		_name.get()
		+
		">";
}

}
}
}

#endif
