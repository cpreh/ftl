#include <libftl/archive/index_error.hpp>
#include <alda/raw/stream/error_output.hpp>
#include <fcppt/io/ostream_fwd.hpp>

fcppt::io::ostream &
libftl::archive::operator<<(fcppt::io::ostream &_stream, libftl::archive::index_error const &_error)
{
  return _stream << _error.value_;
}
