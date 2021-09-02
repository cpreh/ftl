#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/node_output.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/unit_comparison.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/unit_output.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/record.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::node_member", "[xml]")
{
  auto const parser{libftl::impl::xml::typed::make_node_member<
      libftl::impl::xml::typed::required::yes>(
      std::string{"test"},
      libftl::impl::xml::typed::attribute_set{fcppt::record::make()},
      libftl::impl::xml::typed::empty{})};

  libftl::impl::xml::node const node{
      fcppt::optional::nothing{},
      std::string{"test"},
      std::vector<libftl::impl::xml::attribute>{},
      fcppt::optional::nothing{}};

  using arg_type = std::vector<fcppt::reference<libftl::impl::xml::node const>>;

  CHECK(
      parser.parse(arg_type{fcppt::make_cref(node)}) ==
      fcppt::either::make_success<libftl::error>(
          libftl::xml::node{fcppt::record::make(), fcppt::unit{}}));
}
