#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN

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
      fcppt::either::make_success<libftl::error>(123));
}

FCPPT_CATCH_END
