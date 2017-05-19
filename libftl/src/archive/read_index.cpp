#include <libftl/archive/entry.hpp>
#include <libftl/archive/index.hpp>
#include <libftl/archive/index_result.hpp>
#include <libftl/archive/length.hpp>
#include <libftl/archive/offset.hpp>
#include <libftl/archive/read_index.hpp>
#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <ios>
#include <istream>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::uint32_t
int_type;

typedef
alda::bindings::unsigned_<
	int_type,
	fcppt::endianness::format::little
>
int_binding;

typedef
std::vector<
	int_type
>
int_vector;

typedef
alda::bindings::dynamic_len<
	int_vector,
	int_binding,
	int_binding
>
offset_binding;

typedef
alda::bindings::fundamental<
	char
>
char_binding;

typedef
alda::bindings::dynamic_len<
	std::string,
	char_binding,
	int_binding
>
string_binding;

FCPPT_RECORD_MAKE_LABEL(
	size_label
);

FCPPT_RECORD_MAKE_LABEL(
	path_label
);

typedef
alda::bindings::record_variadic<
	fcppt::record::element<
		size_label,
		int_binding
	>,
	fcppt::record::element<
		path_label,
		string_binding
	>
>
record_binding;

typedef
std::pair<
	std::string,
	libftl::archive::entry
>
index_pair;

index_pair
transform_entry(
	int_type const _offset,
	alda::raw::element_type<
		record_binding
	> &&_result
)
{
	return
		std::make_pair(
			std::move(
				fcppt::record::get<
					path_label
				>(
					_result
				)
			),
			libftl::archive::entry{
				libftl::archive::offset{
					fcppt::cast::to_signed(
						_offset
						+
						alda::raw::needed_size<
							record_binding
						>(
							_result
						)
					)
				},
				libftl::archive::length{
					fcppt::cast::to_signed(
						fcppt::record::get<
							size_label
						>(
							_result
						)
					)
				}
			}
		);

}

fcppt::either::object<
	alda::raw::stream::error,
	index_pair
>
read_entry(
	std::istream &_stream,
	int_type const _offset
)
{
	_stream.seekg(
		fcppt::cast::to_signed(
			_offset
		),
		std::ios_base::beg
	);

	return
		fcppt::either::map(
			alda::raw::make_generic<
				alda::raw::stream::istream,
				record_binding
			>(
				_stream
			),
			[
				_offset
			](
				alda::raw::element_type<
					record_binding
				> &&_result
			)
			{
				return
					transform_entry(
						_offset,
						std::move(
							_result
						)
					);
			}
		);
}

fcppt::either::object<
	alda::raw::stream::error,
	libftl::archive::index
>
make_index(
	std::istream &_stream,
	alda::raw::element_type<
		offset_binding
	> const &_offsets
)
{
	return
		fcppt::either::map(
			fcppt::either::sequence<
				std::vector<
					index_pair
				>
			>(
				fcppt::algorithm::map<
					std::vector<
						fcppt::either::object<
							alda::raw::stream::error,
							index_pair
						>
					>
				>(
					_offsets,
					[
						&_stream
					](
						int_type const _offset
					)
					{
						return
							read_entry(
								_stream,
								_offset
							);
					}
				)
			),
			[](
				std::vector<
					index_pair
				> &&_indices
			)
			{
				return
					fcppt::algorithm::map<
						libftl::archive::index
					>(
						std::move(
							_indices
						),
						[](
							// TODO: Why does && not work here?
							index_pair _index
						)
						{
							return
								libftl::archive::index::value_type{
									std::move(
										_index.first
									),
									_index.second
								};
						}
					);
			}
		);
}

}

libftl::archive::index_result
libftl::archive::read_index(
	std::istream &_stream
)
{
	return
		fcppt::either::map_failure(
			fcppt::either::bind(
				alda::raw::make_generic<
					alda::raw::stream::istream,
					offset_binding
				>(
					_stream
				),
				[
					&_stream
				](
					alda::raw::element_type<
						offset_binding
					> const &_offsets
				)
				{
					return
						make_index(
							_stream,
							_offsets
						);
				}
			),
			[](
				alda::raw::stream::error &&_error
			){
				return
					fcppt::string{
						FCPPT_TEXT("Error reading index of .dat file: ")
						+
						std::move(
							_error.get()
						)
					};
			}
		);
}
