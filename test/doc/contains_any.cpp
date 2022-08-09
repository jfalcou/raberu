/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu.hpp>
#include <iostream>

using namespace rbr::literals;

template<rbr::concepts::settings S>
void check_contains_any( S const& )
{
  if constexpr( S::contains_any( "value"_kw, "active"_fl ) )
    std::cout << "Correct settings\n";
  else
    std::cout << "Incorrect settings\n";
}

int main()
{
  check_contains_any( rbr::settings("value"_kw = 9  ) );
  check_contains_any( rbr::settings("malus"_kw = 3.5) );
  check_contains_any( rbr::settings("malus"_kw = 6.5, "value"_kw = 17) );
  check_contains_any( rbr::settings("active"_fl, "value"_kw = 17) );
}
