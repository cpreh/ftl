#ifndef LIBFTL_XML_BLUEPRINTS_SYSTEM_ELEMENT_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_SYSTEM_ELEMENT_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/blueprints/direction.hpp>
#include <libftl/xml/labels/direction.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/max.hpp>
#include <libftl/xml/labels/number.hpp>
#include <libftl/xml/labels/power.hpp>
#include <libftl/xml/labels/room.hpp>
#include <libftl/xml/labels/slot.hpp>
#include <libftl/xml/labels/start.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using system_element = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::power, unsigned>,
        fcppt::record::element<libftl::xml::labels::room, unsigned>,
        fcppt::record::element<libftl::xml::labels::start, bool>,
        fcppt::record::element<libftl::xml::labels::img, fcppt::optional::object<std::string>>,
        fcppt::record::element<libftl::xml::labels::max, fcppt::optional::object<unsigned>>>,
    fcppt::record::object<fcppt::record::element<
        libftl::xml::labels::slot,
        fcppt::optional::object<libftl::xml::node<
            fcppt::record::object<>,
            fcppt::record::object<
                fcppt::record::element<
                    libftl::xml::labels::direction,
                    fcppt::optional::object<libftl::xml::node<
                        fcppt::record::object<>,
                        libftl::xml::blueprints::direction>>>,
                fcppt::record::element<
                    libftl::xml::labels::number,
                    libftl::xml::node<fcppt::record::object<>, unsigned>>>>>>>>;
}

#endif
