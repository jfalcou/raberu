/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu/raberu.hpp>
#include <iostream>

using namespace rbr::literals;

inline constexpr auto value = "value"_kw;
inline constexpr auto line = "line"_kw;
inline constexpr auto file = "file"_kw;

int main()
{
  std::cout << file (value = 45.5, line = 158, file = 'x') << '\n';
  std::cout << line (value = 45.5, line = 158, file = 'x') << '\n';
  std::cout << value(value = 45.5, line = 158, file = 'x') << '\n';
}
