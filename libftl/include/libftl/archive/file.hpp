#ifndef LIBFTL_ARCHIVE_FILE_HPP_INCLUDED
#define LIBFTL_ARCHIVE_FILE_HPP_INCLUDED

#include <libftl/archive/entry.hpp>
#include <libftl/archive/file_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace archive
{

struct file
{
	fcppt::reference<
		std::istream
	> stream;

	libftl::archive::entry entry;
};

}
}

#endif
