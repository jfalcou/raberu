/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu/raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  int i = 77;
  auto values = rbr::settings("size"_kw = 75ULL, "transparent"_fl);

  std::cout << values["size"_kw]                                      << "\n";
  std::cout << values["transparent"_fl]                               << "\n";
  std::cout << values["value"_kw | 13.37]                             << "\n";
  std::cout << values["value"_kw | [&](auto const&) { return ++i; }]  << "\n\n";

  std::cout << "i = " << i << "\n";
}
