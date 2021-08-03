#ifndef LIBFTL_IMPL_XML_READ_HPP_INCLUDED
#define LIBFTL_IMPL_XML_READ_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/load_function.hpp>
#include <libftl/xml/clean.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_from_std.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/exceptions.hxx>
#include <xsd/cxx/tree/exceptions.hxx>
#include <iosfwd>
#include <sstream>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace impl
{
namespace xml
{
template <typename Result>
fcppt::either::object<libftl::error, fcppt::unique_ptr<Result>>
read(std::istream &_stream, libftl::impl::xml::load_function<Result> const &_function)
{
  return fcppt::either::bind(
      libftl::xml::clean(_stream),
      [&_function](std::string &&_input)
      {
        using result_type = fcppt::either::object<libftl::error, fcppt::unique_ptr<Result>>;

        FCPPT_PP_PUSH_WARNING
        FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
        auto const make_error(
            [](fcppt::string &&_value) -> result_type
            {
              return result_type{
                  libftl::error{FCPPT_TEXT("Failed to read XML document: ") + std::move(_value)}};
            });
        FCPPT_PP_POP_WARNING

        try
        {
          std::istringstream stream{_input};

          return result_type{
              FCPPT_ASSERT_OPTIONAL_ERROR(fcppt::unique_ptr_from_std(_function(stream)))};
        }
        catch (xsd::cxx::tree::expected_element<char> const &_error)
        {
          return make_error(
              FCPPT_TEXT("Expected element ") + fcppt::from_std_string(_error.name()) +
              FCPPT_TEXT(" in namespace ") + fcppt::from_std_string(_error.namespace_()) +
              FCPPT_TEXT(": ") + fcppt::from_std_string(fcppt::output_to_std_string(_error)));
        }
        catch (xsd::cxx::tree::expected_attribute<char> const &_error)
        {
          return make_error(
              FCPPT_TEXT("Expected attribute ") + fcppt::from_std_string(_error.name()) +
              FCPPT_TEXT(" in namespace ") + fcppt::from_std_string(_error.namespace_()) +
              FCPPT_TEXT(": ") + fcppt::from_std_string(fcppt::output_to_std_string(_error)));
        }
        catch (xsd::cxx::tree::exception<char> const &_error)
        {
          return make_error(fcppt::from_std_string(fcppt::output_to_std_string(_error)));
        }
        catch (xsd::cxx::exception const &_error)
        {
          return make_error(fcppt::from_std_string(_error.what()));
        }
      });
}

}
}
}

#endif
