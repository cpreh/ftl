#ifndef LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED

#include <libftl/archive/file_fwd.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <fcppt/either/object_impl.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{

fcppt::either::object<
	libftl::xml::error,
	libftl::impl::xml::document
>
parse(
	libftl::archive::file const &
);

}
}
}

#endif
