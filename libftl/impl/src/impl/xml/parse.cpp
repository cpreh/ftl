#include <libftl/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/file_to_string.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/remove_comments.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/as_struct.hpp>
#include <fcppt/parse/char_set.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/parse/literal.hpp>
#include <fcppt/parse/make_convert.hpp>
#include <fcppt/parse/make_lexeme.hpp>
#include <fcppt/parse/grammar.hpp>
#include <fcppt/parse/grammar_parse_string.hpp>
#include <fcppt/parse/space_skipper.hpp>
#include <fcppt/parse/string.hpp>
#include <fcppt/parse/operators/alternative.hpp>
#include <fcppt/parse/operators/complement.hpp>
#include <fcppt/parse/operators/not.hpp>
#include <fcppt/parse/operators/optional.hpp>
#include <fcppt/parse/operators/repetition.hpp>
#include <fcppt/parse/operators/repetition_plus.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/variadic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

class grammar final
:
public
	fcppt::parse::grammar<
		libftl::impl::xml::document,
		char,
		decltype(
			fcppt::parse::space_skipper()
		)
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar()
	:
		grammar::grammar_base{
			fcppt::make_cref(
				this->document_
			),
			fcppt::parse::space_skipper()
		},
		quoted_string_{
			this->make_base(
				fcppt::parse::make_lexeme(
					fcppt::parse::literal{'"'}
					>>
					*~fcppt::parse::char_set{'"'}
					>>
					fcppt::parse::literal{'"'}
				)
			)
		},
		string_{
			this->make_base(
				fcppt::parse::make_lexeme(
					*~fcppt::parse::char_set{'<'}
				)
			)
		},
		inner_node_{
			this->make_base(
				fcppt::parse::as_struct<
					libftl::impl::xml::document::inner_node
				>(
					fcppt::make_cref(
						this->node_content_
					)
					>>
					fcppt::parse::string{"</"}
					>>
					+~fcppt::parse::char_set{'>'}
					>>
					fcppt::parse::literal{'>'}
				)
			)
		},
		node_content_{
			this->make_base(
				fcppt::make_cref(
					this->node_vector_
				)
				|
				fcppt::make_cref(
					this->string_
				)
			)
		},
		node_{
			this->make_base(
				fcppt::parse::as_struct<
					libftl::impl::xml::document::node
				>(
					fcppt::parse::literal{'<'}
					>>
					!
					fcppt::parse::literal{'/'}
					>>
					fcppt::parse::make_lexeme(
						+~fcppt::parse::char_set{' ', '/', '>'}
					)
					>>
					fcppt::make_cref(
						this->attribute_vector_
					)
					>>
					fcppt::parse::make_convert(
						fcppt::parse::string{"/>"}
						|
						-(
							fcppt::parse::literal{'>'}
							>>
							fcppt::make_cref(
								this->inner_node_
							)
						),
						[](
							fcppt::variant::variadic<
								fcppt::unit,
								fcppt::optional::object<
									libftl::impl::xml::document::inner_node
								>
							> &&_value
						)
						{
							return
								fcppt::variant::match(
									std::move(_value),
									[](fcppt::unit)
									{
										return
											fcppt::optional::object<
												libftl::impl::xml::document::inner_node
											>();
									},
									[](
										fcppt::optional::object<
											libftl::impl::xml::document::inner_node
										> &&_inner
									)
									{
										return
											std::move(_inner);
									}
								);
						}
					)
				)
			)
		},
		attribute_{
			this->make_base(
				fcppt::parse::as_struct<
					libftl::impl::xml::document::attribute
				>(
					(
						+~fcppt::parse::char_set{'>', '='}
						>>
						fcppt::parse::literal{'='}
					)
					>>
					fcppt::make_cref(
						this->quoted_string_
					)
				)
			)
		},
		attribute_vector_{
			this->make_base(
				*
				fcppt::make_cref(
					this->attribute_
				)
			)
		},
		node_vector_{
			this->make_base(
				+
				fcppt::make_cref(
					this->node_
				)
			)
		},
		version_{
			this->make_base(
				fcppt::parse::as_struct<
					libftl::impl::xml::document::version
				>(
					fcppt::parse::string{"<?xml"}
					>>
					fcppt::parse::string{"version="}
					>>
					fcppt::make_cref(
						this->quoted_string_
					)
					>>
					fcppt::parse::string{"encoding="}
					>>
					fcppt::make_cref(
						this->quoted_string_
					)
					>>
					fcppt::parse::string{"?>"}
				)
			)
		},
		document_{
			this->make_base(
				fcppt::parse::as_struct<
					libftl::impl::xml::document
				>(
					-
					fcppt::make_cref(
						this->version_
					)
					>>
					fcppt::make_cref(
						this->node_vector_
					)
				)
			)
		}
	{
	}

	~grammar()
	{
	}
private:
	base_type<
		std::string
	>
	quoted_string_;

	base_type<
		std::string
	>
	string_;

	base_type<
		libftl::impl::xml::document::inner_node
	>
	inner_node_;

	base_type<
		libftl::impl::xml::document::node_content
	>
	node_content_;

	base_type<
		libftl::impl::xml::document::node
	>
	node_;

	base_type<
		libftl::impl::xml::document::attribute
	>
	attribute_;

	base_type<
		libftl::impl::xml::document::attribute_vector
	>
	attribute_vector_;

	base_type<
		libftl::impl::xml::document::node_vector
	>
	node_vector_;

	base_type<
		libftl::impl::xml::document::version
	>
	version_;

	base_type<
		libftl::impl::xml::document
	>
	document_;
};

fcppt::either::object<
	libftl::error,
	libftl::impl::xml::document
>
parse_string(
	std::string const &_input
)
{
	return
		fcppt::either::map_failure(
			fcppt::parse::grammar_parse_string(
				std::string{
					_input
				},
				grammar{}
			),
			[](
				fcppt::parse::error<
					char
				> &&_error
			)
			{
				return
					libftl::error{
						FCPPT_TEXT("Parsing failed: ")
						+
						fcppt::from_std_string(
							std::move(
								_error.get()
							)
						)
					};
			}
		);
}

}

fcppt::either::object<
	libftl::error,
	libftl::impl::xml::document
>
libftl::impl::xml::parse(
	std::istream &_stream
)
{
	return
		parse_string(
			libftl::impl::xml::remove_comments(
				libftl::impl::xml::file_to_string(
					_stream
				)
			)
		);
}
