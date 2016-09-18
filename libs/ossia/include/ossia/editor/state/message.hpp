#pragma once
#include <memory>

#include <ossia/editor/value/value.hpp>
#include <ossia_export.h>
#include <utility>

namespace ossia
{
namespace net
{
class address_base;
}
/**
 * @brief The message struct
 *
 * A message allows to store something to send to the network.
 * For instance : a:/b 234
 *
 * \see \ref state_element
 */
struct OSSIA_EXPORT message
{
  ossia::Destination destination;
  ossia::value value;

  void launch() const;

  friend bool operator==(const message& lhs, const message& rhs)
  {
    return lhs.destination == rhs.destination
           && lhs.value == rhs.value;
  }

  friend bool operator!=(const message& lhs, const message& rhs)
  {
    return lhs.destination != rhs.destination
           || lhs.value != rhs.value;
  }
};

struct OSSIA_EXPORT piecewise_message
{
  std::reference_wrapper<ossia::net::address_base> address;
  Tuple value;

  void launch() const;

  friend bool operator==(const piecewise_message& lhs, const piecewise_message& rhs)
  {
    return &lhs.address.get() == &rhs.address.get()
           && lhs.value == rhs.value;
  }

  friend bool operator!=(const piecewise_message& lhs, const piecewise_message& rhs)
  {
    return &lhs.address.get() != &rhs.address.get()
           || lhs.value != rhs.value;
  }
};
}
