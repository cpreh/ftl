#include <libftl/archive/entry.hpp>
#include <libftl/archive/entry_output.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>


fcppt::io::ostream &
libftl::archive::operator<<(
	fcppt::io::ostream &_stream,
	libftl::archive::entry const &_entry
)
{
	return
		_stream
		<<
		FCPPT_TEXT("offset: ")
		<<
		_entry.offset_
		<<
		FCPPT_TEXT(", length: ")
		<<
		_entry.length_;
}
