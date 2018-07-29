#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/achievements.hpp>
#include <libftl/xml/generated/achievements.hpp>


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
			LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(
				achievements
			)
		);
}
