#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/entry.hpp>
#include <libftl/archive/extract.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/archive/index.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/impl/archive/native.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fstream>
#include <ios>
#include <istream>
#include <streambuf>
#include <sstream>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

// TODO: Put this into fcppt?
class io_buf
:
public
	std::streambuf
{
	FCPPT_NONCOPYABLE(
		io_buf
	);
public:
	explicit
	io_buf(
		fcppt::io::buffer &&_buffer
	)
	:
		std::streambuf{},
		buffer_{
			std::move(
				_buffer
			)
		}
	{
		this->setg(
			this->buffer_.data(),
			this->buffer_.data(),
			this->buffer_.data_end()
		);
	}

	~io_buf()
	override
	{
	}
private:
	fcppt::io::buffer buffer_;
};

class io_istream
:
public
	std::istream
{
	FCPPT_NONCOPYABLE(
		io_istream
	);
public:
	explicit
	io_istream(
		fcppt::io::buffer &&_buffer
	)
	:
		std::istream{
			&buf_
		},
		buf_{
			std::move(
				_buffer
			)
		}
	{
	}

	~io_istream()
	override
	{
	}
private:
	io_buf buf_;
};

}

libftl::impl::archive::native::native(
	boost::filesystem::path &&_file_path,
	libftl::archive::index &&_index
)
:
	libftl::archive::base{},
	file_path_{
		std::move(
			_file_path
		)
	},
	index_{
		std::move(
			_index
		)
	}
{
}

libftl::impl::archive::native::~native()
{
}

fcppt::either::object<
	libftl::error,
	fcppt::unique_ptr<
		std::istream
	>
>
libftl::impl::archive::native::open(
	libftl::archive::path const &_path
)
{
	return
		fcppt::either::bind(
			fcppt::either::from_optional(
				fcppt::filesystem::open<
					std::ifstream
				>(
					this->file_path_,
					std::ios_base::binary
				),
				[
					this
				]{
					return
						libftl::error{
							FCPPT_TEXT("Unable to open ")
							+
							fcppt::filesystem::path_to_string(
								this->file_path_
							)
						};
				}
			),
			[
				&_path,
				this
			](
				std::ifstream &&_stream
			)
			{
				return
					fcppt::either::bind(
						fcppt::either::from_optional(
							fcppt::container::find_opt_mapped(
								this->index_,
								_path.rep()
							),
							[
								&_path,
								this
							]{
								return
									libftl::error{
										FCPPT_TEXT("Missing path ")
										+
										fcppt::from_std_string(
											_path.rep()
										)
										+
										FCPPT_TEXT(" in ")
										+
										fcppt::filesystem::path_to_string(
											this->file_path_
										)
									};
							}
						),
						[
							&_path,
							this,
							&_stream
						](
							fcppt::reference<
								libftl::archive::entry const
							> const _entry
						)
						{
							return
								fcppt::either::map(
									fcppt::either::from_optional(
										libftl::archive::extract(
											libftl::archive::file{
												fcppt::reference_to_base<
													std::istream
												>(
													fcppt::make_ref(
														_stream
													)
												),
												_entry.get()
											}
										),
										[
											&_path,
											this
										]{
											return
												libftl::error{
													FCPPT_TEXT("Failed to read ")
													+
													fcppt::from_std_string(
														_path.rep()
													)
													+
													FCPPT_TEXT(" in ")
													+
													fcppt::filesystem::path_to_string(
														this->file_path_
													)
												};
										}
									),
									[](
										fcppt::io::buffer &&_buffer
									)
									{
										return
											fcppt::unique_ptr_to_base<
												std::istream
											>(
												fcppt::make_unique_ptr<
													io_istream
												>(
													std::move(
														_buffer
													)
												)
											);
									}
								);
						}
					);
			}
		);
}
