#pragma once
#include <memory>
#include <vector>
#include <ossia/detail/config.hpp>

namespace ossia
{
/**
 * \typedef ptr_container is a shortcut for a vector of shared_ptr.
 *
 * It is not related to boost::ptr_container.
 */
template <typename T>
using ptr_container
    = std::vector<std::shared_ptr<T>, std::allocator<std::shared_ptr<T>>>;
}
