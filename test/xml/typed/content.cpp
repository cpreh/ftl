#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/make_inner_node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/parse.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::content", "[xml]")
{
  libftl::impl::xml::typed::content<int> const parser{};

  CHECK(libftl::impl::xml::typed::parse(
            parser, fcppt::optional::object<libftl::impl::xml::inner_node>{})
            .has_failure());

  CHECK(libftl::impl::xml::typed::parse(
            parser,
            fcppt::optional::make(libftl::impl::xml::make_inner_node(
                libftl::impl::xml::inner_node_content{std::string{}})))
            .has_failure());

  CHECK(libftl::impl::xml::typed::parse(
            parser,
            fcppt::optional::make(libftl::impl::xml::make_inner_node(
                libftl::impl::xml::inner_node_content{libftl::impl::xml::node_vector{}})))
            .has_failure());

  CHECK(
      libftl::impl::xml::typed::parse(
          parser,
          fcppt::optional::make(libftl::impl::xml::make_inner_node(
              libftl::impl::xml::inner_node_content{std::string{"123"}}))) ==
      fcppt::either::make_success<libftl::error>(123));
}
