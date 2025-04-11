#include <libftl/archive/base.hpp>
#include <libftl/archive/open_path_error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/ship/layout/load_xml.hpp>
#include <libftl/ship/layout/load_xml_error.hpp>
#include <libftl/ship/layout/name.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/xml/ship/load.hpp>
#include <libftl/xml/ship/result.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::ship::layout::load_xml_error, libftl::xml::ship::result>
libftl::ship::layout::load_xml(
    libftl::archive::base const &_archive, libftl::ship::layout::name const &_name)
{
  return fcppt::either::bind(
      fcppt::either::map_failure(
          _archive.open(libftl::archive::path{"data"} / (_name.get() + ".xml")),
          [](libftl::archive::open_path_error &&_error)
          {
            return libftl::ship::layout::load_xml_error{
                libftl::ship::layout::load_xml_error::variant{std::move(_error)}};
          }),
      // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
      [](fcppt::unique_ptr<std::istream> &&_stream)
      {
        return fcppt::either::map_failure(
            libftl::xml::ship::load(*_stream),
            [](libftl::xml::error &&_error)
            {
              return libftl::ship::layout::load_xml_error{
                  libftl::ship::layout::load_xml_error::variant{std::move(_error)}};
            });
      });
}
