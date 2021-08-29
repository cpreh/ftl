#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/make_construct.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/node_output.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/unit_comparison.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/unit_output.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/record.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/catch/variant.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/output.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::alternative", "[xml]")
{
  using inner_result = libftl::xml::node<fcppt::record::object<>,fcppt::unit>;
  FCPPT_MAKE_STRONG_TYPEDEF(inner_result, left);
  FCPPT_MAKE_STRONG_TYPEDEF(inner_result, right);
  using result_type = fcppt::variant::object<left, right>;

  auto const parser{libftl::impl::xml::typed::alternative{
      libftl::impl::xml::typed::make_construct<left>(libftl::impl::xml::typed::node{
          std::string{"test1"},
          libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
          libftl::impl::xml::typed::empty{}}),
      libftl::impl::xml::typed::make_construct<right>(libftl::impl::xml::typed::node{
          std::string{"test2"},
          libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
          libftl::impl::xml::typed::empty{}})}};

  CHECK(parser
            .parse(libftl::impl::xml::node{
                std::string{"x"},
                std::vector<libftl::impl::xml::attribute>{},
                fcppt::optional::nothing{}})
            .has_failure());

  CHECK(
      parser.parse(libftl::impl::xml::node{
          std::string{"test1"},
          std::vector<libftl::impl::xml::attribute>{},
          fcppt::optional::nothing{}}) ==
      fcppt::either::make_success<libftl::error>(
          result_type{left{libftl::xml::node{fcppt::record::make(), fcppt::unit{}}}}));
}