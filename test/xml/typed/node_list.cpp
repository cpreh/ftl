#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/unit_comparison.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/unit_output.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/record.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/catch/tuple.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/tuple/comparison.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::node_list", "[xml]")
{
  libftl::impl::xml::typed::node_list const parser{libftl::impl::xml::typed::node{
      std::string{"node1"},
      libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
      libftl::impl::xml::typed::empty{}}};

  using result_vector = std::vector<fcppt::tuple::object<fcppt::record::object<>, fcppt::unit>>;

  CHECK(
      parser.parse(std::vector<libftl::impl::xml::node>{}) ==
      fcppt::either::make_success<libftl::error>(result_vector{}));

  CHECK(
      parser.parse(std::vector<libftl::impl::xml::node>{libftl::impl::xml::node{
          std::string{"node1"},
          std::vector<libftl::impl::xml::attribute>{},
          fcppt::optional::nothing{}}}) ==
      fcppt::either::make_success<libftl::error>(
          result_vector{fcppt::tuple::make(fcppt::record::make(), fcppt::unit{})}));

  CHECK(parser
            .parse(std::vector<libftl::impl::xml::node>{libftl::impl::xml::node{
                std::string{"node2"},
                std::vector<libftl::impl::xml::attribute>{},
                fcppt::optional::nothing{}}})
            .has_failure());

  CHECK(
      parser.parse(std::vector<libftl::impl::xml::node>{
          libftl::impl::xml::node{
              std::string{"node1"},
              std::vector<libftl::impl::xml::attribute>{},
              fcppt::optional::nothing{}},
          libftl::impl::xml::node{
              std::string{"node1"},
              std::vector<libftl::impl::xml::attribute>{},
              fcppt::optional::nothing{}}}) ==
      fcppt::either::make_success<libftl::error>(result_vector{
          fcppt::tuple::make(fcppt::record::make(), fcppt::unit{}),
          fcppt::tuple::make(fcppt::record::make(), fcppt::unit{})}));
}
