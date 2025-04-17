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
  constexpr auto aligned = "aligned"_fl;
  constexpr auto transparent = "transparent"_fl;

  rbr::settings v ( "surname"_kw = std::string{"john"}
                    , "value"_kw = 3.f
                    , aligned
                    , transparent
                    );

  std::cout << v << "\n";

  auto unaligned = drop(aligned, v);
  auto unamed    = drop("surname"_kw, v);

  std::cout << unaligned << "\n";
  std::cout << unamed << "\n";
}
