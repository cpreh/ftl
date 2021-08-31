#ifndef LIBFTL_XML_BLUEPRINTS_CREW_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_CREW_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/blueprints/color.hpp>
#include <libftl/xml/labels/bp.hpp>
#include <libftl/xml/labels/color_list.hpp>
#include <libftl/xml/labels/cost.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/power_list.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/short.hpp>
#include <libftl/xml/labels/title.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using crew = libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::name, std::string>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::desc,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::cost,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::
            element<libftl::xml::labels::bp, libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::title,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::short_,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::rarity,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::power_list,
            std::vector<libftl::xml::node<fcppt::record::object<>, std::string>>>,
        fcppt::record::element<
            libftl::xml::labels::color_list,
            fcppt::optional::object<std::vector<libftl::xml::node<
                fcppt::record::object<>,
                std::vector<libftl::xml::blueprints::color>>>>>>>;
}

#endif
