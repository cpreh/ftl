#ifndef LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/document.hpp>
#include <fcppt/either/object_impl.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{

fcppt::either::object<
	libftl::error,
	libftl::impl::xml::document
>
parse(
	libftl::archive::file const &
);

}
}
}

#endif
