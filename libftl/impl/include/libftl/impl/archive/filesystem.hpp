#ifndef LIBFTL_IMPL_ARCHIVE_FILESYSTEM_HPP_INCLUDED
#define LIBFTL_IMPL_ARCHIVE_FILESYSTEM_HPP_INCLUDED

#include <libftl/error_fwd.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace archive
{

class filesystem
:
	public libftl::archive::base
{
	FCPPT_NONCOPYABLE(
		filesystem
	);
public:
	explicit
	filesystem(
		boost::filesystem::path &&
	);

	~filesystem()
	override;

	fcppt::either::object<
		libftl::error,
		fcppt::unique_ptr<
			std::istream
		>
	>
	open(
		libftl::archive::path const &
	)
	override;
private:
	boost::filesystem::path const directory_;
};

}
}
}

#endif
