#pragma once
#include <algorithm>
#include <type_traits>
#include <iterator>
#include <array>
#include <iostream>
#include <tuple>
#include <utility>

#include <boost/utility/string_view.hpp>

/**
 * \file algorithms.hpp
 *
 * This header contains various range-style functions that mimic std::algorithm functions.
 * This won't be necessary anymore when ranges are introduced in C++20 (hopefully).
 */
namespace ossia
{
template <typename Vector>
using iterator_t = typename std::remove_reference<Vector>::type::iterator;

template <typename Vector, typename Value>
auto find(Vector&& v, const Value& val)
{
  return std::find(std::begin(v), std::end(v), val);
}

template <typename Vector, typename Fun>
auto find_if(Vector&& v, Fun fun)
{
  return std::find_if(std::begin(v), std::end(v), fun);
}

template<typename Vector, typename Value>
auto* ptr_find(Vector&& v, const Value& val)
{
    auto it = std::find(std::begin(v), std::end(v), val);
    return it != std::end(v) ? &*it : nullptr;
}

template<typename Vector, typename Fun>
auto* ptr_find_if(Vector&& v, Fun fun)
{
    auto it = std::find_if(std::begin(v), std::end(v), fun);
    return it != std::end(v) ? &*it : nullptr;
}

template <typename Vector, typename Value>
bool contains(Vector&& v, const Value& val)
{
  return find(v, val) != std::end(v);
}

template <typename Vector, typename Value>
void remove_one(Vector&& v, const Value& val)
{
  auto it = find(v, val);
  if (it != v.end())
  {
    v.erase(it);
  }
}

template <typename Vector, typename Fun>
bool any_of(Vector&& v, Fun fun)
{
  return std::any_of(std::begin(v), std::end(v), fun);
}

template<typename Vector, typename Fun>
auto all_of(Vector&& v, Fun fun)
{
    return std::all_of(std::begin(v), std::end(v), fun);
}

template <typename Vector, typename Fun>
bool none_of(Vector&& v, Fun fun)
{
  return std::none_of(std::begin(v), std::end(v), fun);
}

template <typename Vector, typename Fun>
auto remove_if(Vector&& v, Fun fun)
{
  return std::remove_if(std::begin(v), std::end(v), fun);
}

template<typename Vector, typename Fun>
auto count_if(Vector&& v, Fun fun)
{
    return std::count_if(std::begin(v), std::end(v), fun);
}

template<typename Vector, typename Fun>
auto max_element(Vector&& v, Fun fun)
{
    return std::max_element(std::begin(v), std::end(v), fun);
}

template<typename Vector, typename Fun>
auto sort(Vector&& v, Fun fun)
{
    return std::sort(std::begin(v), std::end(v), fun);
}

template<typename Vector, typename OutputIterator, typename Fun>
auto transform(Vector&& v, OutputIterator it, Fun f)
{
    return std::transform(v.begin(), v.end(), it, f);
}

template<typename Vector1, typename Vector2>
void copy(const Vector1& source, Vector2& destination)
{
    destination.reserve(destination.size() + source.size());
    std::copy(source.begin(), source.end(), std::back_inserter(destination));
}

template<typename Vector1, typename Vector2, typename Pred>
void copy_if(const Vector1& source, Vector2& destination, Pred predicate)
{
    std::copy_if(source.begin(), source.end(), std::back_inserter(destination), predicate);
}

// http://stackoverflow.com/a/26902803/1495627
template<class F, class...Ts, std::size_t...Is>
void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func, std::index_sequence<Is...>)
{
    using expander = int[];
    (void)expander { 0, ((void)func(std::get<Is>(tuple)), 0)... };
}

template<class F, class...Ts>
void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func)
{
    for_each_in_tuple(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
}

// See also https://gist.github.com/klmr/2775736
template <typename... Args>
constexpr std::array<boost::string_view, sizeof...(Args)>
  make_string_array(Args&&... args)
{
  return std::array<boost::string_view, sizeof...(Args)>{
        boost::string_view{args, sizeof(args) - 1}...
  };
}

template<std::size_t N>
constexpr boost::string_view make_string_view(const char (&str)[N]) noexcept
{ return {str, N - 1}; }
}
