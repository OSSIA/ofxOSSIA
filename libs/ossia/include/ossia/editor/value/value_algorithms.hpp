#pragma once
#include <ossia/editor/value/value.hpp>

namespace ossia
{
// SourcePrecedence causes the merging of values
// to occur only if the destination value is null
// (it won't replace an existing value).

template<bool SourcePrecedence = true>
struct value_merger
{
template<typename Value_T>
static void merge_value(ossia::value& dest, Value_T&& src)
{
  if(!dest.valid())
  {
    dest = src;
    return;
  }
  else
  {
    auto dest_tuple_ptr = dest.target<std::vector<ossia::value>>();
    auto src_tuple_ptr = src.template target<std::vector<ossia::value>>();

    if(dest_tuple_ptr && src_tuple_ptr)
    {
      // Merge two tuples
      merge_tuple(*dest_tuple_ptr, *src_tuple_ptr);
      return;
    }
    else if(dest_tuple_ptr)
    {
      // Merge a single value in a tuple
      set_first_value(*dest_tuple_ptr, std::forward<Value_T>(src));
      return;
    }
    else if(src_tuple_ptr)
    {
      // If one of the two values is invalid, we always keep the other
      if(src_tuple_ptr->empty())
      {
        std::vector<ossia::value> t{dest};
        dest = std::move(t);
        return;
      }
      else if(!(*src_tuple_ptr)[0].valid())
      {
        std::vector<ossia::value> t = *src_tuple_ptr;
        t[0] = dest;
        dest = std::move(t);
        return;
      }
      else
      {
        // src overwrites dest
        if(src.valid() && SourcePrecedence)
          dest = std::forward<Value_T>(src);
        return;
      }
    }
    else
    {
      // src overwrites dest
      if(src.valid() && SourcePrecedence)
        dest = std::forward<Value_T>(src);
      return;
    }
  }
}

template<typename Value_T>
static void insert_in_tuple(std::vector<ossia::value>& t, Value_T&& v, const ossia::destination_index& idx)
{
  std::vector<ossia::value>* cur_ptr = &t;
  for(auto it = idx.begin(); it != idx.end(); )
  {
    auto& cur = *cur_ptr;
    std::size_t pos = *it;
    if(cur.size() < pos + 1)
    {
      cur.resize(pos + 1);
    }

    if(++it == idx.end())
    {
      // We're at the deepest index position :
      // we add the value at the current place.
      merge_value(cur[pos], std::forward<Value_T>(v));
    }
    else
    {
      // We go through another depth layer.
      if(auto sub_tuple = cur[pos].target<std::vector<ossia::value>>())
      {
        cur_ptr = sub_tuple;
      }
      else
      {
        // We put the current value at cur[pos] at index 0 of the newly-created sub-tuple.
        std::vector<ossia::value> t{cur[pos]};
        cur[pos] = std::move(t);

        // And use it for the next iteration
        cur_ptr = cur[pos].target<std::vector<ossia::value>>();
      }
    }
  }
}

template<typename Value_T>
static void set_first_value(std::vector<ossia::value>& t, Value_T&& val)
{
  if(t.empty())
  {
    t.push_back(std::forward<Value_T>(val));
  }
  else
  {
    merge_value(t[0], std::forward<Value_T>(val));
  }
}

template<typename Tuple_T>
static void merge_tuple(std::vector<ossia::value>& lhs, Tuple_T&& rhs)
{
  std::size_t n = rhs.size();
  if(lhs.size() < n)
  {
    lhs.resize(n);
  }

  for(std::size_t i = 0u; i < n; i++)
  {
    merge_value(lhs[i], std::forward<Tuple_T>(rhs)[i]);
  }
}
};

namespace detail
{
/**
 * @brief The destination_index_retriever struct
 * Get the value associated with an index in a tuple.
 * If the index cannot be reached, an exception is thrown.
 *
 * @todo testme
 */
struct destination_index_retriever
{
  const ossia::destination_index& index;
  ossia::destination_index::const_iterator it;

  ossia::value operator()(const std::vector<ossia::value>& t)
  {
    if(it == index.end())
    {
      return t;
    }
    else if(t.size() > *it)
    {
      auto& val = t[*it];
      ++it;
      return val.apply(*this);
    }
    else
    {
      return {};
    }
  }

  template<typename T>
  ossia::value operator()(const T& t)
  {
    if(it == index.end())
    {
      return t;
    }
    else
    {
      return {};
    }
  }

  template<std::size_t N>
  ossia::value operator()(const std::array<float, N>& t)
  {
    if(it == index.end())
    {
      return t;
    }
    else if(t.size() > *it)
    {
      if(it + 1 == index.end())
        return float{t[*it]};
    }

    return {};
  }

  ossia::value operator()()
  {
    return {};
  }
};
}
}
