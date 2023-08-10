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

  auto defaults = rbr::settings("name"_kw = std::string{"Jane Doe"}, "value"_kw = 42.69f, "modal"_fl);
  auto opts     = rbr::settings("value"_kw = 956.7f, "similar"_fl);

  auto merged = rbr::merge(opts, defaults);

  std::cout << merged["modal"_fl] << "\n";
  std::cout << merged["name"_kw] << "\n";
  std::cout << merged["similar"_fl] << "\n";
  std::cout << merged["value"_kw] << "\n";
}
