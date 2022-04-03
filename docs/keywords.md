# Keywords usage

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

[You can see the code and execute it on Compiler Explorer](https://godbolt.org/z/585EY6WEY).

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

## Checked keywords
Regular keywords accept value of any types. Flag keyword implicitly behaves as boolean parameters.
What if you need to have a keyword accepting values of a specific type ? Or, in more complex
context, what if you need a keyword accepting values which types satisfy an arbitrary set of
constraints ?

To do so, we'll need to use the `rbr::keyword` factory function.

By default, `rbr::keyword` takes a parameter which type will be used as its unique identifier.
For example, the declaration:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~c++
using namespace rbr::literals;

auto color = rbr::keyword("color"_id));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

is equivalent to:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~c++
using namespace rbr::literals;

auto color = "color"_kw;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `_id` literal suffix is used to simplify the definition of unique type identifier.

`rbr::keyword` accepts an optional template parameter. If this template parameter is a type,
the keyword is setup to only accept value of this exact type.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~c++
using namespace rbr::literals;

// color can only accept unsigned 32 bits integer
auto color = rbr::keyword<std::uint32_t>("color"_id);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If this template parameter is a type `F` defining an internal template structure named `apply`,
the keyword is setup to only accept value which type satisfy `F::template apply<T>::value == true`.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~c++
using namespace rbr::literals;

struct large_type
{
  template<typename T> struct apply
  {
    static constexpr auto value = sizeof(T) >= 4;
  };
};

// entropy can only accept types of at least 32 bits
inline constexpr auto entropy = rbr::keyword<large_type>( "entropy"_id);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Keywords retrieval

Value associated to a given keyword can be retrieved from a pack of options directly.

## `rbr::fetch`

**Synopsis:**
```c++
namespace rbr
{
  template<concepts::keyword K, concepts::option... Os>
  constexpr decltype(auto) fetch(K const& kw, Os const&... os);               //  1

  template<concepts::keyword K, typename D, concepts::option... Os>
  constexpr decltype(auto) fetch(type_or_<K,V> const& kw, Os const&... os);   //  2
}
```

1. Retrieves the value associate to a given `rbr::concepts::keyword` from the variadic list `os...`.
2. Retrieves the value associate to a given `rbr::concepts::keyword` with default values
   from the variadic list `os...`.

**Example:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  int i = 77;

  std::cout << rbr::fetch("size"_kw, "size"_kw = 75ULL, "modal"_fl ) << "\n";
  std::cout << rbr::fetch("modal"_fl, "size"_kw = 75ULL, "modal"_fl ) << "\n";
  std::cout << rbr::fetch("value"_kw | 13.37, "size"_kw = 75ULL, "modal"_fl ) << "\n";
  std::cout << rbr::fetch("value"_kw | rbr::call([&]() { return ++i; }), "size"_kw = 75ULL, "modal"_fl )  << "\n\n";

  std::cout << "i = " << i << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Expected output:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
75
1
13.37
78

i = 78
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## `rbr::result::fetch`

**Synopsis:**
```c++
namespace rbr::result
{
  template<auto Keyword, concepts::option... Os> struct fetch
  {
    using type = decltype( rbr::fetch(Keyword, Os{}...) );
  };

  template<auto Keyword, concepts::option... Os>
  using fetch_t = typename fetch<Keyword,Os...>::type;
}
```

Computes the type associated to a given call to `rbr::fetch`.

## Direct retrieval
Any given `rbr::concepts::keyword` or  `rbr::concepts::keyword` with default values
can use its `operator()` to fetch its associated value.

**Example:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  int i = 77;

  std::cout << ("size"_kw)("size"_kw = 75ULL, "modal"_fl ) << "\n";
  std::cout << ("modal"_fl)("size"_kw = 75ULL, "modal"_fl ) << "\n";
  std::cout << ("value"_kw | 13.37)("size"_kw = 75ULL, "modal"_fl ) << "\n";
  std::cout << ("value"_kw | rbr::call([&]() { return ++i; }))( "size"_kw = 75ULL, "modal"_fl )  << "\n\n";

  std::cout << "i = " << i << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Expected output:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
75
1
13.37
78

i = 78
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
