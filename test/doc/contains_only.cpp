/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
#include <raberu.hpp>
#include <iostream>

using namespace rbr::literals;

template<rbr::concepts::settings S>
void check_contains_only( S const& )
{
  if constexpr( S::contains_only( "value"_kw, "active"_fl ) )
    std::cout << "Correct settings\n";
  else
    std::cout << "Incorrect settings\n";
}

int main()
{
  check_contains_only( rbr::settings("value"_kw = 9) );
  check_contains_only( rbr::settings("active"_fl)    );
  check_contains_only( rbr::settings("malus"_kw = 6.5, "value"_kw = 17) );
  check_contains_only( rbr::settings("active"_fl, "value"_kw = 17) );
  check_contains_only( rbr::settings("active"_fl, "value"_kw = 17, "other"_kw = false) );
}
