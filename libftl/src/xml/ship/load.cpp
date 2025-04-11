#include <libftl/impl/xml/load.hpp>
#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_set.hpp>
#include <libftl/impl/xml/typed/content.hpp>
#include <libftl/impl/xml/typed/empty.hpp>
#include <libftl/impl/xml/typed/inner_node.hpp>
#include <libftl/impl/xml/typed/make_node_member.hpp>
#include <libftl/impl/xml/typed/node.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_list.hpp>
#include <libftl/impl/xml/typed/node_set.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/xml/labels/angular.hpp>
#include <libftl/xml/labels/cloak.hpp>
#include <libftl/xml/labels/direction.hpp>
#include <libftl/xml/labels/explosion.hpp>
#include <libftl/xml/labels/floor.hpp>
#include <libftl/xml/labels/gib.hpp>
#include <libftl/xml/labels/gib1.hpp>
#include <libftl/xml/labels/gib2.hpp>
#include <libftl/xml/labels/gib3.hpp>
#include <libftl/xml/labels/gib4.hpp>
#include <libftl/xml/labels/gib5.hpp>
#include <libftl/xml/labels/gib6.hpp>
#include <libftl/xml/labels/glow_offset.hpp>
#include <libftl/xml/labels/h.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/max.hpp>
#include <libftl/xml/labels/min.hpp>
#include <libftl/xml/labels/mirror.hpp>
#include <libftl/xml/labels/offsets.hpp>
#include <libftl/xml/labels/rotate.hpp>
#include <libftl/xml/labels/slide.hpp>
#include <libftl/xml/labels/velocity.hpp>
#include <libftl/xml/labels/w.hpp>
#include <libftl/xml/labels/weapon_mounts.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <libftl/xml/ship/gib.hpp>
#include <libftl/xml/ship/load.hpp>
#include <libftl/xml/ship/result.hpp>
#include <libftl/xml/ship/slide.hpp>
#include <libftl/xml/ship/slide_input.hpp> // IWYU pragma: keep
#include <fcppt/deref_reference.hpp> // IWYU pragma: keep
#include <fcppt/make_cref.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::xml::error, libftl::xml::ship::result>
libftl::xml::ship::load(std::istream &_input)
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  typed::node_set const gib_parser{fcppt::record::make(
      labels::velocity{} = typed::make_node_member<required::yes>(
          "velocity",
          typed::attribute_set{fcppt::record::make(
              labels::min{} = typed::attribute<float, required::yes>{"min"},
              labels::max{} = typed::attribute<float, required::yes>{"max"})},
          typed::empty{}),
      labels::direction{} = typed::make_node_member<required::yes>(
          "direction",
          typed::attribute_set{fcppt::record::make(
              labels::min{} = typed::attribute<int, required::yes>{"min"},
              labels::max{} = typed::attribute<int, required::yes>{"max"})},
          typed::empty{}),
      labels::angular{} = typed::make_node_member<required::yes>(
          "angular",
          typed::attribute_set{fcppt::record::make(
              labels::min{} = typed::attribute<float, required::yes>{"min"},
              labels::max{} = typed::attribute<float, required::yes>{"max"})},
          typed::empty{}),
      labels::glow_offset{} = typed::make_node_member<required::no>(
          "glowOffset",
          typed::attribute_set{fcppt::record::make(
              labels::x{} = typed::attribute<int, required::yes>{"x"},
              labels::y{} = typed::attribute<int, required::yes>{"y"})},
          typed::empty{}),
      labels::x{} = typed::make_node_member<required::yes>(
          "x", typed::attribute_set{fcppt::record::make()}, typed::content<int>{}),
      labels::y{} = typed::make_node_member<required::yes>(
          "y", typed::attribute_set{fcppt::record::make()}, typed::content<int>{}))};

  static_assert(std::is_same_v<
                libftl::impl::xml::typed::result_type<decltype(gib_parser)>,
                libftl::xml::ship::gib::content_type>);

  typed::node_set const parser{fcppt::record::make(
      labels::img{} = typed::make_node_member<required::yes>(
          "img",
          typed::attribute_set{fcppt::record::make(
              labels::x{} = typed::attribute<int, required::yes>{"x"},
              labels::y{} = typed::attribute<int, required::yes>{"y"},
              labels::w{} = typed::attribute<unsigned, required::yes>{"w"},
              labels::h{} = typed::attribute<unsigned, required::yes>{"h"})},
          typed::empty{}),
      labels::glow_offset{} = typed::make_node_member<required::no>(
          "glowOffset",
          typed::attribute_set{fcppt::record::make(
              labels::x{} = typed::attribute<int, required::yes>{"x"},
              labels::y{} = typed::attribute<int, required::yes>{"y"})},
          typed::empty{}),
      labels::offsets{} = typed::make_node_member<required::no>(
          "offsets",
          typed::attribute_set{fcppt::record::make()},
          typed::inner_node{typed::node_set{fcppt::record::make(
              labels::cloak{} = typed::make_node_member<required::no>(
                  "cloak",
                  typed::attribute_set{fcppt::record::make(
                      labels::x{} = typed::attribute<int, required::yes>{"x"},
                      labels::y{} = typed::attribute<int, required::yes>{"y"})},
                  typed::empty{}),
              labels::floor{} = typed::make_node_member<required::no>(
                  "floor",
                  typed::attribute_set{fcppt::record::make(
                      labels::x{} = typed::attribute<int, required::yes>{"x"},
                      labels::y{} = typed::attribute<int, required::yes>{"y"})},
                  typed::empty{}))}}),
      labels::weapon_mounts{} = typed::make_node_member<required::yes>(
          "weaponMounts",
          typed::attribute_set{fcppt::record::make()},
          typed::inner_node{typed::node_list{typed::node{
              "mount",
              typed::node_content{
                  typed::attribute_set{fcppt::record::make(
                      labels::x{} = typed::attribute<int, required::yes>{"x"},
                      labels::y{} = typed::attribute<int, required::yes>{"y"},
                      labels::rotate{} = typed::attribute<bool, required::yes>{"rotate"},
                      labels::mirror{} = typed::attribute<bool, required::yes>{"mirror"},
                      labels::gib{} = typed::attribute<unsigned, required::yes>{"gib"},
                      labels::slide{} =
                          typed::attribute<libftl::xml::ship::slide, required::yes>{"slide"})},
                  typed::empty{}}}}}),
      labels::explosion{} = typed::make_node_member<required::yes>(
          "explosion",
          typed::attribute_set{fcppt::record::make()},
          typed::inner_node{typed::node_set{fcppt::record::make(
              labels::gib1{} = typed::make_node_member<required::yes>(
                  "gib1",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{fcppt::make_cref(gib_parser)}),
              labels::gib2{} = typed::make_node_member<required::yes>(
                  "gib2",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{fcppt::make_cref(gib_parser)}),
              labels::gib3{} = typed::make_node_member<required::yes>(
                  "gib3",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{fcppt::make_cref(gib_parser)}),
              labels::gib4{} = typed::make_node_member<required::yes>(
                  "gib4",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{fcppt::make_cref(gib_parser)}),
              labels::gib5{} = typed::make_node_member<required::no>(
                  "gib5",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{fcppt::make_cref(gib_parser)}),
              labels::gib6{} = typed::make_node_member<required::no>(
                  "gib6",
                  typed::attribute_set{fcppt::record::make()},
                  typed::inner_node{fcppt::make_cref(gib_parser)}))}}))};

  return libftl::impl::xml::load(_input, parser);
}
