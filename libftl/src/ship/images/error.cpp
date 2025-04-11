#include <libftl/ship/images/error.hpp>
#include <libftl/sprite/load_error.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>

fcppt::io::ostream &libftl::ship::images::operator<<(
    fcppt::io::ostream &_stream, libftl::ship::images::error const &_error)
{
  return _stream << _error.error1_ << FCPPT_TEXT('\n') << _error.error2_ << FCPPT_TEXT('\n');
}
