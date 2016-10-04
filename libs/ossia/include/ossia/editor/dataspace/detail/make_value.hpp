#pragma once
#include <ossia/editor/dataspace/dataspace.hpp>
#include <ossia/editor/value/value_conversion.hpp>

namespace ossia
{

template<typename U, typename = void>
struct make_value_helper
{

  template<typename T>
  ossia::value_with_unit operator()(const T& t)
  {
    // TODO maybe return first value for tuple or vecNf ?
    throw std::runtime_error("mismatching value type and unit");
    return strong_value<U>{};
  }

  ossia::value_with_unit operator()(Int t)
  {
    return strong_value<U>{t.value};
  }
  ossia::value_with_unit operator()(Float t)
  {
    return strong_value<U>{t.value};
  }
  ossia::value_with_unit operator()(Char t)
  {
    return strong_value<U>{t.value};
  }
  ossia::value_with_unit operator()(Bool t)
  {
    return strong_value<U>{t.value};
  }
};

template<typename U>
struct make_value_helper<U, std::enable_if_t<std::is_same<typename U::value_type, ossia::Vec2f>::value>>
{

  template<typename T>
  ossia::value_with_unit operator()(const T& t)
  {
    throw std::runtime_error("mismatching value type and unit");
    return {};
  }

  ossia::value_with_unit operator()(const ossia::Tuple& t)
  {
    return strong_value<U>{ossia::convert<ossia::Vec2f>(t)};
  }

  ossia::value_with_unit operator()(ossia::Vec2f t)
  {
    return strong_value<U>{t};
  }
};

template<typename U>
struct make_value_helper<U, std::enable_if_t<std::is_same<typename U::value_type, ossia::Vec3f>::value>>
{

  template<typename T>
  ossia::value_with_unit operator()(const T& t)
  {
    throw std::runtime_error("mismatching value type and unit");
    return {};
  }

  ossia::value_with_unit operator()(const ossia::Tuple& t)
  {
    return strong_value<U>{ossia::convert<ossia::Vec3f>(t)};
  }

  ossia::value_with_unit operator()(ossia::Vec3f t)
  {
    return strong_value<U>{t};
  }
};


template<typename U>
struct make_value_helper<U, std::enable_if_t<std::is_same<typename U::value_type, ossia::Vec4f>::value>>
{

  template<typename T>
  ossia::value_with_unit operator()(const T& t)
  {
    throw std::runtime_error("mismatching value type and unit");
    return {};
  }

  ossia::value_with_unit operator()(const ossia::Tuple& t)
  {
    return strong_value<U>{ossia::convert<ossia::Vec4f>(t)};
  }

  ossia::value_with_unit operator()(ossia::Vec4f t)
  {
    return strong_value<U>{t};
  }
};

struct make_value_with_unit_visitor
{
  template<typename Val, typename Unit>
  ossia::value_with_unit operator()(const Val& v, const Unit& u)
  {
    return make_value_helper<Unit>{}(v);
  }
};

}
