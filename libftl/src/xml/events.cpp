#include <libftl/impl/xml/load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/events.hpp>
#include <libftl/xml/generated/events.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <memory>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::events::events_root
>
libftl::xml::events(
	std::istream &_input
)
{
	return
		libftl::impl::xml::read(
			_input,
			libftl::impl::xml::load_function<
				libftl::xml::generated::events::events_root
			>{
				[](
					std::istream &_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::events::events_root
				>
				{
					return
						libftl::xml::generated::events::root(
							_stream,
							xml_schema::flags::dont_validate
						);
				}
			}
		);
}
