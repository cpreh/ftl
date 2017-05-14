#include <libftl/archive/entry.hpp>
#include <libftl/archive/extract.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/io/optional_buffer.hpp>
#include <fcppt/io/read_chars.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <istream>
#include <fcppt/config/external_end.hpp>


fcppt::io::optional_buffer
libftl::archive::extract(
	std::istream &_stream,
	libftl::archive::entry const &_entry
)
{
	_stream.seekg(
		_entry.offset.get(),
		std::ios_base::beg
	);

	return
		fcppt::io::read_chars(
			_stream,
			fcppt::cast::to_unsigned(
				_entry.length.get()
			)
		);
}
