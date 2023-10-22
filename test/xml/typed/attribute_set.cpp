#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/optional.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/record.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/record/make.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("xml::typed::attribute_set", "[xml]")
{
  FCPPT_RECORD_MAKE_LABEL(attrib1);

  libftl::impl::xml::typed::attribute_set const attributes{fcppt::record::make(
      attrib1{} = libftl::impl::xml::typed::attribute<int, libftl::impl::xml::typed::required::yes>{
          std::string{"attrib1"}})};

  CHECK(attributes.parse(std::vector<libftl::impl::xml::attribute>{}).has_failure());

  CHECK(attributes
            .parse(std::vector<libftl::impl::xml::attribute>{
                libftl::impl::xml::attribute{fcppt::optional::nothing{}, "a1", "v1"}})
            .has_failure());

  CHECK(attributes
            .parse(std::vector<libftl::impl::xml::attribute>{
                libftl::impl::xml::attribute{fcppt::optional::nothing{}, "attrib1", "y"}})
            .has_failure());

  CHECK(
      attributes.parse(std::vector<libftl::impl::xml::attribute>{
          libftl::impl::xml::attribute{fcppt::optional::nothing{}, "attrib1", "10"}}) ==
      fcppt::either::make_success<libftl::error>(fcppt::record::make(attrib1{} = 10)));

  CHECK(attributes
            .parse(std::vector<libftl::impl::xml::attribute>{
                libftl::impl::xml::attribute{fcppt::optional::nothing{}, "attrib1", "10"},
                libftl::impl::xml::attribute{fcppt::optional::nothing{}, "attrib2", "v2"}})
            .has_failure());

  FCPPT_RECORD_MAKE_LABEL(attrib2);

  libftl::impl::xml::typed::attribute_set const attributes2{fcppt::record::make(
      attrib1{} =
          libftl::impl::xml::typed::attribute<int, libftl::impl::xml::typed::required::yes>{
              std::string{"attrib1"}},
      attrib2{} =
          libftl::impl::xml::typed::attribute<unsigned, libftl::impl::xml::typed::required::yes>{
              std::string{"attrib2"}})};

  CHECK(
      attributes2.parse(std::vector<libftl::impl::xml::attribute>{
          libftl::impl::xml::attribute{fcppt::optional::nothing{}, "attrib1", "10"},
          libftl::impl::xml::attribute{fcppt::optional::nothing{}, "attrib2", "20"}}) ==
      fcppt::either::make_success<libftl::error>(
          fcppt::record::make(attrib1{} = 10, attrib2{} = 20U)));

  libftl::impl::xml::typed::attribute_set const attributes3{fcppt::record::make(
      attrib1{} = libftl::impl::xml::typed::attribute<int, libftl::impl::xml::typed::required::no>{
          std::string{"attrib1"}})};

  CHECK(
      attributes3.parse(std::vector<libftl::impl::xml::attribute>{}) ==
      fcppt::either::make_success<libftl::error>(
          fcppt::record::make(attrib1{} = fcppt::optional::object<int>{})));
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
