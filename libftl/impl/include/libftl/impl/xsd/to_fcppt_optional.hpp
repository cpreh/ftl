#ifndef LIBFTL_IMPL_XSD_TO_FCPPT_OPTIONAL_HPP_INCLUDED
#define LIBFTL_IMPL_XSD_TO_FCPPT_OPTIONAL_HPP_INCLUDED

#include <fcppt/make_cref.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/tree/containers.hxx>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace xsd
{

template<
	typename Type
>
inline
fcppt::optional::reference<
	Type const
>
to_fcppt_optional(
	fcppt::reference<
		::xsd::cxx::tree::optional<
			Type
		> const
	> const _optional
)
{
	return
		fcppt::optional::make_if(
			_optional.get().present(),
			[
				&_optional
			]{
				return
					fcppt::make_cref(
						*_optional.get()
					);
			}
		);
}

}
}
}

#endif
