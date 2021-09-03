#ifndef LIBFTL_XML_ANIMATIONS_RESULT_HPP_INCLUDED
#define LIBFTL_XML_ANIMATIONS_RESULT_HPP_INCLUDED

#include <libftl/xml/animations/anim.hpp>
#include <libftl/xml/animations/anim_sheet.hpp>
#include <libftl/xml/animations/weapon_anim.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::animations
{
using result = fcppt::tuple::object<
  std::vector<libftl::xml::animations::anim>,
  std::vector<libftl::xml::animations::anim_sheet>,
  std::vector<libftl::xml::animations::weapon_anim>
>;

}

#endif
