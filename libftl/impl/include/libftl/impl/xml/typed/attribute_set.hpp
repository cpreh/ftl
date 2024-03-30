#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_SET_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_SET_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/typed/is_attribute.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/loop_break_record.hpp> // IWYU pragma: keep
#include <fcppt/algorithm/map_record.hpp> // IWYU pragma: keep
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/key_set.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/container/set_difference.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/construct.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/object_concept.hpp> // IWYU pragma: keep
#include <fcppt/either/sequence.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/element_vector.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/init.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/map_elements.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
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

  template <typename Parser>
  static constexpr bool make_is_optional =
      std::remove_cvref_t<fcppt::deref_type<Parser>>::is_optional;

  template <typename Parser>
  using make_result_type = std::conditional_t<
      make_is_optional<Parser>,
      fcppt::optional::object<libftl::impl::xml::typed::result_type<Parser>>,
      libftl::impl::xml::typed::result_type<Parser>>;

  using result_type = fcppt::record::map_elements<
      Parsers,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<make_result_type>,
          fcppt::mpl::lambda<fcppt::record::element_to_type>>>;

  using map = std::unordered_map<std::string, fcppt::reference<libftl::impl::xml::attribute const>>;

  explicit attribute_set(Parsers &&_parsers) : parsers_{std::move(_parsers)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<libftl::impl::xml::attribute> const &_args) const
  {
    return fcppt::either::bind(
        attribute_set::make_map(_args), [this](map const &_map) { return this->run_parsers(_map); });
  }
private:
  [[nodiscard]] static fcppt::either::object<libftl::error, map>
  make_map(std::vector<libftl::impl::xml::attribute> const &_args)
  {
    return fcppt::algorithm::fold(
        _args,
        fcppt::either::make_success<libftl::error>(map{}),
        [](libftl::impl::xml::attribute const &_arg, fcppt::either::object<libftl::error, map> &&_map)
        {
          return fcppt::either::bind(
              std::move(_map),
              [&_arg](map &&_inner_map)
              {
                std::string const &name{fcppt::deref(_arg).name()};

                if (_inner_map.contains(name))
                {
                  return fcppt::either::make_failure<map>(libftl::error{
                      fcppt::from_std_string(name) +
                      FCPPT_TEXT(" specified multiple times.")});
                }
                _inner_map.insert(std::make_pair(name, fcppt::make_cref(_arg)));
                return fcppt::either::make_success<libftl::error>(std::move(_inner_map));
              });
        });
  }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  run_parsers(map const &_args) const
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
                [&_args, &used, this]<typename Label, fcppt::either::object_concept Type>(
                    fcppt::record::element<Label, Type> const &)
                { return this->parse_one(_args, fcppt::make_ref(used), Label{}); })),
        [&used, &_args](result_type &&_result)
        {
          std::set<std::string> const unused_keys{fcppt::container::set_difference(
              fcppt::container::key_set<std::set<std::string>>(_args), used)};
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
      make_result_type<fcppt::record::label_value_type<Parsers, Label>>>
  parse_one(
      map const &_args,
      fcppt::reference<std::set<std::string>> const _used,
      Label const &) const
  {
    using parser = fcppt::record::label_value_type<Parsers, Label>;
    using parser_result = make_result_type<parser>;
    constexpr bool const is_optional = make_is_optional<parser>;

    std::string const &name{fcppt::record::get<Label>(this->parsers_).name()};

    return fcppt::optional::maybe(
        fcppt::container::find_opt_mapped(_args, name),
        [&name]() -> fcppt::either::object<libftl::error, parser_result>
        {
          FCPPT_USE(name);
          if constexpr (is_optional)
          {
            return fcppt::either::make_success<libftl::error>(parser_result{});
          }
          else
          {
            return fcppt::either::make_failure<parser_result>(libftl::error{
                fcppt::string{FCPPT_TEXT("Missing attribute ")} + fcppt::from_std_string(name) +
                FCPPT_TEXT(".")});
          }
        },
        [_used, &name, this](
            fcppt::reference<fcppt::reference<libftl::impl::xml::attribute const> const> const
                _mapped) -> fcppt::either::object<libftl::error, parser_result>
        {
          _used->insert(name);
          return fcppt::either::bind(
              fcppt::deref(fcppt::record::get<Label>(this->parsers_)).parse(_mapped.get().get()),
              [](libftl::impl::xml::typed::result_type<parser> &&_result)
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
