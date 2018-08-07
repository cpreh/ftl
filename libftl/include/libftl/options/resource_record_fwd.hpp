#ifndef LIBFTL_OPTIONS_RESOURCE_RECORD_FWD_HPP_INCLUDED
#define LIBFTL_OPTIONS_RESOURCE_RECORD_FWD_HPP_INCLUDED

#include <libftl/options/resource_label.hpp>
#include <libftl/options/resource_variant_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/record/variadic_fwd.hpp>


namespace libftl
{
namespace options
{

typedef
fcppt::record::variadic<
	fcppt::record::element<
		libftl::options::resource_label,
		libftl::options::resource_variant
	>
>
resource_record;

}
}

#endif
