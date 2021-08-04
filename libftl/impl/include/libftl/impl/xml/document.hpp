#ifndef LIBFTL_IMPL_XML_DOCUMENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_DOCUMENT_HPP_INCLUDED

#include <libftl/impl/xml/document_fwd.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct document
{
  struct version
  {
    std::string version_;

    std::string encoding_;
  };

  fcppt::optional::object<version> version_;

  libftl::impl::xml::node_vector nodes_;
};

}

#endif
