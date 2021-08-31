#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/node_member_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/node.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <libftl::impl::xml::typed::required Required, typename Attributes, typename Content>
requires libftl::impl::xml::typed::parses<Content,fcppt::optional::object<libftl::impl::xml::inner_node>>
class node_member
{
public:
  using result_type = libftl::xml::node<
      libftl::impl::xml::typed::result_type<Attributes>,
      libftl::impl::xml::typed::result_type<Content>>;

  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::required::no);

  node_member(std::string &&_name, Attributes &&_attributes, Content &&_content)
      : name_{std::move(_name)}, attributes_{std::move(_attributes)}, content_{std::move(_content)}
  {
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    return fcppt::either::bind(
        fcppt::deref(this->attributes_).parse(_node.attributes_),
        [this, &_node](libftl::impl::xml::typed::result_type<Attributes> &&_attributes_result)
        {
          return fcppt::either::map(
              fcppt::deref(this->content_).parse(_node.content_),
              [&_attributes_result](
                  libftl::impl::xml::typed::result_type<Content> &&_content_result) {
                return result_type{std::move(_attributes_result), std::move(_content_result)};
              });
        });
  }
private:
  std::string name_;
  Attributes attributes_;
  Content content_;
};

}

#endif
