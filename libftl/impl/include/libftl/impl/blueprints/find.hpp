#ifndef LIBFTL_IMPL_BLUEPRINTS_FIND_HPP_INCLUDED
#define LIBFTL_IMPL_BLUEPRINTS_FIND_HPP_INCLUDED

#include <libftl/blueprints/data.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/container/array/make.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace blueprints
{

template<
	typename Type
>
fcppt::optional::reference<
	Type const
>
find(
	fcppt::function<
		::xsd::cxx::tree::sequence<
			Type
		> const & (
			libftl::xml::generated::blueprints::blueprints_root const &
		)
	> const _get_elements,
	fcppt::function<
		bool (
			Type const &
		)
	> const _compare_element,
	fcppt::reference<
		libftl::blueprints::data const
	> const _data
)
{
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)

	return
		fcppt::algorithm::find_by_opt(
			fcppt::container::array::make(
				// TODO: Add option to enable DLC or not
				fcppt::make_cref(
					_data.get().dlc_blueprints_overwrites_.get()
				),
				fcppt::make_cref(
					_data.get().dlc_blueprints_.get()
				),
				fcppt::make_cref(
					_data.get().normal_blueprints_.get()
				)
			),
			[
				&_get_elements,
				&_compare_element
			](
				fcppt::reference<
					std::vector<
						fcppt::unique_ptr<
							libftl::xml::generated::blueprints::blueprints_root
						>
					> const
				> const _root_list
			)
			->
			fcppt::optional::reference<
				Type const
			>
			{
				return
					fcppt::algorithm::find_by_opt(
						_root_list.get(),
						[
							&_get_elements,
							&_compare_element
						](
							fcppt::unique_ptr<
								libftl::xml::generated::blueprints::blueprints_root
							> const &_root
						)
						->
						fcppt::optional::reference<
							Type const
						>
						{
							return
								fcppt::optional::deref(
									fcppt::algorithm::find_if_opt(
										_get_elements(
											*_root
										),
										_compare_element
									)
								);
						}
					);
			}
		);

	FCPPT_PP_POP_WARNING
}

}
}
}

#endif
