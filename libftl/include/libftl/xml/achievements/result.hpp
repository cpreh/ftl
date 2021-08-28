#ifndef LIBFTL_XML_ACHIEVEMENTS_RESULT_HPP_INCLUDED
#define LIBFTL_XML_ACHIEVEMENTS_RESULT_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/id.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/multi_difficulty.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/ship.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::achievements
{
using result = std::vector<libftl::xml::node<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::id, std::string>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::name,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::desc,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::img,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::ship,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, std::string>>>,
        fcppt::record::element<
            libftl::xml::labels::multi_difficulty,
            fcppt::optional::object<libftl::xml::node<fcppt::record::object<>, unsigned>>>>>>;
}

#endif
