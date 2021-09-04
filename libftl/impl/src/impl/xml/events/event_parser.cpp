#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/events/event_parser.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_construct.hpp>
#include <libftl/impl/xml/typed/make_derived.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_member_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/events/event.hpp>
#include <libftl/xml/events/event_members.hpp>
#include <libftl/xml/labels/choice_list.hpp>
#include <libftl/xml/labels/event.hpp>
#include <libftl/xml/labels/hidden.hpp>
#include <libftl/xml/labels/lvl.hpp>
#include <libftl/xml/labels/req.hpp>
#include <libftl/xml/labels/text.hpp>
#include <fcppt/deref_reference.hpp>
#include <fcppt/deref_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
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

auto event_attributes()
{
  return typed::attribute_set{fcppt::record::make(
      labels::name{} = typed::attribute<std::string, required::yes>{"name"},
      labels::unique{} = typed::attribute<bool, required::no>{"unique"})};
}

class event_impl : public typed::base<
                       fcppt::recursive<libftl::xml::events::event_members>,
                       fcppt::optional::object<libftl::impl::xml::inner_node>>
{
  FCPPT_NONMOVABLE(event_impl);

public:
  using result_type = fcppt::recursive<libftl::xml::events::event_members>;
  using arg_type = fcppt::optional::object<libftl::impl::xml::inner_node>;

  event_impl()
      : event_{typed::make_derived(
            typed::make_construct<fcppt::recursive<libftl::xml::events::event_members>>(
                typed::make_construct<libftl::xml::events::event_members>(
                    typed::inner_node{typed::node_set{fcppt::record::make(
                        labels::text{} = typed::make_node_member<required::yes>(
                            "text",
                            typed::attribute_set{fcppt::record::make()},
                            typed::content<std::string>{}),
                        labels::choice_list{} = typed::node_member_list{
                            "choice",
                            typed::attribute_set{fcppt::record::make(
                                labels::hidden{} = typed::attribute<bool, required::no>{"hidden"},
                                labels::req{} = typed::attribute<std::string, required::no>{"req"},
                                labels::lvl{} = typed::attribute<unsigned, required::no>{"lvl"})},
                            typed::inner_node{typed::node_set{fcppt::record::make(
                                labels::text{} = typed::make_node_member<required::yes>(
                                    "text",
                                    typed::attribute_set{fcppt::record::make()},
                                    typed::content<std::string>{}),
                                labels::event{} = typed::make_node_member<required::yes>(
                                    "event",
                                    event_attributes(),
                                    fcppt::make_cref(this->event_)))}}})}})))}
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
      typed::node_content{
          event_attributes(),
          fcppt::unique_ptr_to_base<libftl::impl::xml::typed::base<
              fcppt::recursive<libftl::xml::events::event_members>,
              fcppt::optional::object<libftl::impl::xml::inner_node>>>(
              fcppt::make_unique_ptr<event_impl>())}});
}
