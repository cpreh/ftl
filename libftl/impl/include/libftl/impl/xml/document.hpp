#ifndef LIBFTL_IMPL_XML_DOCUMENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_DOCUMENT_HPP_INCLUDED

#include <libftl/impl/xml/document_fwd.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/variant/object.hpp>
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

	using
	node_vector
	=
	std::vector<
		node
	>;

	using
	node_content
	=
	fcppt::variant::object<
		node_vector,
		std::string
	>;

	struct inner_node
	{
		node_content content_;

		std::string closing_tag_;
	};

	using
	optional_inner_node
	=
	fcppt::optional::object<
		inner_node
	>;

	struct attribute
	{
		std::string name_;

		std::string value_;
	};

	using
	attribute_vector
	=
	std::vector<
		attribute
	>;

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

	using
	optional_version
	=
	fcppt::optional::object<
		version
	>;

	optional_version version_;

	node_vector nodes_;
};

}
}
}

#endif
