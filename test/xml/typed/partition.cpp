#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/make_construct.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/partition.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/node_output.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/unit_comparison.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/unit_output.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/record.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/catch/tuple.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/output.hpp>
#include <fcppt/tuple/comparison.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::partition", "[xml]")
{
  using inner_result = libftl::xml::node<fcppt::record::object<>,fcppt::unit>;
  FCPPT_MAKE_STRONG_TYPEDEF(inner_result, left);
  FCPPT_MAKE_STRONG_TYPEDEF(inner_result, right);

  auto const parser{libftl::impl::xml::typed::partition{
      libftl::impl::xml::typed::node_list{libftl::impl::xml::typed::alternative{
          libftl::impl::xml::typed::make_construct<left>(libftl::impl::xml::typed::node{
              std::string{"test1"},
              libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
              libftl::impl::xml::typed::empty{}}),
          libftl::impl::xml::typed::make_construct<right>(libftl::impl::xml::typed::node{
              std::string{"test2"},
              libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
              libftl::impl::xml::typed::empty{}})}}}};

  CHECK(parser
            .parse(fcppt::container::make<libftl::impl::xml::node_vector>(
                fcppt::make_recursive(libftl::impl::xml::node{
                    std::string{"x"},
                    std::vector<libftl::impl::xml::attribute>{},
                    fcppt::optional::nothing{}})))
            .has_failure());

  CHECK(
      parser.parse(fcppt::container::make<libftl::impl::xml::node_vector>(
          fcppt::make_recursive(libftl::impl::xml::node{
              std::string{"test1"},
              std::vector<libftl::impl::xml::attribute>{},
              fcppt::optional::nothing{}}),
          fcppt::make_recursive(libftl::impl::xml::node{
              std::string{"test2"},
              std::vector<libftl::impl::xml::attribute>{},
              fcppt::optional::nothing{}}))) ==
      fcppt::either::make_success<libftl::error>(fcppt::tuple::make(
          std::vector<left>{left{libftl::xml::node{fcppt::record::make(), fcppt::unit{}}}},
          std::vector<right>{right{libftl::xml::node{fcppt::record::make(), fcppt::unit{}}}})));
}
