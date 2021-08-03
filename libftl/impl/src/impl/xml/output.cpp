#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/output.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace
{
FCPPT_MAKE_STRONG_TYPEDEF(std::string, opening_tag);

void node_output(std::ostream &, libftl::impl::xml::document::node const &);

void attribute_output(
    std::ostream &_stream, libftl::impl::xml::document::attribute const &_attribute)
{
  _stream << _attribute.name_ << "=\"" << _attribute.value_ << '"';
}

void inner_node_output(
    std::ostream &_stream,
    libftl::impl::xml::document::inner_node const &_inner_node,
    opening_tag const &_opening_tag)
{
  fcppt::variant::match(
      _inner_node.content_,
      [&_stream](libftl::impl::xml::document::node_vector const &_value)
      {
        fcppt::algorithm::loop(
            _value,
            [&_stream](libftl::impl::xml::document::node const &_node)
            { node_output(_stream, _node); });
      },
      [&_stream](std::string const &_value) { _stream << _value; });

  _stream << "</" << _opening_tag.get() << ">";
}

void node_output(std::ostream &_stream, libftl::impl::xml::document::node const &_node)
{
  _stream << '<' << _node.opening_tag_;

  if (!_node.attributes_.empty())
  {
    _stream << ' ';
  }

  fcppt::algorithm::loop(
      _node.attributes_,
      [&_stream](libftl::impl::xml::document::attribute const &_attribute)
      {
        attribute_output(_stream, _attribute);

        _stream << ' ';
      });

  fcppt::optional::maybe(
      _node.content_,
      [&_stream] { _stream << "/>"; },
      [&_node, &_stream](libftl::impl::xml::document::inner_node const &_inner_node)
      {
        _stream << '>';

        inner_node_output(_stream, _inner_node, opening_tag{_node.opening_tag_});
      });
}

}

void libftl::impl::xml::output(std::ostream &_stream, libftl::impl::xml::document const &_document)
{
  _stream << "<root>";

  fcppt::algorithm::loop(
      _document.nodes_,
      [&_stream](libftl::impl::xml::document::node const &_node) { node_output(_stream, _node); });

  _stream << "</root>";
}
