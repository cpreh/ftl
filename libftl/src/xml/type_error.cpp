#include <libftl/impl/xml/location_to_string.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/alternative.hpp>
#include <libftl/xml/errors/attribute_conversion.hpp>
#include <libftl/xml/errors/content_conversion.hpp>
#include <libftl/xml/errors/content_empty.hpp>
#include <libftl/xml/errors/content_inner.hpp>
#include <libftl/xml/errors/excess_nodes.hpp>
#include <libftl/xml/errors/expected_node.hpp>
#include <libftl/xml/errors/inner_empty.hpp>
#include <libftl/xml/errors/invalid_node.hpp>
#include <libftl/xml/errors/mismatched_tags.hpp>
#include <libftl/xml/errors/missing_attribute.hpp>
#include <libftl/xml/errors/missing_node.hpp>
#include <libftl/xml/errors/multi_attribute.hpp>
#include <libftl/xml/errors/node_content.hpp>
#include <libftl/xml/errors/not_empty.hpp>
#include <libftl/xml/errors/unused_attributes.hpp>
#include <libftl/xml/errors/unused_nodes.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_index.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/comparison.hpp> // IWYU pragma: keep
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

bool libftl::xml::type_error::operator==(libftl::xml::type_error const &) const = default;

fcppt::io::ostream &
libftl::xml::operator<<(fcppt::io::ostream &_stream, libftl::xml::type_error const &_type_error)
{
  fcppt::variant::match(
      _type_error.value_,
      [&_stream](libftl::xml::errors::mismatched_tags const &_error)
      {
        _stream << libftl::impl::xml::location_to_string(_error.location_)
                << FCPPT_TEXT("Mismatched tags, expected ") << fcppt::from_std_string(_error.expected_tag_)
                << FCPPT_TEXT(", got ") << fcppt::from_std_string(_error.read_tag_)
                << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::node_content const &_error)
      {
        _stream << libftl::impl::xml::location_to_string(_error.location_) << _error.error_.get();
      },
      [&_stream](libftl::xml::errors::inner_empty const &)
      { _stream << FCPPT_TEXT("Expected an inner node but it is empty."); },
      [&_stream](libftl::xml::errors::expected_node const &_error)
      {
        _stream << FCPPT_TEXT("Expected inner node but content is ")
                << fcppt::from_std_string(_error.content_) << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::unused_nodes const &_error)
      {
        _stream << FCPPT_TEXT("Unparsed nodes ")
                << fcppt::from_std_string(
                       fcppt::output_to_std_string(fcppt::container::output(_error.nodes_)))
                << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::missing_node const &_error)
      {
        _stream << FCPPT_TEXT("Missing node ") << fcppt::from_std_string(_error.name_)
                << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::content_empty const &_error)
      {
        _stream << FCPPT_TEXT("Expected node type ")
                << fcppt::from_std_string(fcppt::type_name_from_index(_error.type_))
                << FCPPT_TEXT(" but node is empty.");
      },
      [&_stream](libftl::xml::errors::content_inner const &_error)
      {
        _stream << FCPPT_TEXT("Expected node type ")
                << fcppt::from_std_string(fcppt::type_name_from_index(_error.type_))
                << FCPPT_TEXT(" but node is an inner node.");
      },
      [&_stream](libftl::xml::errors::content_conversion const &_error)
      {
        _stream << FCPPT_TEXT("Failed to convert \"") << fcppt::from_std_string(_error.content_)
                << FCPPT_TEXT(" to type ")
                << fcppt::from_std_string(fcppt::type_name_from_index(_error.type_))
                << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::excess_nodes const &_error)
      {
        _stream << FCPPT_TEXT("Excess nodes ") << fcppt::from_std_string(_error.name_)
                << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::missing_attribute const &_error)
      {
        _stream << FCPPT_TEXT("Missing attribute ") << fcppt::from_std_string(_error.name_)
                << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::multi_attribute const &_error)
      {
        _stream << FCPPT_TEXT("Attribute ") << fcppt::from_std_string(_error.name_)
                << FCPPT_TEXT(" specified multiple times.");
      },
      [&_stream](libftl::xml::errors::unused_attributes const &_error)
      {
        _stream << FCPPT_TEXT("Unparsed attributes ")
                << fcppt::from_std_string(
                       fcppt::output_to_std_string(fcppt::container::output(_error.attributes_)))
                << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::attribute_conversion const &_error)
      {
        _stream << libftl::impl::xml::location_to_string(_error.location_)
                << FCPPT_TEXT("Failed to convert attribute ")
                << fcppt::from_std_string(_error.name_) << FCPPT_TEXT(" with value ")
                << fcppt::from_std_string(_error.value_) << FCPPT_TEXT(" to type ")
                << fcppt::from_std_string(fcppt::type_name_from_index(_error.type_))
                << FCPPT_TEXT(".");
      },
      [&_stream](libftl::xml::errors::not_empty const &)
      { _stream << FCPPT_TEXT("Expected an empty node."); },
      [&_stream](libftl::xml::errors::alternative const &_error)
      {
        // TODO(philipp): Improve this!
        _stream << fcppt::algorithm::join_strings(
            fcppt::algorithm::map<std::vector<fcppt::string>>(
                _error.errors_,
                [](fcppt::recursive<libftl::xml::type_error> const &_inner)
                { return fcppt::output_to_fcppt_string(_inner.get()); }),
            fcppt::string{FCPPT_TEXT("\n")});
      },
      [&_stream](libftl::xml::errors::invalid_node const &_error)
      {
        _stream << libftl::impl::xml::location_to_string(_error.location_)
                << FCPPT_TEXT("Invalid node \"")
                << fcppt::from_std_string(_error.name_) + FCPPT_TEXT("\".");
      });

  return _stream;
}
