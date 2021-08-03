#ifndef LIBFTL_OPTIONS_CREATE_RESOURCE_PARSER_HPP_INCLUDED
#define LIBFTL_OPTIONS_CREATE_RESOURCE_PARSER_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/options/resource_parser.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace libftl
{
namespace options
{
LIBFTL_DETAIL_SYMBOL
fcppt::unique_ptr<libftl::options::resource_parser> create_resource_parser();

}
}

#endif
