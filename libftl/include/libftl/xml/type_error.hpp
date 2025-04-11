#ifndef LIBFTL_XML_TYPE_ERROR_HPP_INCLUDED
#define LIBFTL_XML_TYPE_ERROR_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/type_error_fwd.hpp>
#include <libftl/xml/errors/alternative.hpp>
#include <libftl/xml/errors/attribute_conversion.hpp>
#include <libftl/xml/errors/content_conversion.hpp>
#include <libftl/xml/errors/content_empty.hpp>
#include <libftl/xml/errors/content_inner.hpp>
#include <libftl/xml/errors/excess_nodes.hpp>
#include <libftl/xml/errors/expected_node.hpp>
#include <libftl/xml/errors/inner_empty.hpp>
#include <libftl/xml/errors/invalid_node.hpp>
#include <libftl/xml/errors/mismatched_tags.hpp>
#include <libftl/xml/errors/missing_attribute.hpp>
#include <libftl/xml/errors/missing_node.hpp>
#include <libftl/xml/errors/multi_attribute.hpp>
#include <libftl/xml/errors/node_content.hpp>
#include <libftl/xml/errors/not_empty.hpp>
#include <libftl/xml/errors/unused_attributes.hpp>
#include <libftl/xml/errors/unused_nodes.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace libftl::xml
{
struct type_error
{
  using variant = fcppt::variant::object<
      libftl::xml::errors::mismatched_tags,
      libftl::xml::errors::node_content,
      libftl::xml::errors::inner_empty,
      libftl::xml::errors::expected_node,
      libftl::xml::errors::unused_nodes,
      libftl::xml::errors::missing_node,
      libftl::xml::errors::content_empty,
      libftl::xml::errors::content_inner,
      libftl::xml::errors::content_conversion,
      libftl::xml::errors::excess_nodes,
      libftl::xml::errors::missing_attribute,
      libftl::xml::errors::multi_attribute,
      libftl::xml::errors::unused_attributes,
      libftl::xml::errors::attribute_conversion,
      libftl::xml::errors::not_empty,
      libftl::xml::errors::alternative,
      libftl::xml::errors::invalid_node>;

  variant value_;

  [[nodiscard]]
  LIBFTL_DETAIL_SYMBOL bool operator==(libftl::xml::type_error const &) const;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::xml::type_error const &);
}

#endif
