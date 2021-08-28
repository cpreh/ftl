#include <ftl/parse/path_label.hpp>
#include <ftl/parse/xml/arguments.hpp>
#include <ftl/parse/xml/main.hpp>
#include <ftl/parse/xml/type.hpp>
#include <ftl/parse/xml/type_label.hpp>
#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/xml/achievements/load.hpp>
#include <libftl/xml/achievements/result.hpp>
#include <libftl/xml/animations.hpp>
#include <libftl/xml/blueprints.hpp>
#include <libftl/xml/events.hpp>
#include <libftl/xml/node_output.hpp>
#include <libftl/xml/sectors.hpp>
#include <libftl/xml/ship/load.hpp>
#include <libftl/xml/ship/slide_output.hpp>
#include <libftl/xml/ship/result.hpp>
#include <libftl/xml/generated/animations.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <libftl/xml/generated/events.hpp>
#include <libftl/xml/generated/sectors.hpp>
#include <fcppt/output.hpp>
#include <fcppt/output_range.hpp>
#include <fcppt/output_string.hpp>
#include <fcppt/overload.hpp>
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
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::error<libftl::error> ftl::parse::xml::main( // NOLINT(bugprone-exception-escape)
    libftl::archive::base &_archive,
    ftl::parse::xml::arguments const &_args)
{
  using result_type = fcppt::variant::object<
      libftl::xml::achievements::result,
      fcppt::unique_ptr<libftl::xml::generated::animations::animations_root>,
      fcppt::unique_ptr<libftl::xml::generated::blueprints::blueprints_root>,
      fcppt::unique_ptr<libftl::xml::generated::events::events_root>,
      fcppt::unique_ptr<libftl::xml::generated::sectors::sectors_root>,
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
          return fcppt::either::map(libftl::xml::animations(*_stream), wrap_result);
        case ftl::parse::xml::type::blueprints:
          return fcppt::either::map(libftl::xml::blueprints(*_stream), wrap_result);
        case ftl::parse::xml::type::events:
          return fcppt::either::map(libftl::xml::events(*_stream), wrap_result);
        case ftl::parse::xml::type::sectors:
          return fcppt::either::map(libftl::xml::sectors(*_stream), wrap_result);
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
            fcppt::overload(
                [](auto const &_element) { fcppt::io::cout() << *_element; },
                [](libftl::xml::achievements::result const &_achievements)
                { fcppt::io::cout() << fcppt::output(_achievements); },
                [](libftl::xml::ship::result const &_ship)
                { fcppt::io::cout() << fcppt::output(_ship); }),
            _result);
        fcppt::io::cout() << FCPPT_TEXT('\n');
        return fcppt::either::no_error{};
      });
}
