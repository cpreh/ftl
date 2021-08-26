#ifndef LIBFTL_XML_ACHIEVEMENTS_RESULT_HPP_INCLUDED
#define LIBFTL_XML_ACHIEVEMENTS_RESULT_HPP_INCLUDED

#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/id.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/multi_difficulty.hpp>
#include <libftl/xml/labels/name.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml
{
using achievements_result = std::vector<fcppt::tuple::object<
    fcppt::record::object<fcppt::record::element<libftl::xml::labels::id, std::string>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::name,
            fcppt::tuple::object<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::desc,
            fcppt::tuple::object<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::img,
            fcppt::tuple::object<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::multi_difficulty,
            fcppt::optional::object<fcppt::tuple::object<fcppt::record::object<>, unsigned>>>>>>;
}

#endif
