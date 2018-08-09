#ifndef LIBFTL_BLUEPRINTS_FIND_SHIP_HPP_INCLUDED
#define LIBFTL_BLUEPRINTS_FIND_SHIP_HPP_INCLUDED

#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace blueprints
{

LIBFTL_DETAIL_SYMBOL
fcppt::optional::reference<
	libftl::xml::generated::blueprints::ship_blueprint const
>
find_ship(
	fcppt::reference<
		libftl::blueprints::data const
	>,
	std::string const &
);

}
}

#endif
