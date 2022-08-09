/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu.hpp>
#include <iostream>
#include <string>

using namespace rbr::literals;

inline constexpr auto name = rbr::keyword("name"_id);

int main()
{
  std::cout << rbr::settings( name = std::string{"Jane Doe"} );
}
