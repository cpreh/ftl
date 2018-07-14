#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/sectors.hpp>
#include <libftl/xml/generated/sectors.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <regex>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::sectors::sectors_root
>
libftl::xml::sectors(
	libftl::archive::file const &_file
)
{
	return
		libftl::impl::xml::read(
			_file,
			libftl::impl::xml::load_function<
				libftl::xml::generated::sectors::sectors_root
			>{
				[](
					std::istream &_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::sectors::sectors_root
				>
				{
					return
						libftl::xml::generated::sectors::root(
							_stream,
							xml_schema::flags::dont_validate
						);
				}
			}
		);
}
