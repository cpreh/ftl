#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTES_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTES_HPP_INCLUDED

/*
namespace libftl::impl::xml::typed
{
template<typename Label, typename Type, char const *Name>
struct attribute
{
   static constexpr char const *const name = Name;
};

template<typename Elements>
struct attributes
{
  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(std::vector<libftl::impl::xml::attribute> const &_attributes) const
  {
    using map_type = std::unordered_map<std::string,fcppt::tuple::object<bool,std::string>>;

    fcppt::either::object<libftl::error,map_type> attributes{
      fcppt::algorithm::fold_break(_attributes,map_type{},[](fcppt::either::object<libftl::error,map_type> &&_map, libftl::impl::xml::attribute const &_attrib)
      {
        return
          fcppt::either::bind(
            std::move(_map),
            [](map_type &&_inner_map)
            {
              return
            });
      })
    };

      fcppt::record::init<result_type>(
        []<typename Label, typename Type>(fcppt::record::element<Label, Type> const &_element)
        {
          using attribute_type
          =
          fcppt::mpl::list::at<
            Elements,
            fcppt::mpl::list::index_of_if<
               Elements,
               label_is_same<Label>>>;
        });
  }
};
}*/
#endif
