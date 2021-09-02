#ifndef LIBFTL_XML_BLUEPRINTS_SOUND_LIST_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_SOUND_LIST_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using sound_list = libftl::xml::node<
    fcppt::record::object<>,
    std::vector<libftl::xml::node<fcppt::record::object<>, std::string>>>;
}

#endif
