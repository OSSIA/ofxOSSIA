#pragma once

#include <ossia/network/base/device.hpp>
#include <ossia/network/generic/generic_node.hpp>
#include <boost/utility/string_view.hpp>
namespace ossia
{
namespace net
{
class OSSIA_EXPORT generic_device final : public ossia::net::device_base,
                                          public generic_node
{
private:
public:
  generic_device() = delete;
  generic_device(const generic_device&) = delete;
  generic_device(generic_device&&) = delete;
  generic_device& operator=(const generic_device&) = delete;
  generic_device& operator=(generic_device&&) = delete;

  generic_device(
      std::unique_ptr<ossia::net::protocol_base> protocol_base,
      std::string name);

  const ossia::net::node_base& getRootNode() const override
  {
    return *this;
  }
  ossia::net::node_base& getRootNode() override
  {
    return *this;
  }

  using generic_node::getName;
  using generic_node::setName;

  ~generic_device();
};

// address : format /a/b/c
OSSIA_EXPORT node_base*
find_node(node_base& dev, boost::string_view address_base);
OSSIA_EXPORT generic_node&
find_or_create_node(generic_device& dev, boost::string_view address_base);
}
}
