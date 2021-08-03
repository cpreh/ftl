#ifndef LIBFTL_ARCHIVE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define LIBFTL_ARCHIVE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <libftl/archive/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace libftl
{
namespace archive
{
using base_unique_ptr = fcppt::unique_ptr<libftl::archive::base>;

}
}

#endif
