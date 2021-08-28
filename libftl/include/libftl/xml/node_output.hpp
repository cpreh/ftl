#ifndef LIBFTL_XML_NODE_OUTPUT_HPP_INCLUDED
#define LIBFTL_XML_NODE_OUTPUT_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <fcppt/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml
{
template <typename Ch, typename Traits, typename Attributes, typename Content>
std::basic_ostream<Ch, Traits> &operator<<(
    std::basic_ostream<Ch, Traits> &_stream, libftl::xml::node<Attributes, Content> const &_node)
{
  return _stream << _stream.widen('(') << fcppt::output(_node.attributes_) << _stream.widen(',')
                 << fcppt::output(_node.content_) << _stream.widen(')');
}
}

#endif
