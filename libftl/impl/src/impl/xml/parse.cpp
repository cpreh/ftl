#include <libftl/error.hpp>
#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/as_struct.hpp>
#include <fcppt/parse/char_set.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/parse/grammar.hpp>
#include <fcppt/parse/grammar_parse_stream.hpp>
#include <fcppt/parse/literal.hpp>
#include <fcppt/parse/make_convert.hpp>
#include <fcppt/parse/make_lexeme.hpp>
#include <fcppt/parse/make_recursive.hpp>
#include <fcppt/parse/make_with_location.hpp>
#include <fcppt/parse/string.hpp>
#include <fcppt/parse/operators/alternative.hpp>
#include <fcppt/parse/operators/complement.hpp>
#include <fcppt/parse/operators/not.hpp>
#include <fcppt/parse/operators/optional.hpp>
#include <fcppt/parse/operators/repetition.hpp>
#include <fcppt/parse/operators/repetition_plus.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/parse/skipper/char_set.hpp>
#include <fcppt/parse/skipper/comment.hpp>
#include <fcppt/parse/skipper/string.hpp>
#include <fcppt/parse/skipper/operators/alternative.hpp>
#include <fcppt/parse/skipper/operators/repetition.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{

auto make_skipper()
{
  return *(
      fcppt::parse::skipper::comment{
          fcppt::parse::skipper::string{"<!--"}, fcppt::parse::skipper::string{"-->"}} |
      fcppt::parse::skipper::char_set{' ', '\n', '\r', '\t'});
}

class grammar final
    : public fcppt::parse::
          grammar<libftl::impl::xml::document, char, decltype(make_skipper())>
{
  FCPPT_NONMOVABLE(grammar);

public:
  grammar()
      : grammar::grammar_base{fcppt::make_cref(this->document_), make_skipper()},
        quoted_string_{grammar::make_base(fcppt::parse::make_lexeme(
            fcppt::parse::literal{'"'} >> *~fcppt::parse::char_set{'"'} >>
            fcppt::parse::literal{'"'}))},
        string_{grammar::make_base(fcppt::parse::make_lexeme(*~fcppt::parse::char_set{'<'}))},
        inner_node_{grammar::make_base(fcppt::parse::as_struct<libftl::impl::xml::inner_node>(
            fcppt::make_cref(this->node_content_) >> fcppt::parse::string{"</"} >>
            +~fcppt::parse::char_set{'>'} >> fcppt::parse::literal{'>'}))},
        node_content_{grammar::make_base(
            fcppt::make_cref(this->node_vector_) | fcppt::make_cref(this->string_))},
        node_{grammar::make_base(
            fcppt::parse::as_struct<libftl::impl::xml::node>(fcppt::parse::make_with_location(
                fcppt::parse::literal{'<'} >> !fcppt::parse::literal{'/'} >>
                fcppt::parse::make_lexeme(+~fcppt::parse::char_set{' ', '/', '>'}) >>
                fcppt::make_cref(this->attribute_vector_) >>
                fcppt::parse::make_convert(
                    fcppt::parse::string{"/>"} |
                        -(fcppt::parse::literal{'>'} >> fcppt::make_cref(this->inner_node_)),
                    [](fcppt::variant::object<
                        fcppt::unit,
                        fcppt::optional::object<libftl::impl::xml::inner_node>> &&_value)
                    {
                      return fcppt::variant::match(
                          std::move(_value),
                          [](fcppt::unit)
                          { return fcppt::optional::object<libftl::impl::xml::inner_node>(); },
                          [](fcppt::optional::object<libftl::impl::xml::inner_node> &&_inner)
                          { return std::move(_inner); });
                    }))))},
        attribute_{grammar::make_base(
            fcppt::parse::as_struct<libftl::impl::xml::attribute>(fcppt::parse::make_with_location(
                (+~fcppt::parse::char_set{'>', '='} >> fcppt::parse::literal{'='}) >>
                fcppt::make_cref(this->quoted_string_))))},
        attribute_vector_{grammar::make_base(*fcppt::make_cref(this->attribute_))},
        node_vector_{
            grammar::make_base(+fcppt::parse::make_recursive(fcppt::make_cref(this->node_)))},
        version_{grammar::make_base(fcppt::parse::as_struct<libftl::impl::xml::document::version>(
            fcppt::parse::string{"<?xml"} >> fcppt::parse::string{"version="} >>
            fcppt::make_cref(this->quoted_string_) >> fcppt::parse::string{"encoding="} >>
            fcppt::make_cref(this->quoted_string_) >> fcppt::parse::string{"?>"}))},
        document_{grammar::make_base(fcppt::parse::as_struct<libftl::impl::xml::document>(
            -fcppt::make_cref(this->version_) >> fcppt::make_cref(this->node_vector_)))}
  {
  }

  ~grammar() = default;

private:
  base_type<std::string> quoted_string_;

  base_type<std::string> string_;

  base_type<libftl::impl::xml::inner_node> inner_node_;

  base_type<libftl::impl::xml::inner_node_content> node_content_;

  base_type<libftl::impl::xml::node> node_;

  base_type<libftl::impl::xml::attribute> attribute_;

  base_type<std::vector<libftl::impl::xml::attribute>> attribute_vector_;

  base_type<libftl::impl::xml::node_vector> node_vector_;

  base_type<libftl::impl::xml::document::version> version_;

  base_type<libftl::impl::xml::document> document_;
};

}

fcppt::either::object<libftl::error, libftl::impl::xml::document>
libftl::impl::xml::parse(std::istream &_stream)
{
  return fcppt::either::map_failure(
      fcppt::parse::grammar_parse_stream(_stream, grammar{}),
      [](fcppt::parse::error<char> &&_error)
      {
        return libftl::error{
            FCPPT_TEXT("Parsing failed: ") + fcppt::from_std_string(std::move(_error.get()))};
      });
}
