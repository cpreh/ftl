#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_SET_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_SET_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/typed/is_attribute.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/loop_break_record.hpp>
#include <fcppt/algorithm/map_record.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/key_set.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/container/set_difference.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/construct.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/object_concept.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/element_vector.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/init.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/map_elements.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <unordered_map>
#include <type_traits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parsers>
class attribute_set
{
public:
  static_assert(fcppt::record::is_object<Parsers>::value);

  static_assert(fcppt::mpl::list::all_of<
                fcppt::mpl::list::map<
                    fcppt::record::element_vector<Parsers>,
                    fcppt::mpl::lambda<fcppt::record::element_to_type>>,
                fcppt::mpl::bind<
                    fcppt::mpl::lambda<libftl::impl::xml::typed::is_attribute>,
                    fcppt::mpl::bind<
                        fcppt::mpl::lambda<std::remove_cvref_t>,
                        fcppt::mpl::lambda<fcppt::deref_type>>>>::value);

  using result_type = fcppt::record::map_elements<
      Parsers,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<libftl::impl::xml::typed::result_type>,
          fcppt::mpl::lambda<fcppt::record::element_to_type>>>;

  using attribute_map = std::unordered_map<std::string, std::string>;

  explicit attribute_set(Parsers &&_parsers) : parsers_{std::move(_parsers)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<libftl::impl::xml::attribute> const &_attributes) const
  {
    return fcppt::either::bind(
        attribute_set::make_attribute_map(_attributes),
        [this](attribute_map const &_attribute_map) { return this->run_parsers(_attribute_map); });
  }

private:
  [[nodiscard]] static fcppt::either::object<libftl::error, attribute_map>
  make_attribute_map(std::vector<libftl::impl::xml::attribute> const &_attributes)
  {
    return fcppt::algorithm::fold(
        _attributes,
        fcppt::either::make_success<libftl::error>(attribute_map{}),
        [](libftl::impl::xml::attribute const &_attrib,
           fcppt::either::object<libftl::error, attribute_map> &&_map)
        {
          return fcppt::either::bind(
              std::move(_map),
              [&_attrib](attribute_map &&_inner_map)
              {
                if (_inner_map.contains(_attrib.name_))
                {
                  return fcppt::either::make_failure<attribute_map>(libftl::error{
                      fcppt::string{FCPPT_TEXT("Attribute ")} +
                      fcppt::from_std_string(_attrib.name_) +
                      FCPPT_TEXT(" specified multiple times.")});
                }
                _inner_map.insert(std::make_pair(_attrib.name_, _attrib.value_));
                return fcppt::either::make_success<libftl::error>(_inner_map);
              });
        });
  }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  run_parsers(attribute_map const &_attributes) const
  {
    using init_type = fcppt::record::map_elements<
        result_type,
        fcppt::mpl::bind<
            fcppt::mpl::lambda<fcppt::either::object>,
            fcppt::mpl::constant<libftl::error>,
            fcppt::mpl::lambda<fcppt::record::element_to_type>>>;

    std::set<std::string> used{};

    return fcppt::either::bind(
        fcppt::either::sequence<fcppt::either::object<libftl::error, result_type>>(
            fcppt::record::init<init_type>(
                [&_attributes, &used, this]<typename Label, fcppt::either::object_concept Type>(
                    fcppt::record::element<Label, Type> const &)
                { return this->parse_one(_attributes, fcppt::make_ref(used), Label{}); })),
        [&used, &_attributes](result_type &&_result)
        {
          std::set<std::string> const unused_keys{fcppt::container::set_difference(
              fcppt::container::key_set<std::set<std::string>>(_attributes), used)};
          return fcppt::either::construct(
              unused_keys.empty(),
              [&_result] { return std::move(_result); },
              [&unused_keys]
              {
                return libftl::error{
                    fcppt::string{FCPPT_TEXT("Unparsed attributes ")} +
                    fcppt::from_std_string(
                        fcppt::output_to_std_string(fcppt::container::output(unused_keys))) +
                    FCPPT_TEXT(".")};
              });
        });
  }

  template <typename Label>
  [[nodiscard]] fcppt::either::object<
      libftl::error,
      libftl::impl::xml::typed::result_type<fcppt::record::label_value_type<Parsers, Label>>>
  parse_one(
      attribute_map const &_attributes,
      fcppt::reference<std::set<std::string>> const _used,
      Label const &) const
  {
    using parser = fcppt::record::label_value_type<Parsers, Label>;
    constexpr bool const is_optional = parser::is_optional;
    using inner_result = libftl::impl::xml::typed::result_type<parser>;

    std::string const &name{fcppt::record::get<Label>(this->parsers_).name()};

    return fcppt::optional::maybe(
        fcppt::container::find_opt_mapped(_attributes, name),
        [&name]() -> fcppt::either::object<libftl::error, inner_result>
        {
          if constexpr (is_optional)
          {
            return fcppt::either::make_success<libftl::error>(inner_result{});
          }
          else
          {
            return fcppt::either::make_failure<inner_result>(libftl::error{
                fcppt::string{FCPPT_TEXT("Missing attribute ")} + fcppt::from_std_string(name) +
                FCPPT_TEXT(".")});
          }
        },
        [_used, &name](fcppt::reference<std::string const> const _mapped)
            -> fcppt::either::object<libftl::error, inner_result>
        {
          _used->insert(name);
          return fcppt::optional::maybe(
              fcppt::extract_from_string<inner_result>(_mapped.get()),
              [&_mapped]
              {
                return fcppt::either::make_failure<inner_result>(libftl::error{
                    fcppt::string{FCPPT_TEXT("Failed to convert ")} +
                    fcppt::from_std_string(_mapped.get()) + FCPPT_TEXT(" to type ") +
                    fcppt::from_std_string(fcppt::type_name_from_info(typeid(inner_result))) +
                    FCPPT_TEXT(".")});
              },
              [](inner_result &&_result)
              {
                if constexpr (is_optional)
                {
                  return fcppt::either::make_success<libftl::error>(
                      fcppt::optional::make(std::move(_result)));
                }
                else
                {
                  return fcppt::either::make_success<libftl::error>(std::move(_result));
                }
              });
        });
  }

  Parsers parsers_;
};
template <typename Parsers>
attribute_set(Parsers &&) -> attribute_set<Parsers>;
}

#endif
