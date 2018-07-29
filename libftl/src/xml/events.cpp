#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/events.hpp>
#include <libftl/xml/generated/events.hpp>


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
			LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(
				events
			)
		);
}
