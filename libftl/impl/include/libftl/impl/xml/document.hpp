#ifndef LIBFTL_IMPL_XML_DOCUMENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_DOCUMENT_HPP_INCLUDED

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

	struct inner_node
	{
		node_content content_;

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

	struct version
	{
		std::string version_;

		std::string encoding_;
	};

	typedef
	fcppt::optional::object<
		version
	>
	optional_version;

	optional_version version_;

	node_vector nodes_;
};

}
}
}

#endif
