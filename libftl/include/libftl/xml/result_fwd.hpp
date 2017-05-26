#ifndef LIBFTL_XML_RESULT_FWD_HPP_INCLUDED
#define LIBFTL_XML_RESULT_FWD_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>


namespace libftl
{
namespace xml
{

template<
	typename Type
>
using
result
=
fcppt::either::object<
	fcppt::string,
	fcppt::unique_ptr<
		Type
	>
>;

}
}

#endif
