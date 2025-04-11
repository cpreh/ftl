#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/events/event_content_parser.hpp>
#include <libftl/impl/xml/events/event_parser_impl.hpp>
#include <libftl/impl/xml/events/text_parser_impl.hpp>
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
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_member_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/events/event.hpp>
#include <libftl/xml/events/event_content.hpp>
#include <libftl/xml/labels/auto_reward.hpp>
#include <libftl/xml/labels/choice_list.hpp>
#include <libftl/xml/labels/event.hpp>
#include <libftl/xml/labels/hidden.hpp>
#include <libftl/xml/labels/level.hpp>
#include <libftl/xml/labels/lvl.hpp>
#include <libftl/xml/labels/req.hpp>
#include <libftl/xml/labels/store.hpp>
#include <libftl/xml/labels/text.hpp>
#include <fcppt/deref_reference.hpp> // IWYU pragma: keep
#include <fcppt/deref_unique_ptr.hpp> // IWYU pragma: keep
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace
{

namespace typed = libftl::impl::xml::typed;
namespace labels = libftl::xml::labels;
using typed::required;

class event_content_impl : public typed::base<
                               libftl::xml::events::event_content,
                               fcppt::optional::object<libftl::impl::xml::inner_node>>
{
  FCPPT_NONMOVABLE(event_content_impl);

  [[nodiscard]] auto choice_list() const
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
                    "text", libftl::impl::xml::events::text_parser_impl()),
                labels::event{} = typed::make_node_member_impl<required::yes>(
                    "event",
                    typed::make_construct<fcppt::recursive<libftl::xml::events::event>>(
                        libftl::impl::xml::events::event_parser_impl(
                            fcppt::make_cref(this->impl_)))))}}}};
  }
public:
  using result_type = libftl::xml::events::event_content;
  using arg_type = fcppt::optional::object<libftl::impl::xml::inner_node>;

  event_content_impl()
      : impl_{typed::make_derived(typed::inner_node{typed::node_set{fcppt::record::make(
            labels::text{} = typed::make_node_member_impl<required::yes>(
                "text", libftl::impl::xml::events::text_parser_impl()),
            labels::choice_list{} = this->choice_list(),
            labels::auto_reward{} = typed::make_node_member<required::no>(
                "autoReward",
                typed::attribute_set{fcppt::record::make(
                    labels::level{} = typed::attribute<std::string, required::yes>{"level"})},
                typed::content<std::string>{}),
            labels::store{} = typed::make_node_member<required::no>(
                "store", typed::attribute_set{fcppt::record::make()}, typed::empty{}))}})}
  {
  }

  ~event_content_impl() override = default;

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(arg_type const &_node) const override
  {
    return this->impl_->parse(_node);
  }
private:
  fcppt::unique_ptr<libftl::impl::xml::typed::base<result_type, arg_type>> const impl_;
};
}

fcppt::unique_ptr<libftl::impl::xml::typed::base<
    libftl::xml::events::event_content,
    fcppt::optional::object<libftl::impl::xml::inner_node>>>
libftl::impl::xml::events::event_content_parser()
{
  return typed::make_derived(fcppt::unique_ptr_to_base<libftl::impl::xml::typed::base<
                                 libftl::xml::events::event_content,
                                 fcppt::optional::object<libftl::impl::xml::inner_node>>>(
      fcppt::make_unique_ptr<event_content_impl>()));
}
