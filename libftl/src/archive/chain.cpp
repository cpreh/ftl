#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/chain.hpp>
#include <libftl/impl/archive/chain.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


libftl::archive::base_unique_ptr
libftl::archive::chain(
	libftl::archive::base_unique_ptr &&_archive1,
	libftl::archive::base_unique_ptr &&_archive2
)
{
	return
		fcppt::unique_ptr_to_base<
			libftl::archive::base
		>(
			fcppt::make_unique_ptr<
				libftl::impl::archive::chain
			>(
				std::move(
					_archive1
				),
				std::move(
					_archive2
				)
			)
		);
}
