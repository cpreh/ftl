#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN

TEST_CASE("xml::typed::empty", "[xml]")
{
  libftl::impl::xml::typed::empty const parser{};

  CHECK(parser.parse(fcppt::optional::object<libftl::impl::xml::inner_node>{}).has_success());

  CHECK(parser
            .parse(fcppt::optional::make(libftl::impl::xml::inner_node{
                libftl::impl::xml::inner_node_content{std::string{}}, std::string{}}))
            .has_failure());

  CHECK(parser
            .parse(fcppt::optional::make(libftl::impl::xml::inner_node{
                libftl::impl::xml::inner_node_content{libftl::impl::xml::node_vector{}},
                std::string{}}))
            .has_failure());
}

FCPPT_CATCH_END
