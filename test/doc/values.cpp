/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
#include <raberu.hpp>
#include <iostream>
#include <tuple>

int main()
{
  using namespace rbr::literals;

  auto opts = rbr::settings("size"_kw = 75ULL, "modal"_fl, "value"_kw = 13.37);
  auto vs = rbr::values<std::tuple>(opts);

  std::apply([](auto const&... e) {  ((std::cout << e << "\n"),...);  }, vs);
}
