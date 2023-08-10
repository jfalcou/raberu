/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu/raberu.hpp>
#include <type_traits>
#include <iostream>

using namespace rbr::literals;

inline constexpr auto unrolling = rbr::keyword("unrolling"_id);

template<int N> inline constexpr auto unroll = (unrolling = std::integral_constant<int,N>{});

void f(rbr::concepts::option auto const& s)
{
  std::cout << rbr::settings(s) << "\n";
}

int main()
{
  f( unroll<8> );
}
