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
	entry(
		libftl::archive::offset const _offset,
		libftl::archive::length const _length
	)
	:
		offset_{
			_offset
		},
		length_{
			_length
		}
	{
	}

	libftl::archive::offset offset_;

	libftl::archive::length length_;
};

}
}

#endif
