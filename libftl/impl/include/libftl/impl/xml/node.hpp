#ifndef LIBFTL_IMPL_XML_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_NODE_HPP_INCLUDED

#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node_fwd.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/parse/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct node
{
  node(
      fcppt::optional::object<fcppt::parse::location> const _location,
      std::string &&_opening_tag,
      std::vector<libftl::impl::xml::attribute> &&_attributes,
      fcppt::optional::object<libftl::impl::xml::inner_node> &&_content)
      : location_{_location},
        opening_tag_{std::move(_opening_tag)},
        attributes_{std::move(_attributes)},
        content_{std::move(_content)}
  {
  }

  fcppt::optional::object<fcppt::parse::location> location_;

  std::string opening_tag_;

  std::vector<libftl::impl::xml::attribute> attributes_;

  fcppt::optional::object<libftl::impl::xml::inner_node> content_;

  [[nodiscard]] std::string const &name() const { return this->opening_tag_; }
};

}

#endif
