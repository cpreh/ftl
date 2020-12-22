#ifndef LIBFTL_OPTIONS_RESOURCE_PARSER_FWD_HPP_INCLUDED
#define LIBFTL_OPTIONS_RESOURCE_PARSER_FWD_HPP_INCLUDED

#include <libftl/options/resource_record_fwd.hpp>
#include <fcppt/options/base_fwd.hpp>


namespace libftl
{
namespace options
{

using
resource_parser
=
fcppt::options::base<
	libftl::options::resource_record
>;

}
}

#endif
