#ifndef LIBFTL_XML_EVENTS_EVENT_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_EVENT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/events/choice.hpp>
#include <libftl/xml/events/event_fwd.hpp>
#include <libftl/xml/labels/choice_list.hpp>
#include <libftl/xml/labels/load.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/text.hpp>
#include <libftl/xml/labels/unique.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
struct event
{
  using type = fcppt::variant::object<
      libftl::xml::node<
          fcppt::record::object<
              fcppt::record::element<libftl::xml::labels::name, std::string>,
              fcppt::record::element<libftl::xml::labels::unique, fcppt::optional::object<bool>>>,
          fcppt::record::object<
              fcppt::record::element<
                  libftl::xml::labels::text,
                  libftl::xml::node<fcppt::record::object<>, std::string>>,
              fcppt::record::element<
                  libftl::xml::labels::choice_list,
                  fcppt::optional::object<std::vector<libftl::xml::events::choice>>>>>,
      libftl::xml::node<
          fcppt::record::object<fcppt::record::element<libftl::xml::labels::load, std::string>>,
          fcppt::unit>>;

  LIBFTL_DETAIL_SYMBOL explicit event(type &&);

  type value_;
};

}

#endif
