#ifndef LIBFTL_OPTIONS_RESOURCE_VARIANT_FWD_HPP_INCLUDED
#define LIBFTL_OPTIONS_RESOURCE_VARIANT_FWD_HPP_INCLUDED

#include <libftl/options/native_resource_record_fwd.hpp>
#include <libftl/options/unpacked_resource_record_fwd.hpp>
#include <fcppt/options/left_fwd.hpp>
#include <fcppt/options/right_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>

namespace libftl::options
{
using resource_variant = fcppt::variant::object<
    fcppt::options::left<libftl::options::native_resource_record>,
    fcppt::options::right<libftl::options::unpacked_resource_record>>;

}

#endif
