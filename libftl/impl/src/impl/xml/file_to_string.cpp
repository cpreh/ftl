#include <libftl/impl/xml/file_to_string.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/maybe_back.hpp>
#include <fcppt/container/pop_back.hpp>
#include <fcppt/io/peek.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace
{
void remove_char(std::istream &_stream, char const _ch)
{
  fcppt::optional::maybe_void(
      fcppt::io::peek(_stream),
      [_ch, &_stream](char const _first)
      {
        if (_first == _ch)
        {
          _stream.get();
        }
      });
}

void remove_bom(std::istream &_stream)
{
  remove_char(
      _stream,
      fcppt::literal<char>(
          239 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));

  remove_char(
      _stream,
      fcppt::literal<char>(
          187 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));

  remove_char(
      _stream,
      fcppt::literal<char>(
          191 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));
}

std::string read_file(std::istream &_stream)
{
  std::string result{};

  std::string line{};

  while (std::getline(_stream, line))
  {
    fcppt::optional::maybe_void(
        fcppt::container::maybe_back(line),
        [&line](fcppt::reference<char> const _back)
        {
          if (_back.get() == '\r')
          {
            fcppt::container::pop_back(line);
          }
        });

    fcppt::optional::maybe_void(
        fcppt::container::maybe_back(line),
        [&line](fcppt::reference<char> const _back)
        {
          if (_back.get() != '\n')
          {
            line.push_back('\n');
          }
        });

    result += line;
  }

  return result;
}

}

std::string libftl::impl::xml::file_to_string(std::istream &_stream)
{
  remove_bom(_stream);

  return read_file(_stream);
}
