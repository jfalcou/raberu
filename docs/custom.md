# Customizing Keyword

## Using Pre-bound keyword

Sometimes you wish you could have a terser syntax for keyword parameters.
Let's say you want to pass a compile-time unrolling factor to some algorithm.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
// This is working but a bit verbose
inline constexpr auto unroll = rbr::keyword<struct unroll_>;

auto x = my_algorithm( unroll = std::integral_constant<int,4>{});

// This looks better
auto x = my_algorithm( unroll<4> );
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

One idea is to defines a **pre-bound keyword parameter**, i.e constructs an inline
variable initialized with the result of the assignment of a value to a keyword.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
inline constexpr auto unrolling = keyword<struct unrolling>;

template<int N> inline constexpr auto unroll = (unrolling = std::integral_constant<int,N>{});
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

`unroll<N>` is now ready to be passed around. To retrieve it, you'll need to use
the `unrolling` keyword.

[You can see the code and execute it on Compiler Explorer](https://godbolt.org/z/YPnzEEdY1).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <type_traits>
#include <iostream>

using namespace rbr::literals;

inline constexpr auto unrolling = "unroll"_kw;

template<int N>
inline constexpr auto unroll = (unrolling = std::integral_constant<int,N>{});

template<typename S> void f(S const& s)
{
  std::cout << rbr::settings(s) << "\n";
}

int main()
{
  f( unroll<8> );
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Custom RABERU Keywords

THe keywords provided by **RABERU** can also be extended to propose a better user experience.
This includes using user-defined type instead of **RABERU** long symbol to improve diagnostic
, complex checks or provide custom display when using stream insertion of settings.

### Extending RABERU Keywords
Let's start again with our unrolling option. This time we want to be able to be sure nobody
will use it with a non integral constant value and to display the value in a more informative way.
To do so, we can inherits from `rbr::any_keyword`:

[You can see the code and execute it on Compiler Explorer](https://godbolt.org/z/PT79qYncd).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
struct unrolling : rbr::any_keyword<unrolling>
{
  template<int N>
  constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
  {
    return rbr::option<unrolling,std::integral_constant<int,N>>{};
  }
};

template<int N>
inline constexpr auto unroll = (unrolling{} = std::integral_constant<int,N>{});
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

What if we call `f( unrolling{} = 3.f );` ? Well, we go this error message:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
example.cpp:24:18: error: no viable overloaded '='
  f( unrolling{} = 3.f );
     ~~~~~~~~~~~ ^ ~~~

example.cpp:8:18: note: candidate template ignored: could not match 'integral_constant<int, N>' against 'float' constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
                 ^
example.cpp:5:8: note: candidate function (the implicit copy assignment operator) not viable: no known conversion from 'float' to 'const unrolling' for 1st argument struct unrolling : rbr::any_keyword<unrolling>
       ^
example.cpp:5:8: note: candidate function (the implicit move assignment operator) not viable: no known conversion from 'float' to 'unrolling' for 1st argument struct unrolling : rbr::any_keyword<unrolling>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Custom Keywords Display
Let's now improve the output of the option. Currently, the output is like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~c++
[unrolling] : 8 (std::integral_constant<int, 8>)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A bit verbose especially for end-user.
Keyword-like entity can specialize a `show` member function to replace this output by a custom one.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
struct unrolling : rbr::any_keyword<unrolling>
{
  template<int N>
  constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
  {
    return rbr::option<unrolling,std::integral_constant<int,N>>{};
  }

  std::ostream& show(std::ostream& os, std::size_t n) const
  {
    return os << "Unroll Factor: x" << n;
  }
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `show` member takes the output stream and the actual value of the option to be displayed.
One can then arrange those as they see fit, leading to a better output:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~c++
Unroll Factor: x8
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
