#ifndef LIBFTL_IMPL_XML_TYPED_NAMED_NODE_BASE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NAMED_NODE_BASE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/named_node_base_fwd.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template<typename Result>
class named_node_base
{
  FCPPT_NONMOVABLE(named_node_base);
public:
  named_node_base() = default;
  virtual ~named_node_base() = default;

  using result_type = Result;
  using arg_type = libftl::impl::xml::node;

  [[nodiscard]] virtual fcppt::either::object<libftl::error, result_type>
  parse(arg_type const &) const = 0;

  [[nodiscard]] virtual std::string const &name() const = 0;
};
}

#endif
