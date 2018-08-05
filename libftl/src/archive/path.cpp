#include <libftl/archive/path.hpp>
#include <fcppt/string.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/io/extract.hpp>
#include <fcppt/io/istream.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


libftl::archive::path::path(
	std::string &&_rep
)
:
	rep_{
		std::move(
			_rep
		)
	}
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

libftl::archive::path &
libftl::archive::path::operator+=(
	path &&_other
)
{
	rep_ =
		std::move(
			rep_
		)
		+
		"/"
		+
		std::move(
			_other.rep_
		);

	return
		*this;
}

libftl::archive::path
libftl::archive::operator+(
	libftl::archive::path &&_path1,
	libftl::archive::path &&_path2
)
{
	return
		_path1
		+=
		std::move(
			_path2
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

fcppt::io::istream &
libftl::archive::operator>>(
	fcppt::io::istream &_stream,
	libftl::archive::path &_path
)
{
	fcppt::optional::maybe_void(
		fcppt::io::extract<
			fcppt::string
		>(
			_stream
		),
		[
			&_path
		](
			fcppt::string &&_value
		)
		{
			_path =
				libftl::archive::path{
					fcppt::to_std_string(
						std::move(
							_value
						)
					)
				};
		}
	);

	return
		_stream;
}
