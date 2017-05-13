#ifndef LIBFTL_ARCHIVE_ENTRY_HPP_INCLUDED
#define LIBFTL_ARCHIVE_ENTRY_HPP_INCLUDED

#include <libftl/archive/entry_fwd.hpp>
#include <libftl/archive/length.hpp>
#include <libftl/archive/offset.hpp>


namespace libftl
{
namespace archive
{

struct entry
{
	libftl::archive::offset offset;

	libftl::archive::length length;
};

}
}

#endif
