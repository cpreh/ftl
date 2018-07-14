#ifndef LIBFTL_XML_ANIMATIONS_HPP_INCLUDED
#define LIBFTL_XML_ANIMATIONS_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/archive/file_fwd.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/generated/animations.hpp>


namespace libftl
{
namespace xml
{

LIBFTL_DETAIL_SYMBOL
libftl::xml::result<
	libftl::xml::generated::animations::animations_root
>
animations(
	libftl::archive::file const &
);

}
}

#endif
