#include <libftl/archive/extract.hpp>
#include <libftl/archive/file.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/io/optional_buffer.hpp>
#include <fcppt/io/read_chars.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <istream>
#include <fcppt/config/external_end.hpp>


fcppt::io::optional_buffer
libftl::archive::extract(
	libftl::archive::file const &_file
)
{
	_file.stream.get().seekg(
		_file.entry.offset.get(),
		std::ios_base::beg
	);

	return
		fcppt::io::read_chars(
			_file.stream.get(),
			fcppt::cast::to_unsigned(
				_file.entry.length.get()
			)
		);
}
