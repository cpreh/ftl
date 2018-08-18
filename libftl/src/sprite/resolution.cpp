#include <libftl/sprite/resolution.hpp>
#include <sge/renderer/screen_size.hpp>


sge::renderer::screen_size
libftl::sprite::resolution()
{
	return
			sge::renderer::screen_size{
				1280u,720u
			};
}
