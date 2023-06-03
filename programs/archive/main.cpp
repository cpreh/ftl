#include <libftl/error.hpp>
#include <libftl/archive/entry_output.hpp>
#include <libftl/archive/extract.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/archive/index.hpp>
#include <libftl/archive/read_index.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/error_code_to_string.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/output_pair.hpp>
#include <fcppt/output_string.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/either/error.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/either/no_error.hpp>
#include <fcppt/either/sequence_error.hpp>
#include <fcppt/filesystem/create_directories_recursive.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/write_chars.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_optional.hpp>
#include <fcppt/options/no_default_value.hpp>
#include <fcppt/options/option.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/options/short_name.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <system_error>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wmissing-prototypes)
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

namespace
{
using either_error = fcppt::either::error<fcppt::string>;

either_error write_to_file(std::filesystem::path const &_path, fcppt::io::buffer const &_buffer)
{
  return fcppt::either::bind(
      fcppt::either::from_optional(
          fcppt::filesystem::open<std::ofstream>(_path, std::ios_base::binary),
          [&_path]
          { return FCPPT_TEXT("Failed to open ") + fcppt::filesystem::path_to_string(_path); }),
      [&_path, &_buffer](std::ofstream &&_stream)
      {
        fcppt::io::cout() << FCPPT_TEXT("Extracting ") << fcppt::filesystem::path_to_string(_path)
                          << FCPPT_TEXT('\n');

        return fcppt::io::write_chars(_stream, _buffer.data(), _buffer.size())
                   ? either_error{fcppt::either::no_error{}}
                   : either_error{
                         FCPPT_TEXT("Failed to write ") + fcppt::filesystem::path_to_string(_path)};
      });
}

either_error write_output(
    std::istream &_stream,
    std::filesystem::path const &_output_path,
    libftl::archive::index::value_type const &_entry)
{
  std::filesystem::path const output_directory{(_output_path / _entry.first).remove_filename()};

  return fcppt::optional::maybe(
      fcppt::filesystem::create_directories_recursive(output_directory),
      [&_stream, &_output_path, &_entry]
      {
        return fcppt::optional::maybe(
            libftl::archive::extract(
                libftl::archive::file{fcppt::make_ref(_stream), _entry.second}),
            [&_entry]() {
              return either_error{
                  FCPPT_TEXT("Failed to extract ") + fcppt::output_to_fcppt_string(_entry)};
            },
            [&_output_path, &_entry](fcppt::io::buffer &&_buffer)
            { return write_to_file(_output_path / _entry.first, _buffer); });
      },
      [&output_directory](std::error_code const _error)
      {
        return either_error{
            FCPPT_TEXT("Failed to create directory ") +
            fcppt::filesystem::path_to_string(output_directory) + FCPPT_TEXT(" - ") +
            fcppt::error_code_to_string(_error)};
      });
}

either_error create_outputs(
    std::istream &_stream,
    std::filesystem::path const &_output_path,
    libftl::archive::index const &_index)
{
  return fcppt::either::sequence_error(
      _index,
      [&_stream, &_output_path](libftl::archive::index::value_type const &_entry)
      { return write_output(_stream, _output_path, _entry); });
}

FCPPT_RECORD_MAKE_LABEL(path_label);

FCPPT_RECORD_MAKE_LABEL(output_path_label);

using argument_record = fcppt::record::object<
    fcppt::record::element<path_label, std::filesystem::path>,
    fcppt::record::element<output_path_label, fcppt::optional::object<std::filesystem::path>>>;

int main_program(argument_record const &_arguments)
{
  std::filesystem::path const &path{fcppt::record::get<path_label>(_arguments)};

  return fcppt::optional::maybe(
      fcppt::filesystem::open<std::ifstream>(path, std::ios_base::binary),
      [&path]
      {
        fcppt::io::cerr() << FCPPT_TEXT("Cannot open ") << fcppt::filesystem::path_to_string(path)
                          << FCPPT_TEXT('\n');

        return EXIT_FAILURE;
      },
      [&_arguments](std::ifstream &&_stream)
      {
        return fcppt::either::match(
            libftl::archive::read_index(_stream),
            [](libftl::error const &_error)
            {
              fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

              return EXIT_FAILURE;
            },
            [&_stream, &_arguments](libftl::archive::index const &_index)
            {
              return fcppt::optional::maybe(
                  fcppt::record::get<output_path_label>(_arguments),
                  [&_index]
                  {
                    fcppt::io::cout() << fcppt::container::output(_index) << FCPPT_TEXT('\n');

                    return EXIT_SUCCESS;
                  },
                  [&_stream, &_index](std::filesystem::path const &_output_path)
                  {
                    return fcppt::either::match(
                        create_outputs(_stream, _output_path, _index),
                        [](fcppt::string const &_error)
                        {
                          fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

                          return EXIT_FAILURE;
                        },
                        [](fcppt::either::no_error) { return EXIT_SUCCESS; });
                  });
            });
      });
}

}

int FCPPT_MAIN(int argc, fcppt::args_char **argv)
try
{
  auto const parser{fcppt::options::apply(
      fcppt::options::argument<path_label, std::filesystem::path>{
          fcppt::options::long_name{FCPPT_TEXT("Path")},
          fcppt::options::optional_help_text{
              fcppt::options::help_text{FCPPT_TEXT("Path to the .dat file")}}},
      fcppt::options::make_optional(
          fcppt::options::option<output_path_label, std::filesystem::path>{
              fcppt::options::optional_short_name{fcppt::options::short_name{FCPPT_TEXT("o")}},
              fcppt::options::long_name{FCPPT_TEXT("output-path")},
              fcppt::options::no_default_value<std::filesystem::path>(),
              fcppt::options::optional_help_text{
                  fcppt::options::help_text{FCPPT_TEXT("Path to output the files to")}}}))};

  using parser_type = decltype(parser);

  return fcppt::variant::match(
      fcppt::options::parse_help(
          fcppt::options::default_help_switch(), parser, fcppt::args_from_second(argc, argv)),
      [](fcppt::options::result<fcppt::options::result_of<parser_type>> const &_result)
      {
        return fcppt::either::match(
            _result,
            [](fcppt::options::error const &_error)
            {
              fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

              return EXIT_FAILURE;
            },
            [](fcppt::options::result_of<parser_type> const &_arguments)
            { return main_program(fcppt::record::permute<argument_record>(_arguments)); });
      },
      [](fcppt::options::help_text const &_help_text)
      {
        fcppt::io::cout() << _help_text << FCPPT_TEXT('\n');

        return EXIT_SUCCESS;
      });
}
catch (fcppt::exception const &_error)
{
  fcppt::io::cerr() << _error.string() << FCPPT_TEXT('\n');

  return EXIT_FAILURE;
}
catch (std::exception const &_error)
{
  std::cerr << _error.what() << '\n';

  return EXIT_FAILURE;
}

FCPPT_PP_POP_WARNING
