#ifndef LIBFTL_XML_BLUEPRINTS_AUG_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_AUG_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/bp.hpp>
#include <libftl/xml/labels/cost.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/stackable.hpp>
#include <libftl/xml/labels/title.hpp>
#include <libftl/xml/labels/value.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using aug = libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::name, std::string>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::title,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::desc,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::cost,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::
            element<libftl::xml::labels::bp, libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::rarity,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::stackable,
            libftl::xml::node<fcppt::record::object<>, bool>>,
        fcppt::record::element<
            libftl::xml::labels::value,
            libftl::xml::node<fcppt::record::object<>, double>>>>;
}

#endif
