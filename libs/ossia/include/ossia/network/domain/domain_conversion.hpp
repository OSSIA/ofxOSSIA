#pragma once
#include <ossia/network/domain/domain.hpp>

namespace ossia
{
namespace net
{
template <typename U>
struct domain_conversion
{

  template <typename T>
  OSSIA_INLINE domain operator()(const T&)
  {
    return U{};
  }

  domain operator()(const domain_base<Int>& t)
  {
    U f;
    if (t.min)
      f.min = t.min.get();
    if (t.max)
      f.max = t.max.get();
    if (!t.values.empty())
      for (auto val : t.values)
        f.values.insert(val);
    return f;
  }

  domain operator()(const domain_base<Float>& t)
  {
    U f;
    if (t.min)
      f.min = t.min.get();
    if (t.max)
      f.max = t.max.get();
    if (!t.values.empty())
      for (auto val : t.values)
        f.values.insert(val);
    return f;
  }

  domain operator()(const domain_base<Bool>& t)
  {
    U f;
    if (t.min)
      f.min = t.min.get();
    if (t.max)
      f.max = t.max.get();
    if (!t.values.empty())
      for (auto val : t.values)
        f.values.insert(val);
    return f;
  }

  domain operator()(const domain_base<Char>& t)
  {
    U f;
    if (t.min)
      f.min = t.min.get();
    if (t.max)
      f.max = t.max.get();
    if (!t.values.empty())
      for (auto val : t.values)
        f.values.insert(val);
    return f;
  }
};

template <>
struct domain_conversion<domain_base<Impulse>>
{
  template <typename T>
  OSSIA_INLINE domain operator()(const T&)
  {
    return domain_base<Impulse>{};
  }
};

template <>
struct domain_conversion<domain_base<Tuple>>
{
  OSSIA_INLINE domain operator()(const domain_base<Tuple>& src)
  {
    return src;
  }

  template <typename T>
  OSSIA_INLINE domain operator()(const T&)
  {
    return domain_base<Tuple>();
  }
};

template <std::size_t N>
struct domain_conversion<domain_base<Vec<float, N>>>
{
  OSSIA_INLINE domain operator()(const domain_base<Vec<float, N>>& src)
  {
    return src;
  }
  domain_base<Vec<float, N>> tuple_func(const domain_base<Tuple>& t)
  {
      auto to_vec = [] (const Tuple& sub)
      {
          Vec<float, N> vec;
          for (std::size_t i = 0; i < N; i++)
              vec[i] = ossia::convert<float>(sub[i]);
          return vec;
      };

      domain_base<Vec<float, N>> dom;
      if(t.min)
      {
          const Tuple& min = t.min.get();
          if(min.size() == N)
          {
              dom.min = to_vec(min);
          }
      }
      if(t.max)
      {
          const Tuple& max = t.max.get();
          if(max.size() == N)
          {
              dom.max = to_vec(max);
          }
      }

      for(auto& val : t.values)
      {
          if(val.size() == N)
          {
              dom.values.insert(to_vec(val));
          }
      }

      return dom;
  }

  OSSIA_INLINE domain operator()(const domain_base<Tuple>& t)
  {
      return tuple_func(t);
  }

  template <typename T>
  OSSIA_INLINE domain operator()(const T&)
  {
    return domain_base<Vec<float, N>>();
  }
};

template <>
struct domain_conversion<domain_base<String>>
{
  OSSIA_INLINE domain operator()(const domain_base<String>& src)
  {
    return src;
  }

  template <typename T>
  OSSIA_INLINE domain operator()(const T&)
  {
    return domain_base<String>();
  }
};

// TODO handle the ossia::value case

inline domain convert_domain(const domain& dom, ossia::val_type newtype)
{
  switch (newtype)
  {
    case val_type::IMPULSE:
      return eggs::variants::apply(
          domain_conversion<domain_base<Impulse>>{}, dom);
    case val_type::INT:
      return eggs::variants::apply(
          domain_conversion<domain_base<Int>>{}, dom);
    case val_type::FLOAT:
      return eggs::variants::apply(
          domain_conversion<domain_base<Float>>{}, dom);
    case val_type::BOOL:
      return eggs::variants::apply(
          domain_conversion<domain_base<Bool>>{}, dom);
    case val_type::CHAR:
      return eggs::variants::apply(
          domain_conversion<domain_base<Char>>{}, dom);
    case val_type::STRING:
      return eggs::variants::apply(
          domain_conversion<domain_base<String>>{}, dom);
    case val_type::TUPLE:
      return eggs::variants::apply(
          domain_conversion<domain_base<Tuple>>{}, dom);
    case val_type::VEC2F:
      return eggs::variants::apply(
          domain_conversion<domain_base<Vec2f>>{}, dom);
    case val_type::VEC3F:
      return eggs::variants::apply(
          domain_conversion<domain_base<Vec3f>>{}, dom);
    case val_type::VEC4F:
      return eggs::variants::apply(
          domain_conversion<domain_base<Vec4f>>{}, dom);
    case val_type::DESTINATION:
    default:
      return domain{};
  }
}

}
}
