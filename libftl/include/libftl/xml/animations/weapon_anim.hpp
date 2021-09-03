#ifndef LIBFTL_XML_ANIMATIONS_WEAPON_ANIM_HPP_INCLUDED
#define LIBFTL_XML_ANIMATIONS_WEAPON_ANIM_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/charged_frame.hpp>
#include <libftl/xml/labels/charge_image.hpp>
#include <libftl/xml/labels/fire_frame.hpp>
#include <libftl/xml/labels/fire_point.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/length.hpp>
#include <libftl/xml/labels/mount_point.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/sheet.hpp>
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
using weapon_anim = libftl::xml::node<
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
            libftl::xml::labels::charged_frame,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::fire_frame,
            libftl::xml::node<fcppt::record::object<>, unsigned>>,
        fcppt::record::element<
            libftl::xml::labels::fire_point,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::x, unsigned>,
                    fcppt::record::element<libftl::xml::labels::y, unsigned>>,
                fcppt::unit>>,
        fcppt::record::element<
            libftl::xml::labels::mount_point,
            libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::x, unsigned>,
                    fcppt::record::element<libftl::xml::labels::y, unsigned>>,
                fcppt::unit>>,
        fcppt::record::element<
            libftl::xml::labels::charge_image,
            libftl::xml::node<fcppt::record::object<>, std::string>>>>;
}

#endif
