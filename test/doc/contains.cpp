/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu.hpp>
#include <iostream>

using namespace rbr::literals;

template<rbr::concepts::settings S>
void check_contains( S const& s)
{
  if constexpr( S::contains( "value"_kw ) )
    std::cout << "Correct settings: " << s["value"_kw] << '\n';
  else
    std::cout << "Incorrect settings\n";
}

int main()
{
  check_contains( rbr::settings("value"_kw = 9  ) );
  check_contains( rbr::settings("malus"_kw = 3.5) );
  check_contains( rbr::settings("malus"_kw = 6.5, "value"_kw = 17) );
}
