#ifndef LIBFTL_XML_ANIMATIONS_ANIM_HPP_INCLUDED
#define LIBFTL_XML_ANIMATIONS_ANIM_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/length.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/sheet.hpp>
#include <libftl/xml/labels/time.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::animations
{
using anim = libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::name, std::string>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::sheet,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::desc,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::length, unsigned>,
                    fcppt::record::element<libftl::xml::labels::x, unsigned>,
                    fcppt::record::element<libftl::xml::labels::y, unsigned>>,
                fcppt::unit>>,
        fcppt::record::element<
            libftl::xml::labels::time,
            libftl::xml::node<fcppt::record::object<>, double>>>>;
}

#endif
