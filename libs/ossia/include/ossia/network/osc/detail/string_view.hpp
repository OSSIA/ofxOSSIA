#pragma once
#include <boost/utility/string_view.hpp>
#include <functional>
#include <oscpack/osc/SmallString.h>
#include <type_traits>
namespace detail
{
using string_view = boost::string_view;
// using string_view = std::string;

template <typename T, typename Enable = void>
struct param_traits
{
};

template <typename T>
struct param_traits<T, std::enable_if_t<std::is_same<T, std::string>::value>>
{
  using type = const T&;
};

template <typename T>
struct param_traits<T,
                    std::enable_if_t<std::is_same<T,
                                                  boost::string_view>::value>>
{
  using type = T;
};

template <typename T>
struct param_traits<T,
                    std::enable_if_t<std::is_same<T, oscpack::small_string>::
                                         value>>
{
  using type = T;
};

template <typename T>
using param_t = typename param_traits<T>::type;
}
