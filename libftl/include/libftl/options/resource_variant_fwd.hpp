#ifndef LIBFTL_OPTIONS_RESOURCE_VARIANT_FWD_HPP_INCLUDED
#define LIBFTL_OPTIONS_RESOURCE_VARIANT_FWD_HPP_INCLUDED

#include <libftl/options/native_resource_record_fwd.hpp>
#include <libftl/options/unpacked_resource_record_fwd.hpp>
#include <fcppt/options/left_fwd.hpp>
#include <fcppt/options/right_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>


namespace libftl
{
namespace options
{

typedef
fcppt::variant::variadic<
	fcppt::options::left<
		libftl::options::native_resource_record
	>,
	fcppt::options::right<
		libftl::options::unpacked_resource_record
	>
>
resource_variant;

}
}

#endif
