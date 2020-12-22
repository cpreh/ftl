#ifndef LIBFTL_ARCHIVE_BASE_REF_HPP_INCLUDED
#define LIBFTL_ARCHIVE_BASE_REF_HPP_INCLUDED

#include <libftl/archive/base_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace libftl
{
namespace archive
{

using
base_ref
=
fcppt::reference<
	libftl::archive::base
>;

}
}

#endif
