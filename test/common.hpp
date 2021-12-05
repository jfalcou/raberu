//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <raberu.hpp>
#include <array>
#include <string>

using namespace rbr::literals;

template<bool B> using bool_ = std::bool_constant<B>;

using point = std::array<int, 3>;

struct foo
{
  int    value = 42;
  friend std::ostream& operator<<(std::ostream& os, foo f) { return os << f.value; }
};

struct bar
{
  double value = 4.2;
  friend std::ostream& operator<<(std::ostream& os, bar b) { return os << b.value; }
};

struct small_type
{
  template<typename T> struct apply : std::bool_constant<(sizeof(T) < 4)> {};
};

inline constexpr auto custom_ = ::rbr::keyword("custom"_id);
inline constexpr auto coord_  = "coord"_kw;

inline constexpr auto value_  = ::rbr::keyword<float>("value"_id);
inline constexpr auto name_   = ::rbr::keyword<std::string>("name"_id);

inline constexpr auto factor_ = ::rbr::keyword<small_type>("factor"_id);

inline constexpr auto is_transparent_ = ::rbr::flag("is_transparent"_id);
inline constexpr auto is_modal_       = "is_modal"_fl;

struct is_integral_constant
{
  template<typename T>      struct apply                               : std::false_type {};
  template<typename T, T N> struct apply<std::integral_constant<T,N>>  : std::true_type {};
};

struct unrolling : rbr::checked_keyword<unrolling, is_integral_constant>
{
  template<int N>
  constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
  {
    return rbr::option<unrolling,std::integral_constant<int,N>>{};
  }

  std::ostream& name(std::ostream& os) const { return os << "Unroll Factor: "; }
};

template<int N> inline constexpr auto unroll = (unrolling{} = std::integral_constant<int,N>{});
