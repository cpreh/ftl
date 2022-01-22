#ifndef LIBFTL_XML_BLUEPRINTS_RESULT_OUTPUT_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_RESULT_OUTPUT_HPP_INCLUDED

#include <libftl/xml/blueprints/result.hpp>
#include <fcppt/output.hpp>
#include <fcppt/string_literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
template <typename Ch, typename Traits>
std::basic_ostream<Ch, Traits> &
operator<<(std::basic_ostream<Ch, Traits> &_stream, libftl::xml::blueprints::result const &_result)
{
  return _stream << FCPPT_STRING_LITERAL(Ch, "( ") << FCPPT_STRING_LITERAL(Ch, "Augmentations: ")
                 << fcppt::output(_result.augmentations) << FCPPT_STRING_LITERAL(Ch, "Crews: ")
                 << fcppt::output(_result.crews) << FCPPT_STRING_LITERAL(Ch, "Drones: ")
                 << fcppt::output(_result.drones) << FCPPT_STRING_LITERAL(Ch, "Items: ")
                 << fcppt::output(_result.items) << FCPPT_STRING_LITERAL(Ch, "Lists: ")
                 << fcppt::output(_result.lists) << FCPPT_STRING_LITERAL(Ch, "Ships: ")
                 << fcppt::output(_result.ships) << FCPPT_STRING_LITERAL(Ch, "Systems: ")
                 << fcppt::output(_result.systems) << FCPPT_STRING_LITERAL(Ch, "Weapons: ")
                 << fcppt::output(_result.weapons) << FCPPT_STRING_LITERAL(Ch, " )");
}
}

#endif
