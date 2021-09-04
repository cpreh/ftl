#ifndef LIBFTL_XML_EVENTS_EVENT_MEMBERS_OUTPUT_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_EVENT_MEMBERS_OUTPUT_HPP_INCLUDED

#include <libftl/xml/events/event_members.hpp>
#include <fcppt/record/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
template <typename Ch, typename Traits>
inline std::basic_ostream<Ch, Traits> &operator<<(
    std::basic_ostream<Ch, Traits> &_stream, libftl::xml::events::event_members const &_members)
{
  return _stream << _members.value_;
}
}

#endif
