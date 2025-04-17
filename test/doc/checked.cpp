/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu/raberu.hpp>
#include <iostream>

using namespace rbr::literals;

template<typename T>
struct is_big : std::bool_constant<(sizeof(T) > 2)> {};

inline constexpr auto large_value = rbr::keyword("large"_id, rbr::if_<is_big>);
inline constexpr auto char_value  = rbr::keyword("character"_id, rbr::only<char>);

int main()
{
  std::cout << rbr::settings( large_value = 9.6 ) << "\n";
  std::cout << rbr::settings( char_value  = 'Z' ) << "\n";
}
