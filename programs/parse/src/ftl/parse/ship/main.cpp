#include <ftl/parse/path_label.hpp>
#include <ftl/parse/ship/arguments.hpp>
#include <ftl/parse/ship/main.hpp>
#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/output.hpp>
#include <libftl/ship/layout/parse.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/error.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/no_error.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>

fcppt::either::error<libftl::error> ftl::parse::ship::main(
    libftl::archive::base const &_archive, ftl::parse::ship::arguments const &_arguments)
{
  return fcppt::either::map(
      fcppt::either::bind(
          _archive.open(fcppt::record::get<ftl::parse::path_label>(_arguments)),
          [](fcppt::unique_ptr<std::istream> &&_stream)
          { return libftl::ship::layout::parse(*_stream); }),
      [](libftl::ship::layout::object const &_layout)
      {
        fcppt::io::cout() << _layout << FCPPT_TEXT('\n');

        return fcppt::either::no_error{};
      });
}
