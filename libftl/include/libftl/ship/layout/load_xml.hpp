#ifndef LIBFTL_SHIP_LAYOUT_LOAD_XML_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_LOAD_XML_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <libftl/ship/layout/name_fwd.hpp>
#include <libftl/xml/generated/ship_fwd.hpp>
#include <fcppt/reference_impl.hpp>
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
	fcppt::reference<
		libftl::xml::generated::ship::ship_root const
	>
>
load_xml(
	libftl::archive::base &,
	libftl::ship::layout::name
);

}
}
}

#endif
