#ifndef LIBFTL_OPTIONS_NATIVE_RESOURCE_RECORD_FWD_HPP_INCLUDED
#define LIBFTL_OPTIONS_NATIVE_RESOURCE_RECORD_FWD_HPP_INCLUDED

#include <libftl/options/data_file_label.hpp>
#include <libftl/options/resource_file_label.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/record/variadic_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace options
{

typedef
fcppt::record::variadic<
	fcppt::record::element<
		libftl::options::data_file_label,
		std::filesystem::path
	>,
	fcppt::record::element<
		libftl::options::resource_file_label,
		std::filesystem::path
	>
>
native_resource_record;

}
}

#endif
