#ifndef LIBFTL_IMPL_SPIRIT_VARIANT_OUTPUT_HPP_INCLUDED
#define LIBFTL_IMPL_SPIRIT_VARIANT_OUTPUT_HPP_INCLUDED

#include <libftl/impl/spirit/variant_impl.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace spirit
{

template<
	typename Variant
>
std::ostream &
operator<<(
	std::ostream &_stream,
	libftl::impl::spirit::variant<
		Variant
	> const &_variant
)
{
	return
		_stream
		<<
		_variant.get();
}

}
}
}

#endif
