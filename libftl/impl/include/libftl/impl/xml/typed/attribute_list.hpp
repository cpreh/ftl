#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_LIST_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_LIST_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_map.hpp>
#include <libftl/impl/xml/typed/attribute_used.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/loop_break_record.hpp>
#include <fcppt/algorithm/map_record.hpp>
#include <fcppt/container/key_set.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/container/set_difference.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/construct.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/init.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/map_elements.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{

template<typename Parsers>
class attribute_list
{
public:
  static_assert(fcppt::record::is_object<Parsers>::value);

  using result_type = fcppt::record::map_elements<
      Parsers,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<libftl::impl::xml::typed::result_type>,
          fcppt::mpl::lambda<fcppt::record::element_to_type>>>;

  explicit attribute_list(Parsers &&_parsers) : parsers_{std::move(_parsers)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<libftl::impl::xml::attribute> const &_attributes) const
  {
    return fcppt::either::bind(
        attribute_list::make_attribute_map(_attributes),
        [this](libftl::impl::xml::typed::attribute_map const &_attribute_map)
        { return this->run_parsers(_attribute_map); });
  }
private:
  [[nodiscard]] static fcppt::either::object<libftl::error, libftl::impl::xml::typed::attribute_map>
  make_attribute_map(std::vector<libftl::impl::xml::attribute> const &_attributes)
  {
    return fcppt::algorithm::fold(
        _attributes,
        fcppt::either::make_success<libftl::error>(libftl::impl::xml::typed::attribute_map{}),
        [](libftl::impl::xml::attribute const &_attrib,
           fcppt::either::object<libftl::error, libftl::impl::xml::typed::attribute_map> &&_map)
        {
          return fcppt::either::bind(
              std::move(_map),
              [&_attrib](libftl::impl::xml::typed::attribute_map &&_inner_map)
              {
                if (_inner_map.contains(_attrib.name_))
                {
                  return fcppt::either::make_failure<libftl::impl::xml::typed::attribute_map>(
                      libftl::error{
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
  run_parsers(libftl::impl::xml::typed::attribute_map const &_attributes) const
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
                [&_attributes, &used, this]<typename Label, typename Type>(
                    fcppt::record::element<Label, Type> const &)
                {
                  using inner_result_type = fcppt::either::object<
                      libftl::error,
                      libftl::impl::xml::typed::result_type<
                          fcppt::record::label_value_type<Parsers, Label>>>;

                  fcppt::tuple::object<libftl::impl::xml::typed::attribute_used, inner_result_type>
                      inner_result{fcppt::deref(fcppt::record::get<Label>(this->parsers_)).parse(_attributes)};
                  fcppt::optional::maybe_void(
                      std::move(fcppt::tuple::get<0>(inner_result).get()),
                      [&used](std::string &&_used) { used.insert(std::move(_used)); });

                  return std::move(fcppt::tuple::get<1>(inner_result));
                })),
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

  Parsers parsers_;
};
template<typename Parsers> attribute_list(Parsers &&) -> attribute_list<Parsers>;
}

#endif
