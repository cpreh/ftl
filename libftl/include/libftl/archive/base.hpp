#ifndef LIBFTL_ARCHIVE_BASE_HPP_INCLUDED
#define LIBFTL_ARCHIVE_BASE_HPP_INCLUDED

#include <libftl/archive/base_fwd.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <libftl/error_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace archive
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	LIBFTL_DETAIL_SYMBOL
	virtual
	~base();

	virtual
	fcppt::either::object<
		libftl::error,
		fcppt::unique_ptr<
			std::istream
		>
	>
	open(
		libftl::archive::path const &
	) = 0;
};

}
}

#endif
