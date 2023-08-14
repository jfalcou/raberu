/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu/raberu.hpp>
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
