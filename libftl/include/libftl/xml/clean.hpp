#ifndef LIBFTL_XML_CLEAN_HPP_INCLUDED
#define LIBFTL_XML_CLEAN_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/archive/file_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace xml
{

LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
	libftl::error,
	std::string
>
clean(
	libftl::archive::file const &
);

}
}

#endif
