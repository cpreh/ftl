#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/ship/layout/name.hpp>
#include <libftl/ship/layout/load_xml.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <libftl/xml/ship.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


fcppt::either::object<
	libftl::error,
	fcppt::unique_ptr<
		libftl::xml::generated::ship::ship_root
	>
>
libftl::ship::layout::load_xml(
	libftl::archive::base &_archive,
	libftl::ship::layout::name const _name
)
{
	return
		fcppt::either::bind(
			_archive.open(libftl::archive::path{"data"} / (_name.get() + ".xml")),
			[](fcppt::unique_ptr<std::istream> &&_stream)
			{
				return
					libftl::xml::ship(*_stream);
			}
		);
}
