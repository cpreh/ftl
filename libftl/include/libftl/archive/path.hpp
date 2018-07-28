#ifndef LIBFTL_ARCHIVE_PATH_HPP_INCLUDED
#define LIBFTL_ARCHIVE_PATH_HPP_INCLUDED

#include <libftl/archive/path_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace archive
{

class path
{
public:
	LIBFTL_DETAIL_SYMBOL
	path();

	LIBFTL_DETAIL_SYMBOL
	std::string const &
	rep() const;

	LIBFTL_DETAIL_SYMBOL
	void
	add(
		std::string &&
	);
private:
	std::string rep_;
};

LIBFTL_DETAIL_SYMBOL
libftl::archive::path
operator/(
	libftl::archive::path &&,
	std::string &&
);

}
}

#endif
