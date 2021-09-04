#include <libftl/xml/events/event_members.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::xml::events::event_members::event_members(type &&_value) : value_{std::move(_value)} {}
