#ifndef LIBFTL_BLUEPRINTS_DATA_HPP_INCLUDED
#define LIBFTL_BLUEPRINTS_DATA_HPP_INCLUDED

#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace blueprints
{

class data
{
	FCPPT_NONCOPYABLE(
		data
	);
public:
	typedef
	std::vector<
		fcppt::unique_ptr<
			libftl::xml::generated::blueprints::blueprints_root
		>
	>
	blueprint_vector;

	FCPPT_MAKE_STRONG_TYPEDEF(
		blueprint_vector,
		normal_blueprints
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		blueprint_vector,
		dlc_blueprints
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		blueprint_vector,
		dlc_blueprints_overwrites
	);

	LIBFTL_DETAIL_SYMBOL
	data(
		normal_blueprints &&,
		dlc_blueprints &&,
		dlc_blueprints_overwrites &&
	);

	LIBFTL_DETAIL_SYMBOL
	data(
		data &&
	);

	LIBFTL_DETAIL_SYMBOL
	data &
	operator=(
		data &&
	);

	LIBFTL_DETAIL_SYMBOL
	~data();

	normal_blueprints normal_blueprints_;

	dlc_blueprints dlc_blueprints_;

	dlc_blueprints_overwrites dlc_blueprints_overwrites_;
};

}
}

#endif
