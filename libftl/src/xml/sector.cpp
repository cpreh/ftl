#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/impl/xml/replace.hpp>
#include <libftl/impl/xml/replace_list.hpp>
#include <libftl/impl/xml/root_name.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/sector.hpp>
#include <libftl/xml/generated/sector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <regex>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::sector_root
>
libftl::xml::sector(
	libftl::archive::file const &_file
)
{
	return
		libftl::impl::xml::read(
			_file,
			libftl::impl::xml::load_function<
				libftl::xml::generated::sector_root
			>{
				[](
					std::istream &_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::sector_root
				>
				{
					return
						libftl::xml::generated::sectorRoot(
							_stream,
							xml_schema::flags::dont_validate
						);
				}
			},
			libftl::impl::xml::root_name{
				"sectorRoot"
			},
			libftl::impl::xml::replace_list{
				libftl::impl::xml::replace{
					std::regex{
						"sectorDescrption"
					},
					"sectorDescription"
				}
			}
		);
}
