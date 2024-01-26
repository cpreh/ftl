#ifndef LIBFTL_IMPL_XML_TYPED_PARTITION_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_PARTITION_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/parses.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/variant/partition.hpp>
#include <fcppt/variant/partition_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
requires libftl::impl::xml::typed::parses<Parser, libftl::impl::xml::node_vector>
class partition
{
public:
  using result_type =
      fcppt::variant::partition_result<libftl::impl::xml::typed::result_type<Parser>>;
  using arg_type = libftl::impl::xml::node_vector;

  explicit partition(Parser &&_parser) : parser_{std::move(_parser)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node_vector const &_nodes) const
  {
    return fcppt::either::map(
        fcppt::deref(this->parser_).parse(_nodes),
        [](libftl::impl::xml::typed::result_type<Parser> &&_result)
        { return fcppt::variant::partition(std::move(_result)); });
  }
private:
  Parser parser_;
};

template <typename Parser>
partition(Parser &&) -> partition<Parser>;
}

#endif
