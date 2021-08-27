#include <libftl/ship/resources.hpp>
#include <libftl/ship/images/object.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/xml/ship/result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::ship::resources::resources(
    libftl::xml::ship::result &&_ship,
    libftl::ship::images::object &&_images,
    libftl::ship::layout::object &&_layout)
    : ship_{std::move(_ship)}, images_{std::move(_images)}, layout_{std::move(_layout)}
{
}

libftl::ship::resources::resources(resources &&) noexcept = default;

libftl::ship::resources &libftl::ship::resources::operator=(resources &&) noexcept = default;

libftl::ship::resources::~resources() = default;
