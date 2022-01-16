# Tutorial

**RABERU** main tool is the `rbr::settings` class that helps aggregate values into a set of parameters that later be queried. Let's build a small example of a function building a string from the replication of a given character.

## Using simple keywords

Let's define a small function - `replicate` - that takes a character `c` and an integer `n` as parameters and return a string containing `c` repeated `n` times.
As we want our users to have maximum flexibility, we will pass those parameters as keyword/value pairs.

[You can see the code and execute it on Compiler Explorer](https://godbolt.org/z/oWjP44n57).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Let's decompose this code:

  + First, we define the `replicate` function. It takes two parameters which model the `rbr::concepts::option` concept, ensuring the aprameters are valid **RABERU**  key/value pairs.
  + Those parameters are then turned into an instance of `rbr::settings` which will provide the interface to query values from the bundle of parameters.
  + We retrieve the value associated to the `"replication"_kw` and `"letter"_kw` keywords.
  + In the `main` function, we call `replicate` by passing key/value pairs. Note that the keys are the exact same identifiers than those used inside the function. Their order is irrelevant.

That's it. The `replicate` function can now takes keywords arguments and as long as the proper keywords are used, it will work as intended.
