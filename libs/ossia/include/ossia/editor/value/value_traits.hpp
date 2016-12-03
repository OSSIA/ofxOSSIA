#pragma once
#include <ossia/editor/value/value.hpp>

namespace ossia
{

template <typename T>
struct value_trait;

template <>
struct value_trait<ossia::Impulse>
{
  using ossia_type = ossia::Impulse;
  using value_type = void;
  static const constexpr auto ossia_enum = val_type::IMPULSE;
  static const constexpr bool is_numeric = false;
  static const constexpr bool is_array = false;
};

template <>
struct value_trait<int32_t>
{
  using ossia_type = int32_t;
  using value_type = int;
  static const constexpr auto ossia_enum = val_type::INT;
  static const constexpr bool is_numeric = true;
  static const constexpr bool is_array = false;
};

template <>
struct value_trait<float>
{
  using ossia_type = float;
  using value_type = float;
  static const constexpr auto ossia_enum = val_type::FLOAT;
  static const constexpr bool is_numeric = true;
  static const constexpr bool is_array = false;
};

template <>
struct value_trait<bool>
{
  using ossia_type = bool;
  using value_type = bool;
  static const constexpr auto ossia_enum = val_type::BOOL;
  static const constexpr bool is_numeric = true;
  static const constexpr bool is_array = false;
};

template <>
struct value_trait<char>
{
  using ossia_type = char;
  using value_type = char;
  static const constexpr auto ossia_enum = val_type::CHAR;
  static const constexpr bool is_numeric = true;
  static const constexpr bool is_array = false;
};

template <>
struct value_trait<std::string>
{
  using ossia_type = std::string;
  using value_type = std::string;
  static const constexpr auto ossia_enum = val_type::STRING;
  static const constexpr bool is_numeric = false;
  static const constexpr bool is_array = false;
};

template <>
struct value_trait<std::vector<ossia::value>>
{
  using ossia_type = std::vector<ossia::value>;
  using value_type = std::vector<value>;
  static const constexpr auto ossia_enum = val_type::TUPLE;
  static const constexpr bool is_numeric = false;
  static const constexpr bool is_array = true;
};

template <>
struct value_trait<ossia::Destination>
{
  using ossia_type = ossia::Destination;
  using value_type = ossia::net::address_base*;
  static const constexpr auto ossia_enum = val_type::DESTINATION;
  static const constexpr bool is_numeric = false;
  static const constexpr bool is_array = false;
};

template <>
struct value_trait<ossia::Vec2f>
{
  using ossia_type = ossia::Vec2f;
  using value_type = std::array<float, 2>;
  static const constexpr auto ossia_enum = val_type::VEC2F;
  static const constexpr bool is_numeric = false;
  static const constexpr bool is_array = true;
};

template <>
struct value_trait<ossia::Vec3f>
{
  using ossia_type = ossia::Vec3f;
  using value_type = std::array<float, 3>;
  static const constexpr auto ossia_enum = val_type::VEC3F;
  static const constexpr bool is_numeric = false;
  static const constexpr bool is_array = true;
};

template <>
struct value_trait<ossia::Vec4f>
{
  using ossia_type = ossia::Vec4f;
  using value_type = std::array<float, 4>;
  static const constexpr auto ossia_enum = val_type::VEC4F;
  static const constexpr bool is_numeric = false;
  static const constexpr bool is_array = true;
};

template <>
struct value_trait<ossia::value>
{
  using ossia_type = ossia::value;
  using value_type = ossia::value;
  static const constexpr bool is_numeric = false;
  static const constexpr bool is_array = false;
};

/**
 * @brief is_numeric True if the value is of a numeric type
 * (int, bool, float, char...)
 */
OSSIA_EXPORT
bool is_numeric(const ossia::value& v);

/**
 * @brief is_numeric True if the value is of an array type
 * (tuple, vec...)
 */
OSSIA_EXPORT
bool is_array(const ossia::value& v);

}
