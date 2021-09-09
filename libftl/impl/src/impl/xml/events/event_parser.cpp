#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/events/event_parser.hpp>
#include <libftl/impl/xml/events/text_parser_impl.hpp>
#include <libftl/impl/xml/typed/alternative.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_construct.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/make_node_member_impl.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_member_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/events/event.hpp>
#include <libftl/xml/labels/choice_list.hpp>
#include <libftl/xml/labels/event.hpp>
#include <libftl/xml/labels/hidden.hpp>
#include <libftl/xml/labels/load.hpp>
#include <libftl/xml/labels/lvl.hpp>
#include <libftl/xml/labels/req.hpp>
#include <libftl/xml/labels/store.hpp>
#include <libftl/xml/labels/text.hpp>
#include <fcppt/deref_reference.hpp>
#include <fcppt/deref_unique_ptr.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace
{

namespace typed = libftl::impl::xml::typed;
namespace labels = libftl::xml::labels;
using typed::required;

class event_impl
    : public typed::base<libftl::xml::events::event, libftl::impl::xml::node>
{
  FCPPT_NONMOVABLE(event_impl);

  auto choice_list() const
  {
    return typed::node_member_list{
        "choice",
        typed::node_content{
            typed::attribute_set{fcppt::record::make(
                labels::hidden{} = typed::attribute<bool, required::no>{"hidden"},
                labels::req{} = typed::attribute<std::string, required::no>{"req"},
                labels::lvl{} = typed::attribute<unsigned, required::no>{"lvl"})},
            typed::inner_node{typed::node_set{fcppt::record::make(
                labels::text{} = typed::make_node_member_impl<required::yes>(
                    "text",
                    libftl::impl::xml::events::text_parser_impl()),
                labels::event{} = typed::make_node_member_impl<required::yes>(
                    "event",
                    typed::make_construct<fcppt::recursive<libftl::xml::events::event>>(
                        fcppt::make_cref(this->event_))))}}}};
  }
public:
  using result_type = libftl::xml::events::event;
  using arg_type = libftl::impl::xml::node;

  event_impl()
      : event_{typed::make_derived(typed::make_construct<
                                   libftl::xml::events::event>(typed::alternative{
            typed::node_content{
                typed::attribute_set{fcppt::record::make()},
                typed::inner_node{typed::node_set{fcppt::record::make(
                    labels::text{} = typed::make_node_member_impl<required::yes>(
                        "text",
                        libftl::impl::xml::events::text_parser_impl()),
                    labels::choice_list{} = this->choice_list(),
                    labels::store{} = typed::make_node_member<required::no>(
                        "store", typed::attribute_set{fcppt::record::make()}, typed::empty{}))}}},
            typed::node_content{
                typed::attribute_set{fcppt::record::make(
                    labels::load{} = typed::attribute<std::string, required::yes>{"load"})},
                typed::empty{}}}))}
  {
}

  ~event_impl() override = default;

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(arg_type const &_node) const override
  {
    return this->event_->parse(_node);
  }
private:
  fcppt::unique_ptr<libftl::impl::xml::typed::base<result_type, arg_type>> const event_;
};

}

fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::events::event, libftl::impl::xml::node>>
libftl::impl::xml::events::event_parser()
{
  return typed::make_derived(typed::node{
      "event",
      fcppt::unique_ptr_to_base<
          libftl::impl::xml::typed::base<libftl::xml::events::event, libftl::impl::xml::node>>(
          fcppt::make_unique_ptr<event_impl>())});
}
