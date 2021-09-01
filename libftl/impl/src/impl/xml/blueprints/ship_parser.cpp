/*
fcppt::unique_ptr<
    libftl::impl::xml::typed::base<libftl::xml::blueprints::ship, libftl::impl::xml::node>>
libftl::impl::xml::blueprints::ship_parser()
{
  namespace typed = libftl::impl::xml::typed;
  namespace labels = libftl::xml::labels;
  namespace blueprints = libftl::impl::xml::blueprints;
  using typed::required;

  return typed::make_derived(typed::node{
      "shipBlueprint",
      typed::attribute_set{fcppt::record::make(
          labels::name{} = typed::attribute<std::string, required::yes>{"name"},
          labels::layout{} = typed::attribute<std::string, required::yes>{"layout"},
          labels::img{} = typed::attribute<std::string, required::yes>{"img"})},
      typed::inner_node{typed::node_set{fcppt::record::make(
          labels::class_{} = typed::make_node_member<required::yes>(
              "class", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::name{} = typed::make_node_member<required::yes>(
              "name", typed::attribute_set{fcppt::record::make()}, typed::content<std::string>{}),
          labels::system_list{} = typed::make_node_member<required::yes>(
              "systemList",
              typed::attribute_set{fcppt::record::make()},
              typed::inner_node{typed::node_set{
                  labels::pilot{} = blueprints::system_element_parser("pilot"),
                  labels::doors{} = blueprints::system_element_parser("doors"),
                  labels::sensors{} = blueprints::system_element_parser("sensors"),
                  labels::medbay{} = blueprints::system_element_parser("medbay"),
                  labels::oxygen{} = blueprints::system_element_parser("oxygen"),
                  labels::shields{} = blueprints::system_element_parser("shields"),
                  labels::engines{} = blueprints::system_element_parser("engines"),
                  labels::weapons{} = blueprints::system_element_parser("weapons"),
                  labels::drones{} = blueprints::system_element_parser("drones"),
                  labels::teleporter{} = blueprints::system_element_parser("teleporter"),
                  labels::cloaking{} = blueprints::system_element_parser("cloaking"),
                  labels::clonebay{} = blueprints::system_element_parser("clonebay"),
                  labels::battery{} = blueprints::system_element_parser("battery"),
                  labels::mind{} = blueprints::system_element_parser("mind"),
                  labels::hacking{} = blueprints::system_element_parser("hacking")}}),
          labels::weapon_slots{} = typed::make_node_member<required::yes>(
              "weaponSlots",
              typed::attribute_set{fcppt::record::make()},
              typed::content<unsigned>{}),
          labels::drone_slots{} = typed::make_node_member<required::yes>(
              "droneSlots",
              typed::attribute_set{fcppt::record::make()},
              typed::content<unsigned>{}),
          labels::weapon_list{} = typed::make_node_member<required::yes>(
              "weaponList",
              typed::attribute_set{fcppt::record::make(
                  labels::count{} = typed::attribute<unsigned, required::yes>{"count"},
                  labels::missiles{} = typed::attribute<unsigned, required::yes>{"missiles"})},
              typed::inner_node{typed::node_list{typed::node{
                  "weapon",
                  typed::attribute_set{fcppt::record::make(
                      labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
                  typed::empty{}}}}),
          labels::drone_list{} = typed::make_node_member<required::yes>(
              "doneList",
              typed::attribute_set{fcppt::record::make(
                  labels::count{} = typed::attribute<unsigned, required::yes>{"count"},
                  labels::drones{} = typed::attribute<unsigned, required::yes>{"drones"})},
              typed::inner_node{typed::node_list{typed::node{
                  "drone",
                  typed::attribute_set{fcppt::record::make(
                      labels::name{} = typed::attribute<std::string, required::yes>{"name"})},
                  typed::empty{}}}}),
          labels::max_power{} = typed::make_node_member<required::yes>(
              "maxPower",
              typed::attribute_set{fcppt::record::make(
                  labels::amount{} = typed::attribute<unsigned, required::yes>{"amount"})},
              typed::empty{}),
          labels::boarding_ai{} = typed::make_node_member<required::no>(
              "boardingAI",
              typed::attribute_set{fcppt::record::make()},
              typed::content<std::string>{}))}}});
}*/
