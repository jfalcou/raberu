# Settings

The main **RABERU** component is `rbr::settings`. It aggregates key/value pairs in a way their
exploitation is simplified. `rbr::settings` provides functions for retrieving value from keywords,
inspect the stored keywords and more.

## Option retrieval

### `rbr::settings::operator[]`

**Synopsis:**
```c++
namespace rbr
{
  template<concepts::keyword Key>
  constexpr auto settings::operator[](Key const&) const noexcept;                   //  1

  template<typename Keyword>
  constexpr auto settings::operator[](flag_keyword<Keyword> const&) const noexcept; //  2

  template<concepts::keyword Key, typename Value>
  constexpr auto settings::operator[](detail::type_or_<Key, Value> const&) const;   //  3
}
```

1. Retrieves the value associate to a given `rbr::concepts::keyword`.
2. Retrieves the value associate to a given flag `rbr::concepts::keyword`.
3. Retrieves the value associate to a given `rbr::concepts::keyword` with an alternative value or
   monadic operation provided by `rbr::call`.

**Example:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  int i = 77;
  auto values = rbr::settings("size"_kw = 75ULL, "transparent"_fl);

  std::cout << values["size"_kw]                                      << "\n";
  std::cout << values["transparent"_fl]                               << "\n";
  std::cout << values["value"_kw | 13.37]                             << "\n";
  std::cout << values["value"_kw | rbr::call([&]() { return ++i; })]  << "\n\n";

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

### Stream insertion

**Synopsis:**
```c++
namespace rbr
{
  std::ostream& operator<<(std::ostream& os, settings const& s);
}
```

Display the contents of the `rbr::settings` `s` onto an output stream.

**Example:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  auto values = rbr::settings("size"_kw = 75ULL, "transparent"_fl, "value"_kw = 7.7f);

  std::cout << values << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Expected output:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'size' : 75 (long long unsigned int)
'transparent' : 1 (std::integral_constant<bool, true>)
'value' : 7.7 (float)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Introspection

### Size

**Synopsis:**
```c++
namespace rbr
{
  static constexpr std::ptrdiff_t settings::size() noexcept;
}
```

Return the number of options stored in a given `rbr::settings`.

**Example:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  auto values = rbr::settings("size"_kw = 75ULL, "transparent"_fl, "value"_kw = 7.7f);

  std::cout << values.size() << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Expected output:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Keys checking

**Synopsis:**
```c++
namespace rbr
{
  template<concepts::keyword Key>
  static constexpr auto settings::contains(Key const &) noexcept;           //  1

  template<concepts::keyword... Keys>
  static constexpr auto settings::contains_any(Keys... ks) noexcept;        //  2

  template<concepts::keyword... Keys>
  static constexpr auto settings::contains_only(Keys const&...) noexcept;   //  3

  template<concepts::keyword... Keys>
  static constexpr auto settings::contains_none(Keys... ks) noexcept;       //  4
}
```

1. Checks if a given keyword is contained in a `rbr::settings`.
2. Checks if any keywords from the parameters are contained in a `rbr::settings`.
3. Checks if only keywords from the parameters are contained in a `rbr::settings`.
4. Checks if no keywords from the parameters are contained in a `rbr::settings`.

**Example:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  auto values = rbr::settings("size"_kw = 75ULL, "transparent"_fl, "value"_kw = 7.7f);

  std::cout << std::boolalpha << values.contains("value"_kw) << "\n";
  std::cout << std::boolalpha << values.contains_any("size"_kw, "color"_kw) << "\n";
  std::cout << std::boolalpha << values.contains_only("size"_kw) << "\n";
  std::cout << std::boolalpha << values.contains_none("color"_kw) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Expected output:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
true
true
false
true
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Settings manipulation

### Merging settings

**Synopsis:**
```c++
namespace rbr
{
  template<concepts::option... K1s, concepts::option... K2s>
  constexpr auto merge(settings<K1s...> const& opts, settings<K2s...> const& defs) noexcept
}
```

Merge two `rbr::settings` and return a new options set containing all the values of `opts` and
all the value from `defs` that are not already present in `opts`.

**Example:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  auto defaults = rbr::settings("name"_kw = std::string{"Jane Doe"}, "value"_kw = 42.69f, "modal"_fl);
  auto opts     = rbr::settings("value"_kw = 956.7f);

  auto merged = rbr::merge(opts, defaults);

  std::cout << merged["name"_kw] << "\n";
  std::cout << merged["value"_kw] << "\n";
  std::cout << merged["modal"_fl] << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Expected output:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Jane Doe
956.7
1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Dropping keywords

**Synopsis:**
```c++
namespace rbr
{
  template<concepts::keyword K, concepts::option... Os>
  constexpr auto drop(K const& k, settings<Os...> const& os)
}
```

Return a `rbr::settings` containing all options from `os` except for the keyword `k`.

**Example:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu.hpp>
#include <iostream>

int main()
{
  using namespace rbr::literals;

  rbr::settings v ( "surname"_kw = std::string{"john"}
                  , "value"_kw = 3.f
                  , "aligned"_fl
                  , "transparent"_fl
                  );

  std::cout << v << "\n";
  std::cout << "\n";
  std::cout << drop("aligned"_fl, v) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Expected output:**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'surname' : john (std::__cxx11::basic_string<char>)
'value' : 3 (float)
'aligned' : 1 (std::integral_constant<bool, true>)
'transparent' : 1 (std::integral_constant<bool, true>)


'surname' : john (std::__cxx11::basic_string<char>)
'value' : 3 (float)
'transparent' : 1 (std::integral_constant<bool, true>)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
