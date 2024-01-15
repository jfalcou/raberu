/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu/raberu.hpp>
#include <iostream>

using namespace rbr::literals;

inline constexpr auto modal = rbr::flag("modal window"_id);

int main()
{
  std::cout << rbr::settings( modal ) << "\n";
}
