#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/record.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("xml::typed::attribute_set", "[xml]")
{
  FCPPT_RECORD_MAKE_LABEL(attrib1);

  libftl::impl::xml::typed::attribute_set const attributes{fcppt::record::make(
      attrib1{} = libftl::impl::xml::typed::attribute<int>{std::string{"attrib1"}})};

  CHECK(attributes.parse(std::vector<libftl::impl::xml::attribute>{}).has_failure());

  CHECK(
      attributes
          .parse(std::vector<libftl::impl::xml::attribute>{libftl::impl::xml::attribute{"a1", "v1"}})
          .has_failure());

  CHECK(
      attributes
          .parse(std::vector<libftl::impl::xml::attribute>{libftl::impl::xml::attribute{"attrib1", "y"}})
          .has_failure());

  CHECK(
      attributes.parse(std::vector<libftl::impl::xml::attribute>{
          libftl::impl::xml::attribute{"attrib1", "10"}}) ==
      fcppt::either::make_success<libftl::error>(fcppt::record::make(attrib1{} = 10)));

  CHECK(attributes
            .parse(std::vector<libftl::impl::xml::attribute>{
                libftl::impl::xml::attribute{"attrib1", "10"},
                libftl::impl::xml::attribute{"attrib2", "v2"}})
            .has_failure());

  FCPPT_RECORD_MAKE_LABEL(attrib2);

  libftl::impl::xml::typed::attribute_set const attributes2{fcppt::record::make(
      attrib1{} = libftl::impl::xml::typed::attribute<int>{std::string{"attrib1"}},
	  attrib2{} = libftl::impl::xml::typed::attribute<unsigned>{std::string{"attrib2"}})};

  CHECK(
      attributes2.parse(std::vector<libftl::impl::xml::attribute>{
          libftl::impl::xml::attribute{"attrib1", "10"},
          libftl::impl::xml::attribute{"attrib2", "20"}}) ==
      fcppt::either::make_success<libftl::error>(
          fcppt::record::make(attrib1{} = 10, attrib2{} = 20U)));
}
