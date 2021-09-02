#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_LIST_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_LIST_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/node_member_list_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/node.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Attributes, typename Content>
requires libftl::impl::xml::typed::parses<Content,fcppt::optional::object<libftl::impl::xml::inner_node>>
class node_member_list
{
public:
  using inner_result = libftl::xml::node<
      libftl::impl::xml::typed::result_type<Attributes>,
      libftl::impl::xml::typed::result_type<Content>>;

  using result_type = std::vector<inner_result>;

  using arg_type = std::vector<fcppt::reference<libftl::impl::xml::node const>>;

  static constexpr libftl::impl::xml::typed::required const is_required =
      libftl::impl::xml::typed::required::no;
  static constexpr bool const is_optional = true;

  node_member_list(std::string &&_name, Attributes &&_attributes, Content &&_content)
      : name_{std::move(_name)}, attributes_{std::move(_attributes)}, content_{std::move(_content)}
  {
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<fcppt::reference<libftl::impl::xml::node const>> const &_nodes) const
  {
    return fcppt::either::sequence<fcppt::either::object<libftl::error, result_type>>(
        fcppt::algorithm::map<std::vector<
            fcppt::either::object<libftl::error, inner_result>>>(
            _nodes,
            [this](fcppt::reference<libftl::impl::xml::node const> const _node)
            {
              return fcppt::either::bind(
                  fcppt::deref(this->attributes_).parse(_node->attributes_),
                  [this,
                   &_node](libftl::impl::xml::typed::result_type<Attributes> &&_attributes_result)
                  {
                    return fcppt::either::map(
                        fcppt::deref(this->content_).parse(_node->content_),
                        [&_attributes_result](
                            libftl::impl::xml::typed::result_type<Content> &&_content_result) {
                          return libftl::xml::node{
                              std::move(_attributes_result), std::move(_content_result)};
                        });
                  });
            }));
  }
private:
  std::string name_;
  Attributes attributes_;
  Content content_;
};

template <typename Attributes, typename Content>
node_member_list(Attributes &&, Content &&) -> node_member_list<Attributes, Content>;
}

#endif
