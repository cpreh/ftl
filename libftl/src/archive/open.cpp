#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/index.hpp>
#include <libftl/archive/open.hpp>
#include <libftl/archive/read_index.hpp>
#include <libftl/impl/archive/native.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fstream>
#include <ios>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>


fcppt::either::object<
	libftl::error,
	libftl::archive::base_unique_ptr
>
libftl::archive::open(
	boost::filesystem::path &&_path
)
{
	return
		fcppt::either::bind(
			fcppt::either::from_optional(
				fcppt::filesystem::open<
					std::ifstream
				>(
					_path,
					std::ios_base::binary
				),
				[
					&_path
				]{
					return
						libftl::error{
							FCPPT_TEXT("Unable to open ")
							+
							fcppt::filesystem::path_to_string(
								_path
							)
						};
				}
			),
			[
				&_path
			](
				std::ifstream &&_stream
			)
			{
				return
					fcppt::either::map(
						libftl::archive::read_index(
							_stream
						),
						[
							&_path
						](
							libftl::archive::index &&_index
						)
						->
						libftl::archive::base_unique_ptr
						{
							return
								fcppt::unique_ptr_to_base<
									libftl::archive::base
								>(
									fcppt::make_unique_ptr<
										libftl::impl::archive::native
									>(
										std::move(
											_path
										),
										std::move(
											_index
										)
									)
								);
						}
					);
			}
		);
}
