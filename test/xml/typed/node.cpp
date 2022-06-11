#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/node_output.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/unit_comparison.hpp>
#include <fcppt/unit_output.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/record.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN

TEST_CASE("xml::typed::node", "[xml]")
{
  auto const parser{libftl::impl::xml::typed::node{
      std::string{"test"},
      libftl::impl::xml::typed::node_content{
          libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
          libftl::impl::xml::typed::empty{}}}};

  CHECK(parser
            .parse(libftl::impl::xml::node{
                fcppt::optional::nothing{},
                std::string{"x"},
                std::vector<libftl::impl::xml::attribute>{},
                fcppt::optional::nothing{}})
            .has_failure());

  CHECK(
      parser.parse(libftl::impl::xml::node{
          fcppt::optional::nothing{},
          std::string{"test"},
          std::vector<libftl::impl::xml::attribute>{},
          fcppt::optional::nothing{}}) ==
      fcppt::either::make_success<libftl::error>(
          libftl::xml::node{fcppt::record::make(), fcppt::unit{}}));
}

FCPPT_CATCH_END
