//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <raberu/raberu.hpp>
#include <string>
#include <iostream>

template<typename P0, typename P1> auto replicate( P0 p0, P1 p1 )
{
  using namespace rbr::literals;

  auto const params = rbr::settings(p0,p1);
  return std::string( params["replication"_kw], params["letter"_kw] );
}

void scenario_1()
{
  using namespace rbr::literals;

  std::cout << "replicate( \"letter\"_kw = 'c'   , \"replication\"_kw = 10 ):"  << "\n";
  std::cout << replicate( "letter"_kw = 'c'   , "replication"_kw = 10 )         << "\n";
  std::cout << "replicate( \"replication\"_kw = 7, \"letter\"_kw = '*'     ):"  << "\n";
  std::cout << replicate( "replication"_kw = 7, "letter"_kw = '*'     )         << "\n";
}

int main()
{
  scenario_1();
}
