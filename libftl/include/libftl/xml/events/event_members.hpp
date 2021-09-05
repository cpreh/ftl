#ifndef LIBFTL_XML_EVENTS_EVENT_MEMBERS_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_EVENT_MEMBERS_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/node.hpp>
#include <libftl/xml/events/choice.hpp>
#include <libftl/xml/events/event_members_fwd.hpp>
#include <libftl/xml/labels/choice_list.hpp>
#include <libftl/xml/labels/text.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
/*              fcppt::record::element<
                  libftl::xml::labels::boarders,
                  fcppt::optional::object<libftl::xml::events::boarders>>,
              fcppt::record::element<
                  libftl::xml::labels::remove_crew,
                  fcppt::optional::object<libftl::xml::events::remove_crew>>,*/
    /*libftl::xml::node<
          fcppt::record::object<fcppt::record::element<libftl::xml::labels::load, std::string>>,
          fcppt::unit>>*/

struct event_members
{
  using type = fcppt::record::object<
      fcppt::record::element<
          libftl::xml::labels::text,
          libftl::xml::node<fcppt::record::object<>, std::string>>,
      fcppt::record::element<
          libftl::xml::labels::choice_list,
          fcppt::optional::object<std::vector<libftl::xml::events::choice>>>>;

  LIBFTL_DETAIL_SYMBOL explicit event_members(type &&);

  type value_;
};

}

#endif