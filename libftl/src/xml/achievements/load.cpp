#include <libftl/impl/xml/load.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/achievements/load.hpp>
#include <libftl/xml/achievements/result.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/xml/labels/desc.hpp>
#include <libftl/xml/labels/id.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/multi_difficulty.hpp>
#include <libftl/xml/labels/name.hpp>
#include <libftl/xml/labels/ship.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::xml::error, libftl::xml::achievements::result>
libftl::xml::achievements::load(std::istream &_input)
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  typed::node_list const parser{typed::node{
      "achievement",
      typed::node_content{
          typed::attribute_set{fcppt::record::make(
              labels::id{} = typed::attribute<std::string, required::yes>{"id"})},
          typed::inner_node{typed::node_set{fcppt::record::make(
              labels::name{} = typed::make_node_member<required::yes>(
                  "name",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::desc{} = typed::make_node_member<required::yes>(
                  "desc",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::img{} = typed::make_node_member<required::yes>(
                  "img",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::ship{} = typed::make_node_member<required::no>(
                  "ship",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<std::string>{}),
              labels::multi_difficulty{} = typed::make_node_member<required::no>(
                  "multiDifficulty",
                  typed::attribute_set{fcppt::record::make()},
                  typed::content<unsigned>{}))}}}}};

  return libftl::impl::xml::load(_input, parser);
}
