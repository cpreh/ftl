#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <fcppt/recursive_output.hpp> // IWYU pragma: keep
#include <fcppt/container/output.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
inline std::ostream &
operator<<(std::ostream &_stream, libftl::impl::xml::node const &_node) // NOLINT(misc-use-internal-linkage)
{
  return _stream << "<('" << _node.opening_tag_ << "' "
                 << fcppt::container::output(_node.attributes_) << _node.content_ << ")>";
}

inline std::ostream &
operator<<(std::ostream &_stream, libftl::impl::xml::inner_node const &_node) // NOLINT(misc-use-internal-linkage)
{
  fcppt::variant::match(
      _node.content_,
      [&_stream](libftl::impl::xml::node_vector const &_value)
      { _stream << fcppt::container::output(_value); },
      [&_stream](std::string const &_value) { _stream << '"' << _value << '"'; });

  return _stream << "</" << _node.closing_tag_ << ">";
}

inline std::ostream &
operator<<(std::ostream &_stream, libftl::impl::xml::attribute const &_attribute) // NOLINT(misc-use-internal-linkage)
{
  return _stream << _attribute.name_ << "=\"" << _attribute.value_ << '"';
}
}

std::ostream &
libftl::impl::xml::operator<<(std::ostream &_stream, libftl::impl::xml::document const &_document)
{
  return _stream << fcppt::container::output(_document.nodes_);
}
