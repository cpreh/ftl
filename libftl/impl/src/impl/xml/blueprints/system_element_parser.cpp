#include <libftl/impl/xml/blueprints/system_element_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/make_node_member_derived.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/optional_inner_node.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/blueprints/direction.hpp>
#include <libftl/xml/blueprints/direction_input.hpp>
#include <libftl/xml/blueprints/system_element.hpp>
#include <libftl/xml/labels/direction.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/max.hpp>
#include <libftl/xml/labels/number.hpp>
#include <libftl/xml/labels/power.hpp>
#include <libftl/xml/labels/room.hpp>
#include <libftl/xml/labels/slot.hpp>
#include <libftl/xml/labels/start.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<libftl::impl::xml::typed::node_member_base<
    libftl::impl::xml::typed::required::no,
    libftl::xml::blueprints::system_element>>
libftl::impl::xml::blueprints::system_element_parser(std::string &&_name)
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_node_member_derived(typed::make_node_member<required::no>(
      std::move(_name),
      typed::attribute_set{fcppt::record::make(
          labels::power{} = typed::attribute<unsigned, required::yes>{"power"},
          labels::room{} = typed::attribute<unsigned, required::yes>{"room"},
          labels::start{} = typed::attribute<bool, required::no>{"start"},
          labels::img{} = typed::attribute<std::string, required::no>{"img"},
          labels::max{} = typed::attribute<unsigned, required::no>{"max"})},
      typed::optional_inner_node{typed::node_set{fcppt::record::make(
          labels::slot{} = typed::make_node_member<required::yes>(
              "slot",
              typed::attribute_set{fcppt::record::make()},
              typed::inner_node{typed::node_set{fcppt::record::make(
                  labels::direction{} = typed::make_node_member<required::no>(
                      "direction",
                      typed::attribute_set{fcppt::record::make()},
                      typed::content<libftl::xml::blueprints::direction>{}),
                  labels::number{} = typed::make_node_member<required::yes>(
                      "number",
                      typed::attribute_set{fcppt::record::make()},
                      typed::content<unsigned>{}))}}))}}));
}
