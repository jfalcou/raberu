/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu/raberu.hpp>
#include <iostream>

using namespace rbr::literals;

inline constexpr auto char_value  = rbr::keyword("character"_id, rbr::only<char>);

int main()
{
  std::cout << rbr::settings( char_value  = 'Z' ) << "\n";
}
