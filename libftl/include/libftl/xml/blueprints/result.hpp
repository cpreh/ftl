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
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
using result = fcppt::tuple::object<
  std::vector<libftl::xml::blueprints::aug>,
  std::vector<libftl::xml::blueprints::crew>,
  std::vector<libftl::xml::blueprints::drone>,
  std::vector<libftl::xml::blueprints::item>,
  std::vector<libftl::xml::blueprints::list>,
  std::vector<libftl::xml::blueprints::ship>,
  std::vector<libftl::xml::blueprints::system>,
  std::vector<libftl::xml::blueprints::weapon>
>;

}

#endif
