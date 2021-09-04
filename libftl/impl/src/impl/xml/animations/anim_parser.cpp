#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/animations/anim_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/animations/anim.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/length.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/sheet.hpp>
#include <libftl/xml/labels/time.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::animations::anim, libftl::impl::xml::node>>
libftl::impl::xml::animations::anim_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "anim",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
          typed::inner_node{typed::node_set{fcppt::record::make(
              labels::sheet{} = typed::make_node_member<required::yes>(
                  "sheet",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::desc{} = typed::make_node_member<required::yes>(
                  "desc",
                  typed::attribute_set{fcppt::record::make(
                      labels::length{} = typed::attribute<unsigned, required::yes>{"length"},
                      labels::x{} = typed::attribute<unsigned, required::yes>{"x"},
                      labels::y{} = typed::attribute<unsigned, required::yes>{"y"})},
                  typed::empty{}),
              labels::time{} = typed::make_node_member<required::yes>(
                  "time",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<double>{}))}}}});
}
