#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/animations.hpp>
#include <libftl/xml/generated/animations.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::animations::animations_root
>
libftl::xml::animations(
	libftl::archive::file const &_file
)
{
	return
		libftl::impl::xml::read(
			_file,
			libftl::impl::xml::load_function<
				libftl::xml::generated::animations::animations_root
			>{
				[](
					std::istream &_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::animations::animations_root
				>
				{
					return
						libftl::xml::generated::animations::root(
							_stream,
							xml_schema::flags::dont_validate
						);
				}
			}
		);
}
