#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/impl/xml/root_name.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/sector.hpp>
#include <libftl/xml/generated/sector.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <regex>
#include <string>
#include <sstream>
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
			fcppt::function<
				std::unique_ptr<
					libftl::xml::generated::sector_root
				>(
					std::string const &
				)
			>{
				[](
					std::string const &_string
				)
				->
				std::unique_ptr<
					libftl::xml::generated::sector_root
				>
				{
					std::regex const fixup{
						"sectorDescrption"
					};

					std::string const fixed{
						std::regex_replace(
							_string,
							fixup,
							"sectorDescription"
						)
					};

					std::istringstream stream{
						fixed
					};

					return
						libftl::xml::generated::sectorRoot(
							stream,
							xml_schema::flags::dont_validate
						);
				}
			},
			libftl::impl::xml::root_name{
				"sectorRoot"
			}
		);
}
