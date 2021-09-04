#ifndef LIBFTL_XML_EVENTS_REMOVE_CREW_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_REMOVE_CREW_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/clone.hpp>
#include <libftl/xml/labels/text.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
using remove_crew
=
libftl::xml::node<
  fcppt::record::object<>,
  fcppt::record::object<
    fcppt::record::element<
      libftl::xml::labels::clone,
      bool
    >,
    fcppt::record::element<
      libftl::xml::labels::text,
      std::string
    >
  >
>;
}
#endif
