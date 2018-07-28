#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/filesystem.hpp>
#include <libftl/impl/archive/filesystem.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


libftl::archive::base_unique_ptr
libftl::archive::filesystem(
	boost::filesystem::path &&_path
)
{
	return
		fcppt::unique_ptr_to_base<
			libftl::archive::base
		>(
			fcppt::make_unique_ptr<
				libftl::impl::archive::filesystem
			>(
				std::move(
					_path
				)
			)
		);
}
