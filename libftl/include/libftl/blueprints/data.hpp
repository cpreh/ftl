#ifndef LIBFTL_BLUEPRINTS_DATA_HPP_INCLUDED
#define LIBFTL_BLUEPRINTS_DATA_HPP_INCLUDED

#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/blueprints/result.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::blueprints
{
class data
{
  FCPPT_NONCOPYABLE(data);

public:
  using blueprint_vector = std::vector<libftl::xml::blueprints::result>;

  FCPPT_DECLARE_STRONG_TYPEDEF(blueprint_vector, normal_blueprints);

  FCPPT_DECLARE_STRONG_TYPEDEF(blueprint_vector, dlc_blueprints);

  FCPPT_DECLARE_STRONG_TYPEDEF(blueprint_vector, dlc_blueprints_overwrites);

  LIBFTL_DETAIL_SYMBOL
  data(normal_blueprints &&, dlc_blueprints &&, dlc_blueprints_overwrites &&);

  LIBFTL_DETAIL_SYMBOL
  data(data &&) noexcept;

  LIBFTL_DETAIL_SYMBOL
  data &operator=(data &&) noexcept;

  LIBFTL_DETAIL_SYMBOL
  ~data();

  normal_blueprints normal_blueprints_;

  dlc_blueprints dlc_blueprints_;

  dlc_blueprints_overwrites dlc_blueprints_overwrites_;
};

}

#endif
