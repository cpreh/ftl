#ifndef LIBFTL_XML_ANIMATIONS_ANIM_SHEET_HPP_INCLUDED
#define LIBFTL_XML_ANIMATIONS_ANIM_SHEET_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/fh.hpp>
#include <libftl/xml/labels/fw.hpp>
#include <libftl/xml/labels/h.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/w.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::animations
{
using anim_sheet = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::name, std::string>,
        fcppt::record::element<libftl::xml::labels::w, unsigned>,
        fcppt::record::element<libftl::xml::labels::h, unsigned>,
        fcppt::record::element<libftl::xml::labels::fw, unsigned>,
        fcppt::record::element<libftl::xml::labels::fh, unsigned>>,
    std::string>;

}

#endif
