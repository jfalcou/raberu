/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
#include <raberu.hpp>
#include <iostream>

using namespace rbr::literals;

inline constexpr auto modal = rbr::flag("modal window"_id);

int main()
{
  std::cout << rbr::settings( modal );
}
