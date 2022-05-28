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
  auto kws  = rbr::keywords<std::tuple>(opts);

  std::apply( []<typename... T>(T const&...)
              {
                ((std::cout << typename T::id_type{} << "\n"),...);
              }
            , kws
            );
}
