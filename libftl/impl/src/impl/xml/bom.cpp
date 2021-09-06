#include <libftl/impl/xml/bom.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

std::string libftl::impl::xml::bom()
{
  return std::string{fcppt::cast::to_char_ptr<char const *>(u8"\uFEFF")};
}
