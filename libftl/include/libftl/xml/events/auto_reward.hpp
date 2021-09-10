#ifndef LIBFTL_XML_EVENTS_AUTO_REWARD_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_AUTO_REWARD_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/level.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::events
{
// TODO(philipp): Use enums for both strings.
using auto_reward = libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::level, std::string>>,
    std::string>;
}

#endif
