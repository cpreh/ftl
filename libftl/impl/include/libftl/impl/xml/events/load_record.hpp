#ifndef LIBFTL_IMPL_XML_EVENTS_LOAD_RECORD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_EVENTS_LOAD_RECORD_HPP_INCLUDED

#include <libftl/impl/xml/typed/attribute.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/labels/load.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::events
{

// This is a workaround for gcc-14.
inline fcppt::record::object<fcppt::record::element<
    libftl::xml::labels::load,
    libftl::impl::xml::typed::attribute<std::string, libftl::impl::xml::typed::required::yes>>>
load_record()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  using typed::required;

  return fcppt::record::make(labels::load{} = typed::attribute<std::string, required::yes>{"load"});
}

}

#endif
