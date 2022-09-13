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

  auto s1 = rbr::settings("opt1"_kw = 3, "opt2"_kw = 22, "yes"_fl);
  auto s2 = rbr::settings("opt1"_kw = 7.8, "yes"_kw = 8.8888, "opt2"_kw = 789.987);
  auto s3 = rbr::settings("opt1"_kw = 7.8, "yes"_fl, "opt3"_kw = 789.987);

  std::cout << std::boolalpha << rbr::is_equivalent_v<decltype(s2), decltype(s3)> << "\n";
  std::cout << std::boolalpha << rbr::is_equivalent_v<decltype(s3), decltype(s2)> << "\n";
  std::cout << std::boolalpha << rbr::is_equivalent_v<decltype(s2), decltype(s1)> << "\n";
  std::cout << std::boolalpha << rbr::is_equivalent_v<decltype(s1), decltype(s2)> << "\n";
  std::cout << std::boolalpha << rbr::is_equivalent_v<decltype(s1), decltype(s1)> << "\n";
  std::cout << std::boolalpha << rbr::is_equivalent_v<decltype(s2), decltype(s2)> << "\n";
}
