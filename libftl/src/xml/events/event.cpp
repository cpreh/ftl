#include <libftl/xml/events/event.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::xml::events::event::event(type &&_value) : value_{std::move(_value)} {}
