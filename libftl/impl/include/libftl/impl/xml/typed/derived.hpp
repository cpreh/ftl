#ifndef LIBFTL_IMPL_XML_TYPED_DERIVED_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_DERIVED_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/typed/arg_type.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Impl>
class derived : public libftl::impl::xml::typed::base<
                    libftl::impl::xml::typed::result_type<Impl>,
                    libftl::impl::xml::typed::arg_type<Impl>>
{
  FCPPT_NONMOVABLE(derived);

public:
  explicit derived(Impl &&_impl) : impl_{std::move(_impl)} {}
  ~derived() override = default;

  using result_type = libftl::impl::xml::typed::result_type<Impl>;

  using arg_type = libftl::impl::xml::typed::arg_type<Impl>;

  [[nodiscard]] virtual fcppt::either::object<libftl::error, result_type>
  parse(arg_type const &_arg) const override
  {
    return fcppt::deref(this->impl_).parse(_arg);
  }

private:
  Impl impl_;
};

}

#endif
