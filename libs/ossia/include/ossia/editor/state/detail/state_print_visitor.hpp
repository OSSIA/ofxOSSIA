#pragma once
#include <ossia/editor/state/state_element.hpp>
#include <ossia/editor/value/value.hpp>
#include <ossia/network/base/address.hpp>
#include <ossia/network/base/node.hpp>
#include <ossia/editor/dataspace/dataspace_visitors.hpp>
#include <iostream>
#include <string>

namespace ossia
{
struct state_print_visitor
{
  std::ostream& out;
  std::string padding;

  void operator()(const state& s)
  {
    out << padding << "state {\n";
    padding.push_back(' ');
    for (auto& sub : s)
      eggs::variants::apply(*this, sub);
    padding.pop_back();
    out << "}\n";
  }

  void operator()(const custom_state& e)
  {
    out << padding << "custom\n";
  }

  void operator()(const message& m)
  {
    out << padding << "message: "
        << ossia::to_pretty_string(m.destination) << " => "
        << ossia::value_to_pretty_string(m.value);

    if(m.unit)
    {
      out << " " << ossia::get_pretty_unit_text(m.unit);
    }

    out << "\n";
  }

  void operator()(const piecewise_message& m)
  {
    out << padding << "message: "
        << ossia::net::address_string_from_node(m.address.get()) << " => "
        << ossia::value_to_pretty_string(m.value) << "\n";
  }

  template<std::size_t N>
  void operator()(const piecewise_vec_message<N>& m)
  {
    // TODO
  }

  void operator()()
  {
    out << "no state\n";
  }
};
}
