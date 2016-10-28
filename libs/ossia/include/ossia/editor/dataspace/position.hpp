#pragma once
#include <ossia/editor/dataspace/dataspace_base.hpp>
#include <eggs/variant.hpp>

namespace ossia
{
struct cartesian_3d_u;
struct position_dataspace;
template<typename Impl>
struct position_unit
{
  using is_unit = std::true_type;
  using is_multidimensional = std::true_type;
  using dataspace_type = position_dataspace;
  using neutral_unit = cartesian_3d_u;
  using concrete_type = Impl;
};

struct cartesian_3d_u :
    public position_unit<cartesian_3d_u>
{
  static OSSIA_DECL_RELAXED_CONSTEXPR auto text()
  { return ossia::make_string_array("cart3D", "xyz"); }
  static OSSIA_DECL_RELAXED_CONSTEXPR auto array_parameters()
  { return ossia::make_string_view("xyz"); }

  using value_type = Vec3f;
  static OSSIA_DECL_RELAXED_CONSTEXPR strong_value<neutral_unit> to_neutral(strong_value<concrete_type> self)
  {
    return self;
  }

  static OSSIA_DECL_RELAXED_CONSTEXPR value_type from_neutral(strong_value<neutral_unit> self)
  {
    return self.dataspace_value;
  }
};

struct cartesian_2d_u :
    public position_unit<cartesian_2d_u>
{
  static OSSIA_DECL_RELAXED_CONSTEXPR auto text()
  { return ossia::make_string_array("cart2D", "xy"); }
  static OSSIA_DECL_RELAXED_CONSTEXPR auto array_parameters()
  { return ossia::make_string_view("xy"); }
  using value_type = Vec2f;
  static strong_value<neutral_unit> to_neutral(strong_value<concrete_type> self)
  {
    return {self.dataspace_value[0], self.dataspace_value[1], 0.f};
  }

  static value_type from_neutral(strong_value<neutral_unit> self)
  {
    return {self.dataspace_value[0], self.dataspace_value[1]};
  }
};

// aed
struct spherical_u :
    public position_unit<spherical_u>
{
  static OSSIA_DECL_RELAXED_CONSTEXPR auto text()
  { return ossia::make_string_array("spherical", "aed"); }
  static OSSIA_DECL_RELAXED_CONSTEXPR auto array_parameters()
  { return ossia::make_string_view("aed"); }
  using value_type = Vec3f;
  static strong_value<neutral_unit> to_neutral(strong_value<concrete_type> self)
  {
    const auto a = self.dataspace_value[0] * deg_to_rad;
    const auto e = self.dataspace_value[1] * deg_to_rad;
    const auto d = self.dataspace_value[2];

    const auto temp = std::cos(e) * d;

    return strong_value<neutral_unit>{
      (float)(std::sin(a) * temp),
      (float)(std::cos(a) * temp),
      (float)(std::sin(e) * d)
    };
  }

  static value_type from_neutral(strong_value<neutral_unit> self)
  {
    const auto x = self.dataspace_value[0];
    const auto y = self.dataspace_value[1];
    const auto z = self.dataspace_value[2];

    const auto temp = std::pow(x, 2.) + std::pow(y, 2.);

    return {
          (float)(std::atan2(x, y) * rad_to_deg),
          (float)(std::atan2(z, std::sqrt(temp)) * rad_to_deg),
          (float)(std::sqrt(temp + std::pow(z, 2.)))
        };
  }
};

// ad
struct polar_u :
    public position_unit<polar_u>
{
  static OSSIA_DECL_RELAXED_CONSTEXPR auto text()
  { return ossia::make_string_array("polar", "ad"); }
  static OSSIA_DECL_RELAXED_CONSTEXPR auto array_parameters()
  { return ossia::make_string_view("ad"); }
  using value_type = Vec2f;
  static strong_value<neutral_unit> to_neutral(strong_value<concrete_type> self)
  {
    const auto a = self.dataspace_value[0] * deg_to_rad;
    const auto d = self.dataspace_value[1];

    return {
          (float)(std::sin(a) * d),
          (float)(std::cos(a) * d),
          0.
        };
  }

  static value_type from_neutral(strong_value<neutral_unit> self)
  {
    const auto x = self.dataspace_value[0];
    const auto y = self.dataspace_value[1];

    return {
          (float)(std::atan2(x, y) * rad_to_deg),
          (float)(ossia::norm(x, y))
        };
  }
};

struct opengl_u :
    public position_unit<opengl_u>
{
  static OSSIA_DECL_RELAXED_CONSTEXPR auto text()
  { return ossia::make_string_array("openGL"); }
  static OSSIA_DECL_RELAXED_CONSTEXPR auto array_parameters()
  { return ossia::make_string_view("xyz"); }
  using value_type = Vec3f;
  static strong_value<neutral_unit> to_neutral(strong_value<concrete_type> self)
  {
    return {self.dataspace_value[0], -self.dataspace_value[2], self.dataspace_value[1]};
  }

  static value_type from_neutral(strong_value<neutral_unit> self)
  {
    return {self.dataspace_value[0], self.dataspace_value[2], -self.dataspace_value[1]};
  }
};

struct cylindrical_u :
    public position_unit<cylindrical_u>
{
  static OSSIA_DECL_RELAXED_CONSTEXPR auto text()
  { return ossia::make_string_array("cylindrical", "daz"); }
  static OSSIA_DECL_RELAXED_CONSTEXPR auto array_parameters()
  { return ossia::make_string_view("daz"); }
  using value_type = Vec3f;
  static strong_value<neutral_unit> to_neutral(strong_value<concrete_type> self)
  {
    const auto d = self.dataspace_value[0];
    const auto a = self.dataspace_value[1] * deg_to_rad;
    const auto z = self.dataspace_value[2];

    return {
      (float)(std::sin(a) * d),
      (float)(std::cos(a) * d),
      z
    };
  }

  static value_type from_neutral(strong_value<neutral_unit> self)
  {
    const auto x = self.dataspace_value[0];
    const auto y = self.dataspace_value[1];
    const auto z = self.dataspace_value[2];

    return {
          (float)(ossia::norm(x, y)),
          (float)(std::atan2(x, y) * rad_to_deg),
          z
        };
  }
};



using cartesian_3d = strong_value<cartesian_3d_u>;
using cartesian_2d = strong_value<cartesian_2d_u>;
using spherical = strong_value<spherical_u>;
using polar = strong_value<polar_u>;
using opengl = strong_value<opengl_u>;
using cylindrical = strong_value<cylindrical_u>;

using position_u =
  eggs::variant<cartesian_3d_u, cartesian_2d_u, spherical_u, polar_u, opengl_u, cylindrical_u>;

template<>
struct dataspace_traits<position_u>
{
  static OSSIA_DECL_RELAXED_CONSTEXPR auto text()
  { return ossia::make_string_array("position"); }
};
}
