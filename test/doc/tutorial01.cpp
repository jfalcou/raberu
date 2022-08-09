/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <raberu.hpp>
#include <string>
#include <iostream>

template<rbr::concepts::option P0, rbr::concepts::option P1>
auto replicate( P0 p0, P1 p1 )
{
  using namespace rbr::literals;

  auto const params = rbr::settings(p0,p1);
  return std::string( params["replication"_kw], params["letter"_kw] );
}

int main()
{
  using namespace rbr::literals;

  std::cout << replicate("replication"_kw = 9, "letter"_kw = 'z'   ) << "\n";
  std::cout << replicate("letter"_kw = '!'   , "replication"_kw = 3) << "\n";
}
