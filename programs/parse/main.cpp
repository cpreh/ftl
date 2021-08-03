#include <ftl/parse/ship/arguments.hpp>
#include <ftl/parse/ship/main.hpp>
#include <ftl/parse/ship/options_parser.hpp>
#include <ftl/parse/xml/arguments.hpp>
#include <ftl/parse/xml/main.hpp>
#include <ftl/parse/xml/options_parser.hpp>
#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/options/create_resource_parser.hpp>
#include <libftl/options/open_archive.hpp>
#include <libftl/options/resource_label.hpp>
#include <libftl/options/resource_record.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/either/no_error.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/make_commands.hpp>
#include <fcppt/options/make_sub_command.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/options/sub_command_label.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>

namespace
{
FCPPT_RECORD_MAKE_LABEL(ship_label);

FCPPT_RECORD_MAKE_LABEL(xml_label);

using ship_command_arguments =
    fcppt::record::object<fcppt::record::element<ship_label, ftl::parse::ship::arguments>>;

using xml_command_arguments =
    fcppt::record::object<fcppt::record::element<xml_label, ftl::parse::xml::arguments>>;

using arguments = fcppt::record::object<
    fcppt::record::element<fcppt::options::options_label, libftl::options::resource_record>,
    fcppt::record::element<
        fcppt::options::sub_command_label,
        fcppt::variant::object<ship_command_arguments, xml_command_arguments>>>;

bool main_program(arguments const &_args)
{
  return fcppt::either::match(
      fcppt::either::bind(
          libftl::options::open_archive(fcppt::record::get<libftl::options::resource_label>(
              fcppt::record::get<fcppt::options::options_label>(_args))),
          [&_args](libftl::archive::base_unique_ptr &&_archive)
          {
            return fcppt::variant::match(
                fcppt::record::get<fcppt::options::sub_command_label>(_args),
                [&_archive](ship_command_arguments const &_ship_args) {
                  return ftl::parse::ship::main(
                      *_archive, fcppt::record::get<ship_label>(_ship_args));
                },
                [&_archive](xml_command_arguments const &_xml_args) {
                  return ftl::parse::xml::main(*_archive, fcppt::record::get<xml_label>(_xml_args));
                });
          }),
      [](libftl::error const &_error)
      {
        fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

        return false;
      },
      [](fcppt::either::no_error const &) { return true; });
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

int FCPPT_MAIN(int argc, fcppt::args_char **argv)
try
{
  auto const ship_command{fcppt::options::make_sub_command<ship_label>(
      FCPPT_TEXT("ship"),
      ftl::parse::ship::options_parser(),
      fcppt::options::optional_help_text{
          fcppt::options::help_text{FCPPT_TEXT("Parse a ship layout file")}})};

  auto const xml_command{fcppt::options::make_sub_command<xml_label>(
      FCPPT_TEXT("xml"),
      ftl::parse::xml::options_parser(),
      fcppt::options::optional_help_text{
          fcppt::options::help_text{FCPPT_TEXT("Parse an xml file")}})};

  auto const parser{fcppt::options::make_commands(
      libftl::options::create_resource_parser(),
      fcppt::make_cref(ship_command),
      fcppt::make_cref(xml_command))};

  using parser_type = decltype(parser);

  return fcppt::variant::match(
             fcppt::options::parse_help(
                 fcppt::options::default_help_switch(),
                 parser,
                 fcppt::args_from_second(argc, argv)),
             [](fcppt::options::result<fcppt::options::result_of<parser_type>> const &_result)
             {
               return fcppt::either::match(
                   _result,
                   [](fcppt::options::error const &_error)
                   {
                     fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

                     return false;
                   },
                   [](fcppt::options::result_of<parser_type> const &_args)
                   { return main_program(fcppt::record::permute<arguments>(_args)); });
             },
             [](fcppt::options::help_text const &_help_text)
             {
               fcppt::io::cout() << _help_text << FCPPT_TEXT('\n');

               return true;
             })
             ? EXIT_SUCCESS
             : EXIT_FAILURE;
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
