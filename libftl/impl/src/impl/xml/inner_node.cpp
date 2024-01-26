#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/node.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::impl::xml::inner_node::inner_node(
    libftl::impl::xml::inner_node_content &&_content, std::string &&_closing_tag)
    : content_{std::move(_content)}, closing_tag_{std::move(_closing_tag)}
{
}
