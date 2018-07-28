#include <libftl/error.hpp>
#include <libftl/archive/entry_output.hpp>
#include <libftl/archive/extract.hpp>
#include <libftl/archive/file.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/remove_comments.hpp>
#include <sge/parse/error_string.hpp>
#include <sge/parse/install_error_handler.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/identity.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/include/qi_alternative.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_kleene.hpp>
#include <boost/spirit/include/qi_lexeme.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_not_predicate.hpp>
#include <boost/spirit/include/qi_optional.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_plus.hpp>
#include <boost/spirit/include/qi_rule.hpp>
#include <boost/spirit/include/qi_sequence.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


BOOST_FUSION_ADAPT_STRUCT(
	libftl::impl::xml::document::attribute,
	(std::string, name_),
	(std::string, value_)
)

BOOST_FUSION_ADAPT_STRUCT(
	libftl::impl::xml::document::inner_node,
	(libftl::impl::xml::document::node_content_wrapper, content_),
	(std::string, closing_tag_)
)

BOOST_FUSION_ADAPT_STRUCT(
	libftl::impl::xml::document::node,
	(std::string, opening_tag_),
	(libftl::impl::xml::document::attribute_vector, attributes_)
	(libftl::impl::xml::document::optional_inner_node, content_)
)

namespace
{

namespace
encoding
=
boost::spirit::standard;

typedef
encoding::space_type
space_type;

template<
	typename In
>
class grammar final
:
public
	boost::spirit::qi::grammar<
		In,
		libftl::impl::xml::document(),
		space_type
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar()
	:
		grammar::base_type(
			document_
		),
		quoted_string_(),
		string_(),
		inner_node_(),
		node_content_(),
		node_(),
		attribute_(),
		attribute_vector_(),
		node_vector_(),
		document_(),
		error_string_()
	{
		namespace
		qi = boost::spirit::qi;

		quoted_string_ %=
			boost::spirit::qi::lexeme[
				qi::lit('"')
				>
				*~encoding::char_('"')
				>
				qi::lit('"')
			];

		quoted_string_.name(
			"quoted string"
		);

		string_ %=
			boost::spirit::qi::lexeme[
				*~encoding::char_('<')
			];

		string_.name(
			"string"
		);

		inner_node_ %=
			node_content_
			>>
			qi::lit("</")
			>>
			+~encoding::char_('>')
			>>
			qi::lit('>');

		inner_node_.name(
			"inner node"
		);

		node_content_ %=
			node_vector_
			|
			string_;

		node_content_.name(
			"node content"
		);

		node_ %=
			qi::lit('<')
			>>
			!qi::lit('/')
			>>
			boost::spirit::qi::lexeme[
				+~encoding::char_(" />")
			]
			>>
			attribute_vector_
			>>
			(
				qi::lit("/>")
				|
				-(
					qi::lit(">")
					>>
					inner_node_
				)
			);

		node_.name(
			"node"
		);

		attribute_ %=
			(
				+~encoding::char_(">=")
				>>
				qi::lit('=')
			)
			>>
			quoted_string_;

		attribute_.name(
			"attribute"
		);

		attribute_vector_ %=
			*attribute_;

		attribute_vector_.name(
			"attribute vector"
		);

		node_vector_ %=
			+node_;

		node_vector_.name(
			"node vector"
		);

		document_ %=
			node_vector_;

		document_.name(
			"document"
		);

		sge::parse::install_error_handler(
			fcppt::make_ref(
				node_vector_
			),
			fcppt::make_ref(
				error_string_
			)
		);
	}

	~grammar()
	{
	}

	sge::parse::optional_error_string const &
	error_string() const
	{
		return
			error_string_;
	}
private:
	boost::spirit::qi::rule<
		In,
		std::string(),
		space_type
	>
	quoted_string_;

	boost::spirit::qi::rule<
		In,
		std::string(),
		space_type
	>
	string_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::document::inner_node(),
		space_type
	>
	inner_node_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::document::node_content_wrapper(),
		space_type
	>
	node_content_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::document::node(),
		space_type
	>
	node_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::document::attribute(),
		space_type
	>
	attribute_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::document::attribute_vector(),
		space_type
	>
	attribute_vector_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::document::node_vector(),
		space_type
	>
	node_vector_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::document(),
		space_type
	>
	document_;

	sge::parse::optional_error_string error_string_;
};

fcppt::either::object<
	libftl::error,
	libftl::impl::xml::document
>
parse_string(
	std::string const &_input
)
{
	grammar<
		std::string::const_iterator
	>
	parser{};

	std::string::const_iterator begin{
		_input.begin()
	};

	libftl::impl::xml::document result{};

	boost::spirit::qi::phrase_parse(
		begin,
		_input.end(),
		parser,
		encoding::space,
		result
	);

	return
		fcppt::optional::maybe(
			parser.error_string(),
			[
				begin,
				&result,
				&_input
			]{
				return
					begin
					==
					_input.end()
					?
						fcppt::either::make_success<
							libftl::error
						>(
							std::move(
								result
							)
						)
					:
						fcppt::either::make_failure<
							libftl::impl::xml::document
						>(
							libftl::error{
								fcppt::from_std_string(
									std::string{
										begin,
										_input.end()
									}
								)
							}
						)
					;
			},
			[](
				sge::parse::error_string const &_error
			)
			{
				return
					fcppt::either::make_failure<
						libftl::impl::xml::document
					>(
						libftl::error{
							_error.get()
						}
					);
			}
		);
}

}

fcppt::either::object<
	libftl::error,
	libftl::impl::xml::document
>
libftl::impl::xml::parse(
	libftl::archive::file const &_file
)
{
	return
		fcppt::either::bind(
			fcppt::either::from_optional(
				libftl::archive::extract(
					_file
				),
				[
					&_file
				]{
					return
						libftl::error{
							FCPPT_TEXT("Failed to read ")
							+
							fcppt::output_to_fcppt_string(
								_file.entry_
							)
						};
				}
			),
			[](
				fcppt::io::buffer &&_buffer
			)
			{
				return
					parse_string(
						libftl::impl::xml::remove_comments(
							fcppt::algorithm::map<
								std::string
							>(
								_buffer,
								fcppt::identity{}
							)
						)
					);
			}
		);
}
