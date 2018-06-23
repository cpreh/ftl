#ifndef LIBFTL_IMPL_XML_GRAMMAR_DECL_HPP_INCLUDED
#define LIBFTL_IMPL_XML_GRAMMAR_DECL_HPP_INCLUDED

#include <libftl/impl/xml/grammar_fwd.hpp>
#include <libftl/impl/xml/types/attribute_fwd.hpp>
#include <libftl/impl/xml/types/attribute_vector.hpp>
#include <libftl/impl/xml/types/document_fwd.hpp>
#include <libftl/impl/xml/types/inner_node_fwd.hpp>
#include <libftl/impl/xml/types/node_content_wrapper_fwd.hpp>
#include <libftl/impl/xml/types/node_fwd.hpp>
#include <libftl/impl/xml/types/node_vector_fwd.hpp>
#include <libftl/impl/xml/types/space.hpp>
#include <libftl/impl/xml/types/string.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_rule.hpp>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{

template<
	typename In
>
class grammar final
:
public
	boost::spirit::qi::grammar<
		In,
		libftl::impl::xml::types::document(),
		libftl::impl::xml::types::space
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	typedef
	libftl::impl::xml::types::space
	space_type;

	grammar();

	~grammar();

	sge::parse::optional_error_string const &
	error_string() const;
private:
	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::string(),
		space_type
	>
	quoted_string_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::string(),
		space_type
	>
	string_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::inner_node(),
		space_type
	>
	inner_node_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::node_content_wrapper(),
		space_type
	>
	node_content_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::node(),
		space_type
	>
	node_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::attribute(),
		space_type
	>
	attribute_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::attribute_vector(),
		space_type
	>
	attribute_vector_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::node_vector(),
		space_type
	>
	node_vector_;

	boost::spirit::qi::rule<
		In,
		libftl::impl::xml::types::document(),
		space_type
	>
	document_;

	sge::parse::optional_error_string error_string_;
};

}
}
}

#endif
