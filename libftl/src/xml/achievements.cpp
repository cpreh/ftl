#include <libftl/impl/xml/load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/achievements.hpp>
#include <libftl/xml/generated/achievements.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <memory>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::achievements::achievements_root
>
libftl::xml::achievements(
	std::istream &_input
)
{
	return
		libftl::impl::xml::read(
			_input,
			libftl::impl::xml::load_function<
				libftl::xml::generated::achievements::achievements_root
			>{
				[](
					std::istream &_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::achievements::achievements_root
				>
				{
					return
						libftl::xml::generated::achievements::root(
							_stream,
							xml_schema::flags::dont_validate
						);
				}
			}
		);
}
