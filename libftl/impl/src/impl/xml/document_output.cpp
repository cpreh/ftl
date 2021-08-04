#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/document_output.hpp>
#include <fcppt/recursive_output.hpp>
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
operator<<(std::ostream &_stream, libftl::impl::xml::document::node const &_node)
{
  return _stream << "<('" << _node.opening_tag_ << "' "
                 << fcppt::container::output(_node.attributes_) << _node.content_ << ")>";
}

inline std::ostream &
operator<<(std::ostream &_stream, libftl::impl::xml::document::inner_node const &_node)
{
  fcppt::variant::match(
      _node.content_,
      [&_stream](libftl::impl::xml::document::node_vector const &_value)
      { _stream << fcppt::container::output(_value); },
      [&_stream](std::string const &_value) { _stream << '"' << _value << '"'; });

  return _stream << "</" << _node.closing_tag_ << ">";
}

inline std::ostream &
operator<<(std::ostream &_stream, libftl::impl::xml::document::attribute const &_attribute)
{
  return _stream << _attribute.name_ << "=\"" << _attribute.value_ << '"';
}

}

std::ostream &
libftl::impl::xml::operator<<(std::ostream &_stream, libftl::impl::xml::document const &_document)
{
  return _stream << fcppt::container::output(_document.nodes_);
}
