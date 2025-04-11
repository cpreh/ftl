#include <libftl/archive/open_path_error.hpp>
#include <libftl/sprite/load_error.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/match.hpp>

fcppt::io::ostream &libftl::sprite::operator<<(fcppt::io::ostream &_stream, libftl::sprite::load_error const &_load_error)
{
  fcppt::variant::match(
    _load_error.value_,
    [&_stream](libftl::archive::open_path_error const &_error)
    {
      _stream << _error;
    },
    [&_stream](libftl::sprite::load_error::decode_error const &_error)
    {
      _stream << FCPPT_TEXT("Failed to decode image ")
      << _error.get()
      << FCPPT_TEXT('.');
    });

    return _stream;
}
