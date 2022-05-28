/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
#include <raberu.hpp>
#include <type_traits>
#include <iostream>

#include <raberu.hpp>
#include <type_traits>
#include <iostream>

struct unrolling : rbr::as_keyword<unrolling>
{
  template<int N>
  constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
  {
    return rbr::option<unrolling,std::integral_constant<int,N>>{};
  }
   std::ostream& display(std::ostream& os, auto v) const { return os << "Unroll Factor: " << v; }
};

template<int N>
inline constexpr auto unroll = (unrolling{} = std::integral_constant<int, N>{});

void f(rbr::concepts::option auto const& s)
{
  std::cout << rbr::settings(s) << "\n";
}

int main()
{
  f( unroll<8> );
}
