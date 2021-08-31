#ifndef LIBFTL_XML_BLUEPRINTS_SYSTEM_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_SYSTEM_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/cost.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/locked.hpp>
#include <libftl/xml/labels/max_power.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/start_power.hpp>
#include <libftl/xml/labels/title.hpp>
#include <libftl/xml/labels/type.hpp>
#include <libftl/xml/labels/upgrade_cost.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using system = libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::name, std::string>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::type,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::title,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::desc,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::start_power,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::max_power,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::rarity,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::upgrade_cost,
            libftl::xml::node<
                fcppt::record::object<>,
                std::vector<libftl::xml::node<fcppt::record::object<>, unsigned>>>>,
        fcppt::record::element<
            libftl::xml::labels::cost,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::locked,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, unsigned>>>>>;
}

#endif
