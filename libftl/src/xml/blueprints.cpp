#include <libftl/impl/xml/load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/blueprints.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <memory>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::blueprints::blueprints_root
>
libftl::xml::blueprints(
	std::istream &_input
)
{
	return
		libftl::impl::xml::read(
			_input,
			libftl::impl::xml::load_function<
				libftl::xml::generated::blueprints::blueprints_root
			>{
				[](
					std::istream &_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::blueprints::blueprints_root
				>
				{
					return
						libftl::xml::generated::blueprints::root(
							_stream,
							xml_schema::flags::dont_validate
						);
				}
			}
		);
}
