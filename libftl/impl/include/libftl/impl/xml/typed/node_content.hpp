#ifndef LIBFTL_IMPL_XML_TYPED_NODE_CONTENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_CONTENT_HPP_INCLUDED

#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/parses.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/node_content.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Attributes, typename Content>
requires libftl::impl::xml::typed::
    parses<Content, fcppt::optional::object<libftl::impl::xml::inner_node>>
class node_content
{
public:
  using result_type = libftl::xml::node<
      libftl::impl::xml::typed::result_type<Attributes>,
      libftl::impl::xml::typed::result_type<Content>>;

  using arg_type = libftl::impl::xml::node;

  node_content(Attributes &&_attributes, Content &&_content)
      : attributes_{std::move(_attributes)}, content_{std::move(_content)}
  {
  }

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    return fcppt::either::map_failure(
        fcppt::either::bind(
            fcppt::deref(this->attributes_).parse(_node.attributes_),
            [this, &_node](libftl::impl::xml::typed::result_type<Attributes> &&_attributes_result)
            {
              return fcppt::either::map(
                  fcppt::deref(this->content_).parse(_node.content_),
                  [&_attributes_result](
                      libftl::impl::xml::typed::result_type<Content> &&_content_result)
                  {
                    return result_type{std::move(_attributes_result), std::move(_content_result)};
                  });
            }),
        [&_node](libftl::xml::type_error &&_error)
        {
          return libftl::xml::type_error{libftl::xml::type_error::variant{
              libftl::xml::errors::node_content{_node.location_, std::move(_error)}}};
        });
  }

private:
  Attributes attributes_;
  Content content_;
};

template <typename Attributes, typename Content>
node_content(Attributes &&, Content &&) -> node_content<Attributes, Content>;
}

#endif
