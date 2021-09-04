#include <ftl/parse/path_label.hpp>
#include <ftl/parse/xml/arguments.hpp>
#include <ftl/parse/xml/main.hpp>
#include <ftl/parse/xml/type.hpp>
#include <ftl/parse/xml/type_label.hpp>
#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/xml/events/event_members.hpp>
#include <libftl/xml/events/event_members_output.hpp>
#include <libftl/xml/events/load.hpp>
#include <libftl/xml/events/result.hpp>
#include <libftl/xml/node_output.hpp>
#include <libftl/xml/achievements/load.hpp>
#include <libftl/xml/achievements/result.hpp>
#include <libftl/xml/animations/load.hpp>
#include <libftl/xml/animations/result.hpp>
#include <libftl/xml/blueprints/direction_output.hpp>
#include <libftl/xml/blueprints/load.hpp>
#include <libftl/xml/blueprints/result.hpp>
#include <libftl/xml/sectors/load.hpp>
#include <libftl/xml/sectors/result.hpp>
#include <libftl/xml/ship/load.hpp>
#include <libftl/xml/ship/result.hpp>
#include <libftl/xml/ship/slide_output.hpp>
#include <fcppt/output.hpp>
#include <fcppt/output_range.hpp>
#include <fcppt/output_string.hpp>
#include <fcppt/recursive_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unit_output.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/error.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/no_error.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/output.hpp>
#include <fcppt/tuple/output.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::error<libftl::error> ftl::parse::xml::main( // NOLINT(bugprone-exception-escape)
    libftl::archive::base const &_archive,
    ftl::parse::xml::arguments const &_args)
{
  using result_type = fcppt::variant::object<
      libftl::xml::achievements::result,
      libftl::xml::animations::result,
      libftl::xml::blueprints::result,
      libftl::xml::events::result,
      libftl::xml::sectors::result,
      libftl::xml::ship::result>;

  auto const load_xml(
      [&_args](fcppt::unique_ptr<std::istream> &&_stream)
          -> fcppt::either::object<libftl::error, result_type>
      {
        auto const wrap_result([](auto &&_result)
                               { return result_type{std::forward<decltype(_result)>(_result)}; });

        switch (fcppt::record::get<ftl::parse::xml::type_label>(_args))
        {
        case ftl::parse::xml::type::achievements:
          return fcppt::either::map(libftl::xml::achievements::load(*_stream), wrap_result);
        case ftl::parse::xml::type::animations:
          return fcppt::either::map(libftl::xml::animations::load(*_stream), wrap_result);
        case ftl::parse::xml::type::blueprints:
          return fcppt::either::map(libftl::xml::blueprints::load(*_stream), wrap_result);
        case ftl::parse::xml::type::events:
          return fcppt::either::map(libftl::xml::events::load(*_stream), wrap_result);
        case ftl::parse::xml::type::sectors:
          return fcppt::either::map(libftl::xml::sectors::load(*_stream), wrap_result);
        case ftl::parse::xml::type::ship:
          return fcppt::either::map(libftl::xml::ship::load(*_stream), wrap_result);
        }

        FCPPT_ASSERT_UNREACHABLE;
      });

  return fcppt::either::map(
      fcppt::either::bind(
          _archive.open(fcppt::record::get<ftl::parse::path_label>(_args)), load_xml),
      [](result_type const &_result)
      {
        fcppt::io::cout() << FCPPT_TEXT("SUCCESS:\n");
        fcppt::variant::apply(
            [](auto const &_element) { fcppt::io::cout() << fcppt::output(_element); }, _result);
        fcppt::io::cout() << FCPPT_TEXT('\n');
        return fcppt::either::no_error{};
      });
}
