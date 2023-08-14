//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once
#include <raberu/raberu.hpp>
#include <array>
#include <string>
#include <type_traits>

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

template<typename T>
struct small_type : std::bool_constant<(sizeof(T) < 4)> {};

inline constexpr auto custom_ = ::rbr::keyword("custom"_id);
inline constexpr auto coord_  = "coord"_kw;

inline constexpr auto value_  = ::rbr::keyword<float>("value"_id);
inline constexpr auto name_   = ::rbr::keyword<std::string>("name"_id);

inline constexpr auto factor_ = ::rbr::keyword<small_type>("factor"_id);

inline constexpr auto is_transparent_ = ::rbr::flag("is_transparent"_id);
inline constexpr auto is_modal_       = "is_modal"_fl;

struct unrolling : rbr::as_keyword<unrolling>
{
  template<int N>
  constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
  {
    return rbr::option<unrolling,std::integral_constant<int,N>>{};
  }

  std::ostream& display(std::ostream& os, auto v) const { return os << "Unroll Factor: " << v; }
};

template<int N> inline constexpr auto unroll = (unrolling{} = std::integral_constant<int,N>{});
