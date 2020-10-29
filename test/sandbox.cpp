//#define RABERU_NOEXCEPT
#include <raberu.hpp>
#include <iostream>
#include <array>

struct foo
{
  using option_tag = rbr::option_<foo>;
  int i;
};

struct bar
{
  using option_tag = rbr::option_<bar>;
  float dx;
};

struct chu {};

namespace rbr
{
  template<> struct tag<chu> : rbr::option_<chu> {};

  template<typename T, std::size_t N>
  struct tag<std::array<T,N>> : rbr::option_<std::array<T,N>> {};
}

int main()
{
  constexpr auto x = rbr::settings(foo{4}, bar{0.04f}, std::array<float,3>{0.1f,0.2f,0.3f} );
  std::cout << x.get<foo>().i << std::endl;
  std::cout << x.get<bar>().dx << std::endl;
  std::cout << x.get_or<chu>("lol") << std::endl;

  auto o = x.maybe_get<std::array<float,3>>();
  std::cout << std::boolalpha << bool(o) << "\n";
  for(auto e : *o)
    std::cout << e << " ";
  std::cout << "\n";

  x.get_or_eval<chu>( []() { std::cout << "C'est balot :/\n"; } );

  try
  {
    x.try_get<chu>();
  }
  catch( rbr::unknown_option_exception& e )
  {
    std::cout << e.what() << "\n";
  }

  std::array<char, x.get<foo>().i> y;
  std::cout << y.size() << "\n";
}