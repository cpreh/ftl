#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/impl/xml/replace_list.hpp>
#include <libftl/impl/xml/root_name.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/achievements.hpp>
#include <libftl/xml/generated/achievements.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <string>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::achievements_root
>
libftl::xml::achievements(
	libftl::archive::file const &_file
)
{
	return
		libftl::impl::xml::read(
			_file,
			fcppt::function<
				std::unique_ptr<
					libftl::xml::generated::achievements_root
				>(
					std::string const &
				)
			>{
				[](
					std::string const &_string
				)
				->
				std::unique_ptr<
					libftl::xml::generated::achievements_root
				>
				{
					return
						libftl::xml::generated::achievementsRoot(
							_string,
							xml_schema::flags::dont_validate
						);
				}
			},
			libftl::impl::xml::root_name{
				"achievementsRoot"
			},
			libftl::impl::xml::replace_list{}
		);
}
