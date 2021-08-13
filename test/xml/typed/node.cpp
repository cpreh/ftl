#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/attribute_list.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/node.hpp>
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
#include <fcppt/tuple/comparison.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::node", "[xml]")
{
  auto const parser{libftl::impl::xml::typed::node{
      std::string{"test"},
      libftl::impl::xml::typed::attribute_list{fcppt::record::make()},
      libftl::impl::xml::typed::empty{}}};

  CHECK(parser
            .parse(libftl::impl::xml::node{
                std::string{"x"},
                std::vector<libftl::impl::xml::attribute>{},
                fcppt::optional::nothing{}})
            .has_failure());

  CHECK(
      parser.parse(libftl::impl::xml::node{
          std::string{"test"},
          std::vector<libftl::impl::xml::attribute>{},
          fcppt::optional::nothing{}}) ==
      fcppt::either::make_success<libftl::error>(
          fcppt::tuple::make(fcppt::record::make(), fcppt::unit{})));
}
