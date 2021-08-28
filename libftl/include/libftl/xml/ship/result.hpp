#ifndef LIBFTL_XML_SHIP_RESULT_HPP_INCLUDED
#define LIBFTL_XML_SHIP_RESULT_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/explosion.hpp>
#include <libftl/xml/labels/gib.hpp>
#include <libftl/xml/labels/glow_offset.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/mirror.hpp>
#include <libftl/xml/labels/offsets.hpp>
#include <libftl/xml/labels/rotate.hpp>
#include <libftl/xml/labels/slide.hpp>
#include <libftl/xml/labels/weapon_mounts.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <libftl/xml/ship/explosion.hpp>
#include <libftl/xml/ship/img.hpp>
#include <libftl/xml/ship/offsets.hpp>
#include <libftl/xml/ship/slide.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::ship
{
using result = fcppt::record::object<
    fcppt::record::element<libftl::xml::labels::img, libftl::xml::ship::img>,
    fcppt::record::element<
        libftl::xml::labels::glow_offset,
        fcppt::optional::object<libftl::xml::node<
            fcppt::record::object<
                fcppt::record::element<libftl::xml::labels::x, int>,
                fcppt::record::element<libftl::xml::labels::y, int>>,
            fcppt::unit>>>,
    fcppt::record::
        element<libftl::xml::labels::offsets, fcppt::optional::object<libftl::xml::ship::offsets>>,
    fcppt::record::element<
        libftl::xml::labels::weapon_mounts,
        libftl::xml::node<
            fcppt::record::object<>,
            std::vector<libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::x, int>,
                    fcppt::record::element<libftl::xml::labels::y, int>,
                    fcppt::record::element<libftl::xml::labels::rotate, bool>,
                    fcppt::record::element<libftl::xml::labels::mirror, bool>,
                    fcppt::record::element<libftl::xml::labels::gib, unsigned>,
                    fcppt::record::element<libftl::xml::labels::slide, libftl::xml::ship::slide>>,
                fcppt::unit>>>>,
    fcppt::record::element<libftl::xml::labels::explosion, libftl::xml::ship::explosion>>;
}

#endif
