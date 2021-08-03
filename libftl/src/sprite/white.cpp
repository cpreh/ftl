#include <libftl/sprite/color.hpp>
#include <libftl/sprite/color_format.hpp>
#include <libftl/sprite/white.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>

libftl::sprite::color libftl::sprite::white()
{
  return sge::image::color::convert<libftl::sprite::color_format>(
      sge::image::color::predef::white());
}
