#include <libftl/error.hpp>
#include <libftl/impl/xml/document_fwd.hpp>
#include <libftl/impl/xml/output.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/xml/clean.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, std::string> libftl::xml::clean(std::istream &_stream)
{
  return fcppt::either::map(
      libftl::impl::xml::parse(_stream),
      [](libftl::impl::xml::document const &_document)
      {
        std::ostringstream stream{};

        libftl::impl::xml::output(stream, _document);

        return stream.str();
      });
}
