#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_SET_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_SET_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/typed/basic_set.hpp>
#include <libftl/impl/xml/typed/is_attribute.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/record/element_vector.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/config/external_begin.hpp>
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

  using impl = libftl::impl::xml::typed::basic_set<Parsers,libftl::impl::xml::attribute>;
  using result_type = libftl::impl::xml::typed::result_type<impl>;

  explicit attribute_set(Parsers &&_parsers) : impl_{std::move(_parsers)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<libftl::impl::xml::attribute> const &_attributes) const
  {
    return this->impl_.parse(_attributes);
  }

private:
  impl impl_;
};
template <typename Parsers>
attribute_set(Parsers &&) -> attribute_set<Parsers>;
}

#endif
