#ifndef LIBFTL_IMPL_XML_TYPED_NODE_SET_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_SET_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/basic_set.hpp>
#include <libftl/impl/xml/typed/is_node_member.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref_recursive.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/element_vector.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parsers>
class node_set
{
public:
  static_assert(fcppt::record::is_object<Parsers>::value);

  static_assert(fcppt::mpl::list::all_of<
                fcppt::mpl::list::map<
                    fcppt::record::element_vector<Parsers>,
                    fcppt::mpl::lambda<fcppt::record::element_to_type>>,
                fcppt::mpl::bind<
                    fcppt::mpl::lambda<libftl::impl::xml::typed::is_node_member>,
                    fcppt::mpl::bind<
                        fcppt::mpl::lambda<std::remove_cvref_t>,
                        fcppt::mpl::lambda<fcppt::deref_type>>>>::value);

  using impl =
      libftl::impl::xml::typed::basic_set<Parsers, fcppt::recursive<libftl::impl::xml::node>>;
  using result_type = libftl::impl::xml::typed::result_type<impl>;

  explicit node_set(Parsers &&_parsers) : impl_{std::move(_parsers)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node_vector const &_nodes) const
  {
    return this->impl_.parse(_nodes);
  }

private:
  impl impl_;
};
template <typename Parsers>
node_set(Parsers &&) -> node_set<Parsers>;
}

#endif
