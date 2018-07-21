#ifndef LIBFTL_IMPL_XML_DOCUMENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_DOCUMENT_HPP_INCLUDED

#include <libftl/impl/spirit/variant_impl.hpp>
#include <libftl/impl/xml/document_fwd.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/variant/variadic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{

struct document
{
	struct node;

	typedef
	std::vector<
		node
	>
	node_vector;

	typedef
	fcppt::variant::variadic<
		node_vector,
		std::string
	>
	node_content;

	typedef
	libftl::impl::spirit::variant<
		node_content
	>
	node_content_wrapper;

	struct inner_node
	{
		node_content_wrapper content_;

		std::string closing_tag_;
	};

	typedef
	fcppt::optional::object<
		inner_node
	>
	optional_inner_node;

	struct attribute
	{
		std::string name_;

		std::string value_;
	};

	typedef
	std::vector<
		attribute
	>
	attribute_vector;

	struct node
	{
		std::string opening_tag_;

		attribute_vector attributes_;

		optional_inner_node content_;
	};

	document();

	explicit
	document(
		node_vector const &
	);

	node_vector nodes_;
};

}
}
}

#endif
