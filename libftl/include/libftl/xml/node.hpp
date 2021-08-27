#ifndef LIBFTL_XML_NODE_HPP_INCLUDED
#define LIBFTL_XML_NODE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml
{
template<typename Attributes, typename Content>
struct node
{
  node(Attributes &&_attributes, Content &&_content)
      : attributes_{std::move(_attributes)}, content_{std::move(_content)}
  {
  }

  using attributes_type = Attributes;

  using content_type = Content;

  Attributes attributes_;

  Content content_;
};

template<typename Attributes, typename Content>
node(Attributes &&, Content &&) -> node<Attributes, Content>;

template <typename Attributes, typename Content>
[[nodiscard]] bool operator==(
    libftl::xml::node<Attributes, Content> const &_left,
    libftl::xml::node<Attributes, Content> const &_right)
{
  return _left.attributes_ == _right.attributes_ && _left.content_ == _right.content_;
}
}

#endif
