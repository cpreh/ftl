#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/unit_comparison.hpp>
#include <fcppt/unit_output.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/optional.hpp>
#include <fcppt/catch/record.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN

TEST_CASE("xml::typed::node_set", "[xml]")
{
  FCPPT_RECORD_MAKE_LABEL(node1);

  libftl::impl::xml::typed::node_set const parser{fcppt::record::make(
      node1{} = libftl::impl::xml::typed::make_node_member<libftl::impl::xml::typed::required::yes>(
          std::string{"node1"},
          libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
          libftl::impl::xml::typed::empty{}))};

  CHECK(parser.parse(libftl::impl::xml::node_vector{}).has_failure());

  CHECK(
      parser.parse(fcppt::container::make<libftl::impl::xml::node_vector>(
          fcppt::make_recursive(libftl::impl::xml::node{
              fcppt::optional::nothing{},
              std::string{"node1"},
              std::vector<libftl::impl::xml::attribute>{},
              fcppt::optional::nothing{}}))) ==
      fcppt::either::make_success<libftl::error>(
          fcppt::record::make(node1{} = libftl::xml::node{fcppt::record::make(), fcppt::unit()})));

  libftl::impl::xml::typed::node_set const parser2{fcppt::record::make(
      node1{} = libftl::impl::xml::typed::make_node_member<libftl::impl::xml::typed::required::no>(
          std::string{"node1"},
          libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
          libftl::impl::xml::typed::empty{}))};

  CHECK(
      parser2.parse(libftl::impl::xml::node_vector{}) ==
      fcppt::either::make_success<libftl::error>(fcppt::record::make(
          node1{} = fcppt::optional::object<
              libftl::xml::node<fcppt::record::object<>, fcppt::unit>>{})));
}

FCPPT_CATCH_END
