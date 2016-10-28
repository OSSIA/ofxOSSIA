#pragma once
#include <ossia/network/domain/domain_base.hpp>
namespace ossia
{
namespace net
{
/**
 * Applying a domain without caring about the underlying type
 */
struct generic_clamp
{
  const net::domain_base<ossia::value>& domain;

  ossia::value operator()(bounding_mode b, const ossia::value& v) const;
  ossia::value operator()(bounding_mode b, ossia::value&& v) const;

  // TODO should we have the same optimization for Vec?
  // This will clamp the Tuple component by component with the given value.
  value operator()(bounding_mode b, const Tuple& val) const;
  value operator()(bounding_mode b, Tuple&& val) const;
};

}
}
