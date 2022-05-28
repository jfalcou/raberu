/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  int i = 77;

  auto values = rbr::settings("size"_kw = 75ULL, "transparent"_fl);

  std::cout << rbr::fetch ( "transparent"_fl, values)                                 << "\n";
  std::cout << rbr::fetch ( "size"_kw, "size"_kw = 75ULL, "transparent"_fl)           << "\n";
  std::cout << rbr::fetch ( "value"_kw | 13.37, "size"_kw = 75ULL, "transparent"_fl)  << "\n";
  std::cout << rbr::fetch ( "modal"_fl | rbr::call([&]() { return i++; })
                          , "size"_kw = 75ULL, "transparent"_fl
                          )   << "\n\n";

  std::cout << "i = " << i << "\n";
}
