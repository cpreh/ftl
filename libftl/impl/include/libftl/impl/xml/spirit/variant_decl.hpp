#ifndef LIBFTL_IMPL_XML_SPIRIT_VARIANT_DECL_HPP_INCLUDED
#define LIBFTL_IMPL_XML_SPIRIT_VARIANT_DECL_HPP_INCLUDED

#include <libftl/impl/xml/spirit/variant_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/variant/is_object.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace spirit
{

template<
	typename Variant
>
class variant
{
public:
	static_assert(
		fcppt::variant::is_object<
			Variant
		>::value,
		""
	);

	variant();

	template<
		typename Type
	>
	explicit
	variant(
		Type const &
	);

	template<
		typename Type
	>
	variant &
	operator=(
		Type const &
	);

	Variant const &
	get() const;
private:
	typedef
	fcppt::optional::object<
		Variant
	>
	optional;

	optional impl_;
};

}
}
}
}

#endif
