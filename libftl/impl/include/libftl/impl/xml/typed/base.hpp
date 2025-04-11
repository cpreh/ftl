#ifndef LIBFTL_IMPL_XML_TYPED_BASE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_BASE_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>
#include <fcppt/either/object.hpp>
#include <libftl/xml/type_error.hpp>

namespace libftl::impl::xml::typed
{
template<typename Result, typename Arg>
class base
{
  FCPPT_NONMOVABLE(base);
public:
  base() = default;
  virtual ~base() = default;

  using result_type = Result;
  using arg_type = Arg;

  [[nodiscard]] virtual fcppt::either::object<libftl::xml::type_error, result_type>
  parse(arg_type const &) const = 0;
};
}

#endif
