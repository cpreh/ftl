#ifndef LIBFTL_SHIP_LAYOUT_LOAD_XML_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_LOAD_XML_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/ship/layout/name_fwd.hpp>
#include <libftl/xml/generated/ship_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/object_impl.hpp>


namespace libftl
{
namespace ship
{
namespace layout
{

LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
	libftl::error,
	fcppt::unique_ptr<
		libftl::xml::generated::ship::ship_root
	>
>
load_xml(
	libftl::archive::base &, // NOLINT(google-runtime-references)
	libftl::ship::layout::name const &
);

}
}
}

#endif
