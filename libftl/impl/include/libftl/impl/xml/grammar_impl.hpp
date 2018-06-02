#ifndef LIBFTL_IMPL_XML_GRAMMAR_IMPL_HPP_INCLUDED
#define LIBFTL_IMPL_XML_GRAMMAR_IMPL_HPP_INCLUDED

#include <libftl/impl/xml/encoding.hpp>
#include <libftl/impl/xml/grammar_decl.hpp>
#include <libftl/impl/xml/types/adapt_attribute.hpp>
#include <libftl/impl/xml/types/adapt_inner_node.hpp>
#include <libftl/impl/xml/types/adapt_leaf_node.hpp>
#include <sge/parse/install_error_handler.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
//#include <boost/spirit/include/qi_action.hpp>
/*
#include <boost/spirit/include/qi_attr.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_directive.hpp>
#include <boost/spirit/include/qi_lexeme.hpp>
#include <boost/spirit/include/qi_nonterminal.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_string.hpp>*/
#include <boost/spirit/include/qi.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename In
>
libftl::impl::xml::grammar<
	In
>::grammar()
:
	grammar::base_type(
		document_
	),
	quoted_string_(),
	string_(),
	inner_node_(),
	leaf_node_(),
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

	namespace
	encoding
	=
	libftl::impl::xml::encoding;

	quoted_string_ %=
		boost::spirit::qi::lexeme[
			qi::lit('"')
			>
			*encoding::char_
			>
			qi::lit('"')
		];

	quoted_string_.name(
		"quoted string"
	);

	string_ %=
		boost::spirit::qi::lexeme[
			*(
				~encoding::char_('<')
			)
		];

	string_.name(
		"string"
	);

	inner_node_ %=
		+(
			~encoding::char_(" >")
		)
		>>
		attribute_vector_
		>>
		qi::lit('>')
		>>
		node_content_
		>>
		qi::lit("</")
		>>
		+(
			~encoding::char_('>')
		)
		>>
		qi::lit('>');

	inner_node_.name(
		"inner node"
	);

	leaf_node_ %=
		+(
			encoding::char_
			-
			(
				qi::lit(' ')
				|
				qi::lit("/>")
			)
		)
		>>
		attribute_vector_
		>>
		qi::lit("/>");

	leaf_node_.name(
		"leaf node"
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
		(
			leaf_node_
			|
			inner_node_
		);

	node_.name(
		"node"
	);

	attribute_ %=
		(
			+(
				~encoding::char_(">=")
			)
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

template<
	typename In
>
libftl::impl::xml::grammar<
	In
>::~grammar()
{
}

template<
	typename In
>
sge::parse::optional_error_string const &
libftl::impl::xml::grammar<
	In
>::error_string() const
{
	return
		error_string_;
}

#endif
