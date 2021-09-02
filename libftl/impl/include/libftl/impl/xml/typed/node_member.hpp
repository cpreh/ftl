#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/node_member_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/node.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/uncons.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/iterator/range.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/range/empty.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <libftl::impl::xml::typed::required Required, typename Attributes, typename Content>
requires libftl::impl::xml::typed::parses<Content,fcppt::optional::object<libftl::impl::xml::inner_node>>
class node_member
{
public:
  using result_type = libftl::xml::node<
      libftl::impl::xml::typed::result_type<Attributes>,
      libftl::impl::xml::typed::result_type<Content>>;

  using arg_type = std::vector<fcppt::reference<libftl::impl::xml::node const>>;

  static constexpr libftl::impl::xml::typed::required const is_required = Required;
  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::required::no);

  node_member(std::string &&_name, Attributes &&_attributes, Content &&_content)
      : name_{std::move(_name)}, attributes_{std::move(_attributes)}, content_{std::move(_content)}
  {
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<fcppt::reference<libftl::impl::xml::node const>> const &_nodes) const
  {
    return fcppt::either::bind(
        fcppt::either::from_optional(
            fcppt::container::uncons(_nodes),
            [this]
            {
              return libftl::error{
                  fcppt::string{FCPPT_TEXT("Missing node ")} + fcppt::from_std_string(this->name_) +
                  FCPPT_TEXT(".")};
            }),
        [this](fcppt::tuple::object<
               fcppt::reference<fcppt::reference<libftl::impl::xml::node const> const>,
               fcppt::iterator::range<std::vector<
                   fcppt::reference<libftl::impl::xml::node const>>::const_iterator>> const &_split)
        {
          libftl::impl::xml::node const &node{fcppt::tuple::get<0U>(_split).get().get()};

          return fcppt::range::empty(fcppt::tuple::get<1U>(_split))
                     ? fcppt::either::bind(
                           fcppt::deref(this->attributes_).parse(node.attributes_),
                           [this, &node](libftl::impl::xml::typed::result_type<Attributes>
                                             &&_attributes_result)
                           {
                             return fcppt::either::map(
                                 fcppt::deref(this->content_).parse(node.content_),
                                 [&_attributes_result](
                                     libftl::impl::xml::typed::result_type<Content>
                                         &&_content_result) {
                                   return result_type{
                                       std::move(_attributes_result), std::move(_content_result)};
                                 });
                           })
                     : fcppt::either::make_failure<result_type>(libftl::error{
                           fcppt::string{FCPPT_TEXT("Excess nodes ")} +
                           fcppt::from_std_string(this->name_) + FCPPT_TEXT(".")});
        });
  }
private:
  std::string name_;
  Attributes attributes_;
  Content content_;
};

}

#endif
