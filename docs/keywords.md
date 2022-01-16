# Keywords and Options

Next to the direct usage of the `_kw` user-defined literal suffix, keyword
can be built with more control over their behavior. Let's dive into the
different variants of keywords and their definition API.

## Regular keywords

Let's say you want to pass a compile-time unrolling factor to some algorithm.
You can use a regular keyword as seen in the tutorial:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
auto x = my_algorithm( "unroll"_kw = std::integral_constant<int,4>{});
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is working but a bit verbose. Another issue can be that documenting the fact
that your functions awaits a `"unroll"_kw` maybe cumbersome.

A nicer way to simplify the user experience is to preemptively defines a keyword variable.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
inline constexpr auto unroll = "unroll"_kw;

auto x = my_algorithm( unroll = std::integral_constant<int,4>{});
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Slightly terser and far easier to document.

## Flag keywords
Sometimes, you just want to check if a given parameter has been passed but you don't really care about an associated value. Such keyword parameters are **flags**, carrying information about their sole presence without the need ot be bound to a value.

They work in a similar way than regular keyword parameters but use the `_fl` user-defined literal. Their  value can be retrieved via `rbr::settings::operator[]`. If present, the value returned is `std::true_type`, otherwise `std::false_type` is returned.

[You can see the code and execute it on Compiler Explorer]([Modal window](https://godbolt.org/z/585EY6WEY)).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

using namespace rbr::literals;

inline constexpr auto is_modal = "is_modal"_fl;
inline constexpr auto autosave = "autosave"_fl;

template<rbr::concepts::option... Params>
void check_options(Params const&... ps)
{
  auto s = rbr::settings(ps...);
  std::cout << "Modal window: " << std::boolalpha << s[is_modal] << " - "
            << "autosave: "     << std::boolalpha << s[autosave] << "\n";
}

int main()
{
  check_options();
  check_options(autosave);
  check_options(is_modal);
  check_options(autosave,is_modal);
  check_options(is_modal,autosave);
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Typed keywords

## Checked keywords
