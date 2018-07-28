#include <libftl/archive/path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


libftl::archive::path::path()
:
	rep_{}
{
}

std::string const &
libftl::archive::path::rep() const
{
	return
		rep_;
}

void
libftl::archive::path::add(
	std::string &&_name
)
{
	rep_ +=
		"/"
		+
		std::move(
			_name
		);
}

libftl::archive::path
libftl::archive::operator/(
	libftl::archive::path &&_path,
	std::string &&_name
)
{
	_path.add(
		std::move(
			_name
		)
	);

	return
		std::move(
			_path
		);
}
