/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
