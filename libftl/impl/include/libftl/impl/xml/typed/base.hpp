#ifndef LIBFTL_IMPL_XML_TYPED_BASE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_BASE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/either/object.hpp>

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

  [[nodiscard]] virtual fcppt::either::object<libftl::error, result_type>
  parse(arg_type const &) const = 0;
};
}

#endif
