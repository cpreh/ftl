#include <libftl/options/create_resource_parser.hpp>
#include <libftl/options/data_file_label.hpp>
#include <libftl/options/native_resource_record.hpp>
#include <libftl/options/resource_file_label.hpp>
#include <libftl/options/resource_label.hpp>
#include <libftl/options/resource_parser.hpp>
#include <libftl/options/resource_path_label.hpp>
#include <libftl/options/resource_record.hpp>
#include <libftl/options/unpacked_resource_record.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_base.hpp>
#include <fcppt/options/make_sum.hpp>
#include <fcppt/options/no_default_value.hpp>
#include <fcppt/options/option.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


fcppt::unique_ptr<
	libftl::options::resource_parser
>
libftl::options::create_resource_parser()
{
	return
		fcppt::options::make_base<
			libftl::options::resource_record
		>(
			fcppt::options::make_sum<
				libftl::options::resource_label
			>(
				fcppt::options::make_base<
					libftl::options::native_resource_record
				>(
					fcppt::options::apply(
						fcppt::options::option<
							libftl::options::data_file_label,
							std::filesystem::path
						>{
							fcppt::options::optional_short_name{},
							fcppt::options::long_name{
								FCPPT_TEXT("data-file")
							},
							fcppt::options::no_default_value<
								std::filesystem::path
							>(),
							fcppt::options::optional_help_text{
								fcppt::options::help_text{
									FCPPT_TEXT("Path to FTL's data.dat file")
								}
							}
						},
						fcppt::options::option<
							libftl::options::resource_file_label,
							std::filesystem::path
						>{
							fcppt::options::optional_short_name{},
							fcppt::options::long_name{
								FCPPT_TEXT("resource-file")
							},
							fcppt::options::no_default_value<
								std::filesystem::path
							>(),
							fcppt::options::optional_help_text{
								fcppt::options::help_text{
									FCPPT_TEXT("Path to FTL's resource.dat file")
								}
							}
						}
					)
				),
				fcppt::options::make_base<
					libftl::options::unpacked_resource_record
				>(
					fcppt::options::option<
						libftl::options::resource_path_label,
						std::filesystem::path
					>{
						fcppt::options::optional_short_name{},
						fcppt::options::long_name{
							FCPPT_TEXT("resource-path")
						},
						fcppt::options::no_default_value<
							std::filesystem::path
						>(),
						fcppt::options::optional_help_text{
							fcppt::options::help_text{
								FCPPT_TEXT("Path to unpacked FTL files")
							}
						}
					}
				)
			)
		);
}
