#ifndef LIBFTL_XML_EVENTS_EVENT_OUTPUT_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_EVENT_OUTPUT_HPP_INCLUDED

#include <libftl/xml/node_output.hpp>
#include <libftl/xml/events/event.hpp>
#include <fcppt/output_range.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/record/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
template <typename Ch, typename Traits>
inline std::basic_ostream<Ch, Traits> &operator<<(
    std::basic_ostream<Ch, Traits> &_stream, libftl::xml::events::event const &_event)
{
  return _stream << _event.value_;
}
}

#endif
