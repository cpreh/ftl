#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/read_without_root.hpp>
#include <libftl/impl/xml/root_name.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/sector.hpp>
#include <libftl/xml/generated/sector.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::sector_root
>
libftl::xml::sector(
	libftl::archive::file const &_file
)
{
	return
		libftl::impl::xml::read_without_root(
			_file,
			fcppt::function<
				std::unique_ptr<
					libftl::xml::generated::sector_root
				>(
					std::istream &
				)
			>{
				[](
					std::istream &_inner_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::sector_root
				>
				{
					return
						libftl::xml::generated::sectorRoot(
							_inner_stream
						);
				}
			},
			libftl::impl::xml::root_name{
				"sectorRoot"
			}
		);
}
