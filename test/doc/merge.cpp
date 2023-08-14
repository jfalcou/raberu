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

  constexpr auto modal = "modal"_fl;
  constexpr auto similar = "similar"_fl;
  auto defaults = rbr::settings("name"_kw = std::string{"Jane Doe"}, "value"_kw = 42.69f, modal);
  auto opts     = rbr::settings("value"_kw = 956.7f, similar);

  auto merged = rbr::merge(opts, defaults);

  std::cout << merged[modal] << "\n";
  std::cout << merged["name"_kw] << "\n";
  std::cout << merged[similar] << "\n";
  std::cout << merged["value"_kw] << "\n";
}
