#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::attribute", "[xml]")
{
  libftl::impl::xml::typed::attribute<int, libftl::impl::xml::typed::required::yes> const attribute{
      std::string{"test"}};

  CHECK(attribute.parse(libftl::impl::xml::attribute{fcppt::optional::nothing{}, "test", "x"})
            .has_failure());

  CHECK(
      attribute.parse(libftl::impl::xml::attribute{fcppt::optional::nothing{}, "test", "10"}) ==
      fcppt::either::make_success<libftl::error>(10));
}
