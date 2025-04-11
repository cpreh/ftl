#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/xml/type_error.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("xml::typed::content", "[xml]")
{
  libftl::impl::xml::typed::content<int> const parser{};

  CHECK(parser.parse(fcppt::optional::object<libftl::impl::xml::inner_node>{}).has_failure());

  CHECK(parser
            .parse(fcppt::optional::make(libftl::impl::xml::inner_node{
                libftl::impl::xml::inner_node_content{std::string{}}, std::string{}}))
            .has_failure());

  CHECK(parser
            .parse(fcppt::optional::make(libftl::impl::xml::inner_node{
                libftl::impl::xml::inner_node_content{libftl::impl::xml::node_vector{}},
                std::string{}}))
            .has_failure());

  CHECK(
      parser.parse(fcppt::optional::make(libftl::impl::xml::inner_node{
          libftl::impl::xml::inner_node_content{std::string{"123"}}, std::string{}})) ==
      fcppt::either::make_success<libftl::xml::type_error>(123));
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
