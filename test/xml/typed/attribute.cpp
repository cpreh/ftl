#include <libftl/error.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_map.hpp>
#include <libftl/impl/xml/typed/attribute_required.hpp>
#include <libftl/impl/xml/typed/attribute_used.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/optional.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/catch/tuple.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/tuple/comparison.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::attribute", "[xml]")
{
  libftl::impl::xml::typed::attribute<int> const required_int{std::string{"attrib1"}};

  CHECK(
      required_int.parse(libftl::impl::xml::typed::attribute_map{
          std::make_pair(std::string{"attrib1"}, std::string{"12"}),
          std::make_pair(std::string{"attrib2"}, std::string{"test"})}) ==
      fcppt::tuple::make(
          libftl::impl::xml::typed::attribute_used{fcppt::optional::make(std::string{"attrib1"})},
          fcppt::either::make_success<libftl::error>(12)));

  {
    auto const result{
      required_int.parse(libftl::impl::xml::typed::attribute_map{
          std::make_pair(std::string{"attrib2"}, std::string{"test"})})};

    CHECK_FALSE(fcppt::tuple::get<0>(result).get().has_value());

    CHECK(fcppt::tuple::get<1>(result).has_failure());
  }

  {
    auto const result{
      required_int.parse(libftl::impl::xml::typed::attribute_map{
          std::make_pair(std::string{"attrib1"}, std::string{"test"})})};

    CHECK(fcppt::tuple::get<0>(result).get().has_value());

    CHECK(fcppt::tuple::get<1>(result).has_failure());
  }

  libftl::impl::xml::typed::attribute<int, libftl::impl::xml::typed::attribute_required::no> const
      optional_int{std::string{"attrib1"}};

  CHECK(
      optional_int.parse(libftl::impl::xml::typed::attribute_map{
          std::make_pair(std::string{"attrib1"}, std::string{"12"}),
          std::make_pair(std::string{"attrib2"}, std::string{"test"})}) ==
      fcppt::tuple::make(
          libftl::impl::xml::typed::attribute_used{fcppt::optional::make(std::string{"attrib1"})},
          fcppt::either::make_success<libftl::error>(fcppt::optional::make(12))));

  CHECK(
      optional_int.parse(libftl::impl::xml::typed::attribute_map{
          std::make_pair(std::string{"attrib2"}, std::string{"test"})}) ==
      fcppt::tuple::make(
          libftl::impl::xml::typed::attribute_used{fcppt::optional::nothing{}},
          fcppt::either::make_success<libftl::error>(fcppt::optional::object<int>{})));

  {
    auto const result{
      optional_int.parse(libftl::impl::xml::typed::attribute_map{
          std::make_pair(std::string{"attrib1"}, std::string{"test"})})};

    CHECK(fcppt::tuple::get<0>(result).get() == fcppt::optional::make(std::string{"attrib1"}));

    CHECK(fcppt::tuple::get<1>(result).has_failure());
  }
}
