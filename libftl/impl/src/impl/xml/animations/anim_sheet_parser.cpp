#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/animations/anim_sheet_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/animations/anim_sheet.hpp>
#include <libftl/xml/labels/fh.hpp>
#include <libftl/xml/labels/fw.hpp>
#include <libftl/xml/labels/h.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/w.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::animations::anim_sheet, libftl::impl::xml::node>>
libftl::impl::xml::animations::anim_sheet_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return typed::make_derived(typed::node{
      "animSheet",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::name{} = typed::attribute<std::string, required::yes>{"name"},
              labels::w{} = typed::attribute<unsigned, required::yes>{"w"},
              labels::h{} = typed::attribute<unsigned, required::yes>{"h"},
              labels::fw{} = typed::attribute<unsigned, required::yes>{"fw"},
              labels::fh{} = typed::attribute<unsigned, required::yes>{"fh"})},
          typed::content<std::string>{}}});
}
