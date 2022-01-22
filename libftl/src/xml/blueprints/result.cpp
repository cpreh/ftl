#include <libftl/xml/blueprints/aug.hpp>
#include <libftl/xml/blueprints/crew.hpp>
#include <libftl/xml/blueprints/drone.hpp>
#include <libftl/xml/blueprints/item.hpp>
#include <libftl/xml/blueprints/list.hpp>
#include <libftl/xml/blueprints/result.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <libftl/xml/blueprints/system.hpp>
#include <libftl/xml/blueprints/weapon.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

libftl::xml::blueprints::result::result(
    std::vector<libftl::xml::blueprints::aug> &&_augmentations,
    std::vector<libftl::xml::blueprints::crew> &&_crews,
    std::vector<libftl::xml::blueprints::drone> &&_drones,
    std::vector<libftl::xml::blueprints::item> &&_items,
    std::vector<libftl::xml::blueprints::list> &&_lists,
    std::vector<libftl::xml::blueprints::ship> &&_ships,
    std::vector<libftl::xml::blueprints::system> &&_systems,
    std::vector<libftl::xml::blueprints::weapon> &&_weapons)
    : augmentations{std::move(_augmentations)},
      crews{std::move(_crews)},
      drones{std::move(_drones)},
      items{std::move(_items)},
      lists{std::move(_lists)},
      ships{std::move(_ships)},
      systems{std::move(_systems)},
      weapons{std::move(_weapons)}
{
}
