#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/node_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/make_recursive.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/unit.hpp>
#include <fcppt/unit_comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/unit_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/record.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/container/make.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/record/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("xml::typed::node_list", "[xml]")
{
  libftl::impl::xml::typed::node_list const parser{libftl::impl::xml::typed::node{
      std::string{"node1"},
      libftl::impl::xml::typed::node_content{
          libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
          libftl::impl::xml::typed::empty{}}}};

  using result_vector = std::vector<libftl::xml::node<fcppt::record::object<>, fcppt::unit>>;

  CHECK(
      parser.parse(libftl::impl::xml::node_vector{}) ==
      fcppt::either::make_success<libftl::error>(result_vector{}));

  CHECK(
      parser.parse(fcppt::container::make<libftl::impl::xml::node_vector>(
          fcppt::make_recursive(libftl::impl::xml::node{
              fcppt::optional::nothing{},
              std::string{"node1"},
              std::vector<libftl::impl::xml::attribute>{},
              fcppt::optional::nothing{}}))) ==
      fcppt::either::make_success<libftl::error>(
          result_vector{libftl::xml::node{fcppt::record::make(), fcppt::unit{}}}));

  CHECK(parser
            .parse(fcppt::container::make<libftl::impl::xml::node_vector>(
                fcppt::make_recursive(libftl::impl::xml::node{
                    fcppt::optional::nothing{},
                    std::string{"node2"},
                    std::vector<libftl::impl::xml::attribute>{},
                    fcppt::optional::nothing{}})))
            .has_failure());

  CHECK(
      parser.parse(fcppt::container::make<libftl::impl::xml::node_vector>(
          fcppt::make_recursive(libftl::impl::xml::node{
              fcppt::optional::nothing{},
              std::string{"node1"},
              std::vector<libftl::impl::xml::attribute>{},
              fcppt::optional::nothing{}}),
          fcppt::make_recursive(libftl::impl::xml::node{
              fcppt::optional::nothing{},
              std::string{"node1"},
              std::vector<libftl::impl::xml::attribute>{},
              fcppt::optional::nothing{}}))) ==
      fcppt::either::make_success<libftl::error>(result_vector{
          libftl::xml::node{fcppt::record::make(), fcppt::unit{}},
          libftl::xml::node{fcppt::record::make(), fcppt::unit{}}}));
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
