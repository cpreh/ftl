#ifndef LIBFTL_ARCHIVE_OFFSET_HPP_INCLUDED
#define LIBFTL_ARCHIVE_OFFSET_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace archive
{

FCPPT_MAKE_STRONG_TYPEDEF(
	std::streamsize,
	offset
);

}
}

#endif
