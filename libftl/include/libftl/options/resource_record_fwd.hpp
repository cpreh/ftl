#ifndef LIBFTL_OPTIONS_RESOURCE_RECORD_FWD_HPP_INCLUDED
#define LIBFTL_OPTIONS_RESOURCE_RECORD_FWD_HPP_INCLUDED

#include <libftl/options/resource_label.hpp>
#include <libftl/options/resource_variant_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/record/object_fwd.hpp>

namespace libftl::options
{
using resource_record = fcppt::record::object<
    fcppt::record::element<libftl::options::resource_label, libftl::options::resource_variant>>;

}

#endif
