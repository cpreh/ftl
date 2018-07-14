#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/ship.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <regex>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::ship::ship_root
>
libftl::xml::ship(
	libftl::archive::file const &_file
)
{
	return
		libftl::impl::xml::read(
			_file,
			libftl::impl::xml::load_function<
				libftl::xml::generated::ship::ship_root
			>{
				[](
					std::istream &_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::ship::ship_root
				>
				{
					return
						libftl::xml::generated::ship::root(
							_stream,
							xml_schema::flags::dont_validate
						);
				}
			}
		);
}
