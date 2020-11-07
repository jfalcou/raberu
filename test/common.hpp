//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <raberu.hpp>
#include <string>
#include <array>

template<bool B> using bool_ =  std::bool_constant<B>;

struct foo { int    value = 42;   };
struct bar { double value = 4.2;  };

using point = std::array<int,3>;

inline constexpr auto custom_  = ::rbr::keyword<struct custom_tag>;
inline constexpr auto coord_   = ::rbr::keyword<struct coord_tag>;

namespace rbr
{
  template<> struct tag<foo> : tag<struct custom_tag> {};
  template<> struct tag<bar> : tag<struct custom_tag> {};
}

inline constexpr auto value_  = ::rbr::keyword<float>;
inline constexpr auto name_   = ::rbr::keyword<std::string>;
inline constexpr auto factor_ = ::rbr::keyword<int>;
inline constexpr auto ref_    = ::rbr::keyword<double>;

