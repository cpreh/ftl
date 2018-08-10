#ifndef LIBFTL_SHIP_RESOURCES_HPP_INCLUDED
#define LIBFTL_SHIP_RESOURCES_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/resources_fwd.hpp>
#include <libftl/ship/images/object.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/xml/generated/ship_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace libftl
{
namespace ship
{

class resources
{
	FCPPT_NONCOPYABLE(
		resources
	);
public:
	resources(
		fcppt::unique_ptr<
			libftl::xml::generated::ship::ship_root
		> &&,
		libftl::ship::images::object &&,
		libftl::ship::layout::object &&
	);

	LIBFTL_DETAIL_SYMBOL
	resources(
		resources &&
	);

	LIBFTL_DETAIL_SYMBOL
	resources &
	operator=(
		resources &&
	);

	LIBFTL_DETAIL_SYMBOL
	~resources();

	fcppt::unique_ptr<
		libftl::xml::generated::ship::ship_root
	> ship_root_;

	libftl::ship::images::object images_;

	libftl::ship::layout::object layout_;
};

}
}

#endif
