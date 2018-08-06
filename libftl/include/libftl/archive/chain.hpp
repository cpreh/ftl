#ifndef LIBFTL_ARCHIVE_CHAIN_HPP_INCLUDED
#define LIBFTL_ARCHIVE_CHAIN_HPP_INCLUDED

#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/detail/symbol.hpp>


namespace libftl
{
namespace archive
{

LIBFTL_DETAIL_SYMBOL
libftl::archive::base_unique_ptr
chain(
	libftl::archive::base_unique_ptr &&,
	libftl::archive::base_unique_ptr &&
);

}
}

#endif
