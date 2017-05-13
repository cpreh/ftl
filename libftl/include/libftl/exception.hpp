#ifndef LIBFTL_EXCEPTION_HPP_INCLUDED
#define LIBFTL_EXCEPTION_HPP_INCLUDED

#include <libftl/exception_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>


namespace libftl
{

class exception
:
	public fcppt::exception
{
public:
	LIBFTL_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::string &&
	);
};

}

#endif
