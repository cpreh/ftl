#ifndef LIBFTL_IMPL_XML_TYPED_NODE_LIST_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_LIST_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
class node_list
{
public:
  using result_type = std::vector<libftl::impl::xml::typed::result_type<Parser>>;

  explicit node_list(Parser &&_parser) : parser_{std::move(_parser)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node_vector const &_nodes) const
  {
    return fcppt::either::sequence<fcppt::either::object<libftl::error, result_type>>(
        fcppt::algorithm::map<std::vector<
            fcppt::either::object<libftl::error, libftl::impl::xml::typed::result_type<Parser>>>>(
            _nodes,
            [this](fcppt::recursive<libftl::impl::xml::node> const &_node)
            { return fcppt::deref(this->parser_).parse(_node.get()); }));
  }
private:
  Parser parser_;
};

template <typename Parser>
node_list(Parser &&) -> node_list<Parser>;
}

#endif
