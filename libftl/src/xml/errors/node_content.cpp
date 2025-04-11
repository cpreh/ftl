#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/node_content.hpp>
#include <fcppt/recursive_comparison.hpp> // IWYU pragma: keep
#include <fcppt/optional/comparison.hpp> // IWYU pragma: keep
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::xml::errors::node_content::node_content(
    fcppt::optional::object<fcppt::parse::location> const _location,
    libftl::xml::type_error &&_error)
    : location_{_location}, error_{std::move(_error)}
{
}

bool libftl::xml::errors::node_content::operator==(
    libftl::xml::errors::node_content const &) const = default;
