#include <libftl/xml/errors/alternative.hpp>
#include <libftl/xml/type_error.hpp>
#include <fcppt/recursive_comparison.hpp> // IWYU pragma: keep
#include <fcppt/recursive_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

libftl::xml::errors::alternative::alternative(
    std::vector<fcppt::recursive<libftl::xml::type_error>> &&_errors)
    : errors_{std::move(_errors)}
{
}

bool libftl::xml::errors::alternative::operator==(libftl::xml::errors::alternative const &) const =
    default;
