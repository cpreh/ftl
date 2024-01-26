#ifndef LIBFTL_XML_EVENTS_EVENT_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_EVENT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/events/event_content.hpp>
#include <libftl/xml/events/event_fwd.hpp> // IWYU pragma: keep
#include <libftl/xml/labels/load.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
struct event
{
  using type = fcppt::variant::object<
      libftl::xml::node<fcppt::record::object<>, libftl::xml::events::event_content>,
      libftl::xml::node<
          fcppt::record::object<fcppt::record::element<libftl::xml::labels::load, std::string>>,
          fcppt::unit>>;

  LIBFTL_DETAIL_SYMBOL explicit event(type &&);

  type value_;
};
}

#endif
