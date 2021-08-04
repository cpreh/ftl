#ifndef LIBFTL_IMPL_XML_NODE_VECTOR_HPP_INCLUDED
#define LIBFTL_IMPL_XML_NODE_VECTOR_HPP_INCLUDED

#include <libftl/impl/xml/node_fwd.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
using node_vector = std::vector<fcppt::recursive<libftl::impl::xml::node>>;
}

#endif
