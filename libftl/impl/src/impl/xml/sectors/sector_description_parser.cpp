#include <libftl/impl/xml/sectors/sector_description_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_named_node_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/named_node.hpp>
#include <libftl/impl/xml/typed/named_node_base.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/node_member_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
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
#include <libftl/xml/sectors/sector_description.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::named_node_base<libftl::xml::sectors::sector_description>>
libftl::impl::xml::sectors::sector_description_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_named_node_derived(typed::named_node{
      "sectorDescription",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"},
              labels::min_sector{} = typed::attribute<unsigned, required::yes>{"minSector"},
              labels::unique{} = typed::attribute<bool, required::yes>{"unique"})},
          typed::inner_node{typed::node_set{fcppt::record::make(
              labels::name_list{} = typed::make_node_member<required::yes>(
                  "nameList",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{typed::node_list{typed::node{
                      "name",
                      typed::node_content{
                          typed::attribute_set{fcppt::record::make()},
                          typed::content<std::string>{}}}}}),
              labels::track_list{} = typed::make_node_member<required::yes>(
                  "trackList",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{typed::node_list{typed::node{
                      "track",
                      typed::node_content{
                          typed::attribute_set{fcppt::record::make()},
                          typed::content<std::string>{}}}}}),
              labels::rarity_list{} = typed::make_node_member<required::yes>(
                  "rarityList",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{typed::node_list{typed::node{
                      "blueprint",
                      typed::node_content{
                          typed::attribute_set{fcppt::record::make(
                              labels::name{} = typed::attribute<std::string, required::yes>{"name"},
                              labels::rarity{} =
                                  typed::attribute<unsigned, required::yes>{"rarity"})},
                          typed::empty{}}}}}),
              labels::start_event{} = typed::make_node_member<required::yes>(
                  "startEvent",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::event_list{} = typed::node_member_list{
                  "event",
                  typed::node_content{
                      typed::attribute_set{fcppt::record::make(
                          labels::name{} = typed::attribute<std::string, required::yes>{"name"},
                          labels::min{} = typed::attribute<unsigned, required::yes>{"min"},
                          labels::max{} = typed::attribute<unsigned, required::yes>{"max"})},
                      typed::empty{}}})}}}});
}
