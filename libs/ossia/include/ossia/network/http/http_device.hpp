#pragma once

#include <ossia/network/base/device.hpp>
#include <ossia/network/http/http_node.hpp>

namespace ossia
{
namespace net
{
class http_protocol;
class OSSIA_EXPORT http_device final :
    public ossia::net::device_base,
    public http_node
{
public:
  http_device() = delete;
  http_device(const http_device&) = delete;
  http_device(http_device&&) = delete;
  http_device& operator=(const http_device&) = delete;
  http_device& operator=(http_device&&) = delete;

  http_device(
      std::unique_ptr<ossia::net::http_protocol> protocol_base,
      std::string name);

  const ossia::net::node_base& getRootNode() const override
  {
    return *this;
  }
  ossia::net::node_base& getRootNode() override
  {
    return *this;
  }

  using http_node::getName;
  using http_node::setName;

  ~http_device();
};

}
}
