#ifndef LIBFTL_ARCHIVE_INDEX_RESULT_FWD_HPP_INCLUDED
#define LIBFTL_ARCHIVE_INDEX_RESULT_FWD_HPP_INCLUDED

#include <libftl/archive/index.hpp>
#include <fcppt/string.hpp>
#include <fcppt/either/object_fwd.hpp>


namespace libftl
{
namespace archive
{

typedef
fcppt::either::object<
	fcppt::string,
	libftl::archive::index
>
index_result;

}
}

#endif
