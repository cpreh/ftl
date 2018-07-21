#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/output.hpp>
#include <libftl/impl/xml/document_fwd.hpp>
#include <libftl/xml/clean.hpp>
#include <libftl/xml/error.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>


fcppt::either::object<
	libftl::xml::error,
	std::string
>
libftl::xml::clean(
	libftl::archive::file const &_file
)
{
	return
		fcppt::either::map(
			libftl::impl::xml::parse(
				_file
			),
			[](
				libftl::impl::xml::document const &_document
			)
			{
				std::ostringstream stream{};

				libftl::impl::xml::output(
					stream,
					_document
				);

				return
					stream.str();
			}
		);
}
