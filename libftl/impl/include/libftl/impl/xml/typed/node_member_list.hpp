#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_LIST_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_LIST_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/node_member_list_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
requires libftl::impl::xml::typed::parses<Parser, libftl::impl::xml::node>
class node_member_list
{
public:
  using inner_result = libftl::impl::xml::typed::result_type<Parser>;

  using result_type = std::vector<inner_result>;

  using arg_type = std::vector<fcppt::reference<libftl::impl::xml::node const>>;

  static constexpr libftl::impl::xml::typed::required const is_required =
      libftl::impl::xml::typed::required::no;
  static constexpr bool const is_optional = true;

  node_member_list(std::string &&_name, Parser &&_parser)
      : name_{std::move(_name)}, parser_{std::move(_parser)}
  {
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<fcppt::reference<libftl::impl::xml::node const>> const &_nodes) const
  {
    return fcppt::either::sequence<fcppt::either::object<libftl::error, result_type>>(
        fcppt::algorithm::map<std::vector<fcppt::either::object<libftl::error, inner_result>>>(
            _nodes,
            [this](fcppt::reference<libftl::impl::xml::node const> const _node)
            { return fcppt::deref(this->parser_).parse(_node.get()); }));
  }
private:
  std::string name_;
  Parser parser_;
};

template <typename Parser>
node_member_list(Parser &&) -> node_member_list<Parser>;
}

#endif
