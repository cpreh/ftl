#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_LIST_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_LIST_HPP_INCLUDED

#include <libftl/impl/xml/typed/result_type.hpp>

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

  explicit(Parsers &&_parsers) : parsers_{std::move(_parsers)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<libftl::impl::xml::attribute> const &_attributes) const
  {
    fcppt::either::object<libftl::error, map_type> attributes{fcppt::algorithm::fold_break(
        _attributes,
        map_type{},
        [](fcppt::either::object<libftl::error, map_type> &&_map,
           libftl::impl::xml::attribute const &_attrib)
        {
          return fcppt::either::bind(
              std::move(_map),
              [](map_type &&_inner_map)
              {
                if (_inner_map.contains(_attrib.name_))
                {
                  return fcppt::either::make_failure<map_type>(
                      fcppt::string{FCPPT_TEXT("Attribute ")} + fcppt::from_std_string(_attrib.name_) +
                      FCPPT_TEXT(" specified multiple times."));
                }
                _inner_map.insert(std::make_pair(_attrib.name_, _attrib.value_));
                return fcppt::either::make_success<libftl::error>(_inner_map);
              });
        })};

    using init_type = fcppt::record::map_elements<fcppt::mpl::bind<
        fcppt::mpl::lambda<fcppt::either::object>,
        fcppt::mpl::constant<libftl::error>,
        fcppt::mpl::bind<fcppt::mpl::lambda<fcppt::record::element_to_type>>>>;

    result_type result{fcppt::either::sequence(fcppt::record::init<init_type>(
        [&attributes]<typename Label, typename Type>(
            fcppt::record::element<Label, Type> const &_element)
        { return fcppt::record::get<Label>(this->parsers_).parse(fcppt::make_ref(attributes)); }))};

    // TODO: Excess attributes
    return result;
  }
private:
  Parsers parsers_;
};
}

#endif
