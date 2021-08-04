#ifndef LIBFTL_IMPL_XML_LOAD_FUNCTION_HPP_INCLUDED
#define LIBFTL_IMPL_XML_LOAD_FUNCTION_HPP_INCLUDED

#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <memory>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
template <typename Result>
using load_function = fcppt::function<std::unique_ptr<Result>(std::istream &)>;

}

#endif
