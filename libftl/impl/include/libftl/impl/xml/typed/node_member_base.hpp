#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_BASE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_BASE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/node_member_base_fwd.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template<libftl::impl::xml::typed::required Required, typename Result>
class node_member_base
{
  FCPPT_NONMOVABLE(node_member_base);
public:
  node_member_base() = default;
  virtual ~node_member_base() = default;

  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::required::no);

  using result_type = Result;
  using arg_type = std::vector<fcppt::reference<libftl::impl::xml::node const>>;

  [[nodiscard]] virtual fcppt::either::object<libftl::error, result_type>
  parse(arg_type const &) const = 0;

  [[nodiscard]] virtual std::string const &name() const = 0;
};
}

#endif
