/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  rbr::settings v ( "surname"_kw = std::string{"john"}
                  , "value"_kw = 3.f
                  , "aligned"_fl
                  , "transparent"_fl
                  );

  std::cout << v << "\n";

  auto unaligned = drop("aligned"_fl, v);
  auto unamed    = drop("surname"_kw, v);

  std::cout << unaligned << "\n";
  std::cout << unamed << "\n";
}
