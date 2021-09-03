#ifndef LIBFTL_XML_SECTORS_SECTOR_DESCRIPTION_HPP_INCLUDED
#define LIBFTL_XML_SECTORS_SECTOR_DESCRIPTION_HPP_INCLUDED

#include <libftl/xml/node.hpp>
#include <libftl/xml/labels/event_list.hpp>
#include <libftl/xml/labels/max.hpp>
#include <libftl/xml/labels/min.hpp>
#include <libftl/xml/labels/min_sector.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/name_list.hpp>
#include <libftl/xml/labels/rarity.hpp>
#include <libftl/xml/labels/rarity_list.hpp>
#include <libftl/xml/labels/start_event.hpp>
#include <libftl/xml/labels/track_list.hpp>
#include <libftl/xml/labels/unique.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::sectors
{
using sector_description = libftl::xml::node<
    fcppt::record::object<
        fcppt::record::element<libftl::xml::labels::name, std::string>,
        fcppt::record::element<libftl::xml::labels::min_sector, unsigned>,
        fcppt::record::element<libftl::xml::labels::unique, bool>>,
    fcppt::record::object<
        fcppt::record::element<
            libftl::xml::labels::name_list,
            libftl::xml::node<
                fcppt::record::object<>,
                std::vector<libftl::xml::node<fcppt::record::object<>, std::string>>>>,
        fcppt::record::element<
            libftl::xml::labels::track_list,
            libftl::xml::node<
                fcppt::record::object<>,
                std::vector<libftl::xml::node<fcppt::record::object<>, std::string>>>>,
        fcppt::record::element<
            libftl::xml::labels::rarity_list,
            libftl::xml::node<
                fcppt::record::object<>,
                std::vector<libftl::xml::node<
                    fcppt::record::object<
                        fcppt::record::element<libftl::xml::labels::name, std::string>,
                        fcppt::record::element<libftl::xml::labels::rarity, unsigned>>,
                    fcppt::unit>>>>,
        fcppt::record::element<
            libftl::xml::labels::start_event,
            libftl::xml::node<fcppt::record::object<>, std::string>>,
        fcppt::record::element<
            libftl::xml::labels::event_list,
            fcppt::optional::object<std::vector<libftl::xml::node<
                fcppt::record::object<
                    fcppt::record::element<libftl::xml::labels::name, std::string>,
                    fcppt::record::element<libftl::xml::labels::min, unsigned>,
                    fcppt::record::element<libftl::xml::labels::max, unsigned>>,
                fcppt::unit>>>>>>;
}

#endif
