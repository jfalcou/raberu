/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
#include <raberu.hpp>
#include <iostream>

using namespace rbr::literals;

template<typename T>
struct is_big : std::bool_constant<(sizeof(T) > 2)> {};

inline constexpr auto large_value = rbr::keyword<is_big>("large"_id);

int main()
{
  std::cout << rbr::settings( large_value = 9.6 );
}
