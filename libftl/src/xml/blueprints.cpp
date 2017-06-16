#include <libftl/archive/file_fwd.hpp>
#include <libftl/impl/xml/load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/impl/xml/replace.hpp>
#include <libftl/impl/xml/replace_list.hpp>
#include <libftl/impl/xml/root_name.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/blueprints.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <regex>
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
			libftl::impl::xml::load_function<
				libftl::xml::generated::blueprints_root
			>{
				[](
					std::istream &_stream
				)
				->
				std::unique_ptr<
					libftl::xml::generated::blueprints_root
				>
				{
					return
						libftl::xml::generated::blueprintsRoot(
							_stream,
							xml_schema::flags::dont_validate
						);
				}
			},
			libftl::impl::xml::root_name{
				"blueprintsRoot"
			},
			libftl::impl::xml::replace_list{
				libftl::impl::xml::replace{
					std::regex{
						"</clonebay>\\r\\s*<clonebay"
					},
					"</medbay><clonebay"
				},
				libftl::impl::xml::replace{
					std::regex{
						"</slot>\\r\\s*</slot>"
					},
					"</slot></shields>"
				},
				libftl::impl::xml::replace{
					std::regex{
						"false\"img"
					},
					"false\" img"
				},
				libftl::impl::xml::replace{
					std::regex{
						"true\"img"
					},
					"true\" img"
				},
				libftl::impl::xml::replace{
					std::regex{
						"</ship>"
					},
					"</shipBlueprint>"
				}
			}
		);
}
