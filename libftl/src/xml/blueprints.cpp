#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/impl/xml/root_name.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/blueprints.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <regex>
#include <string>
#include <sstream>
#include <fcppt/config/external_end.hpp>


libftl::xml::result<
	libftl::xml::generated::blueprints_root
>
libftl::xml::blueprints(
	libftl::archive::file const &_file
)
{
	return
		libftl::impl::xml::read(
			_file,
			fcppt::function<
				std::unique_ptr<
					libftl::xml::generated::blueprints_root
				>(
					std::string const &
				)
			>{
				[](
					std::string const &_string
				)
				->
				std::unique_ptr<
					libftl::xml::generated::blueprints_root
				>
				{
					std::string const fixed{
						std::regex_replace(
							std::regex_replace(
								std::regex_replace(
									std::regex_replace(
										std::regex_replace(
											_string,
											std::regex{
												"</clonebay>\\r\\s*<clonebay"
											},
											"</medbay><clonebay"
										),
										std::regex{
											"</slot>\\r\\s*</slot>"
										},
										"</slot></shields>"
									),
									std::regex{
										"false\"img"
									},
									"false\" img"
								),
								std::regex{
									"true\"img"
								},
								"true\" img"
							),
							std::regex{
								"</ship>"
							},
							"</shipBlueprint>"
						)
					};

					std::istringstream stream{
						fixed
					};

					return
						libftl::xml::generated::blueprintsRoot(
							stream,
							xml_schema::flags::dont_validate
						);
				}
			},
			libftl::impl::xml::root_name{
				"blueprintsRoot"
			}
		);
}
