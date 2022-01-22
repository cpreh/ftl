#ifndef LIBFTL_XML_BLUEPRINTS_RESULT_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_RESULT_HPP_INCLUDED

#include <libftl/xml/blueprints/aug.hpp>
#include <libftl/xml/blueprints/crew.hpp>
#include <libftl/xml/blueprints/drone.hpp>
#include <libftl/xml/blueprints/item.hpp>
#include <libftl/xml/blueprints/list.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <libftl/xml/blueprints/system.hpp>
#include <libftl/xml/blueprints/weapon.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
struct result
{
  result(
      std::vector<libftl::xml::blueprints::aug> &&,
      std::vector<libftl::xml::blueprints::crew> &&,
      std::vector<libftl::xml::blueprints::drone> &&,
      std::vector<libftl::xml::blueprints::item> &&,
      std::vector<libftl::xml::blueprints::list> &&,
      std::vector<libftl::xml::blueprints::ship> &&,
      std::vector<libftl::xml::blueprints::system> &&,
      std::vector<libftl::xml::blueprints::weapon> &&);

  std::vector<libftl::xml::blueprints::aug> augmentations;
  std::vector<libftl::xml::blueprints::crew> crews;
  std::vector<libftl::xml::blueprints::drone> drones;
  std::vector<libftl::xml::blueprints::item> items;
  std::vector<libftl::xml::blueprints::list> lists;
  std::vector<libftl::xml::blueprints::ship> ships;
  std::vector<libftl::xml::blueprints::system> systems;
  std::vector<libftl::xml::blueprints::weapon> weapons;
};
}

#endif
