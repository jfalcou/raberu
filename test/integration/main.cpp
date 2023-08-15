#include <raberu/raberu.hpp>
#include <iostream>
#include <string>

using namespace rbr::literals;

template<rbr::concepts::option P0, rbr::concepts::option P1>
auto replicate( P0 p0, P1 p1 )
{
  auto const params = rbr::settings(p0,p1);
  return std::string( params["replication"_kw], params["letter"_kw] );
}

int main()
{
  std::cout << replicate("replication"_kw = 9, "letter"_kw = 'z'   ) << "\n";
  std::cout << replicate("letter"_kw = '!'   , "replication"_kw = 3) << "\n";
}
