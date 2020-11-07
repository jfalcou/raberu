<img src="https://github.com/jfalcou/raberu/raw/main/logo.png" alt="RABERU Library logo" data-canonical-src="https://github.com/jfalcou/raberu/raw/main/logo.png" align="left" width="18%" height="18%" />

# RABERU

**The Fancy, Dandy Parameters Library**

**Visual Studio**: [![Build status](https://ci.appveyor.com/api/projects/status/k1x181xn48w6qatt/branch/main?svg=true)](https://ci.appveyor.com/project/jfalcou/raberu/branch/main)&nbsp;&nbsp;**clang/gcc**: [![jfalcou](https://circleci.com/gh/jfalcou/raberu.svg?style=svg)](https://app.circleci.com/pipelines/github/jfalcou/raberu)


## Requirements
**RABERU** requires a C++20 conformat compiler.
It is currently test on latest MSVC, g++ 10.2 and clang++ 10.

## Installation and Usage
Installing **RABERU** is rather straight forward.

  1. Download the one header file `raberu.hpp` : 
     ```
     wget https://raw.githubusercontent.com/jfalcou/raberu/main/include/raberu.hpp
     ```
  2. Copy it in the location of your choice.

Using **RABERU** boils down to including `raberu.hpp` and compile using C++20.

```
g++ my_app.cpp -I/path/to/raberu -std=c++20
```

If you want to contribute to **RABERU**, you can clone this repository or fork it.

## Quick Start

**RABERU** want to provides a way to pass named parameters, *i.e* a list of values assigned to arbitrary keyword-like
identifiers, to functions. It does so by providing:

  + a protocol to define such keyword.
  + a type to process such aggregate of parameters.
  + a `constexpr`-compatible implementation for all of those.

**RABERU** main tools is the `rbr::settings` class that helps aggregating values into a set of
parameters than later be queried. Let's build a small example of a function building a string
from the replication of a given character.

### Defining the keywords

We will first defines two keywords to pass parameters:
  + `letter` to specify the character to replicate
  + `replications_` to specify the replication count of the character

This is done by creating instances of the `rbr::keyword` template variable. Each instance must be
defined with an unique tag, usually a locally defined, incomplete type.

``` c++
#include <raberu.hpp>
#include <string>
#include <iostream>

inline constexpr auto letter       = rbr::keyword<struct letter_tag>;
inline constexpr auto replication  = rbr::keyword<struct replication_tag>;
```

Once done, we can define our function. Parameters will be passed as template parameters and
aggregated by `rbr::settings`.

``` c++
template<typename Param0, typename Param1> auto replicate( Param0 p0, Param1 p1 )
{
  auto const params = rbr::settings(p0,p1);
}
```

Now, our parameters are ready to be fetched. Once can retrieve a given parameters via the
subscript operator of `rbr::settings` that takes a keyword as a parameter.

``` c++
template<typename Param0, typename Param1> auto replicate( Param0 p0, Param1 p1 )
{
  auto const params = rbr::settings(p0,p1);
  return std::string( params[replication], params[letter] );
}
```

The actual call of the function can then be done this way:

``` c++
int main()
{
  std::cout << replicate( letter = 'c'   , replication = 10 ) << "\n";
  std::cout << replicate( replication = 7, letter = '*'     ) << "\n";
}
```

which displays:

```
cccccccccc
*******
```

The complete code is as follows:

``` c++
#include <raberu.hpp>
#include <string>
#include <iostream>

inline constexpr auto letter       = rbr::keyword<struct letter_tag>;
inline constexpr auto replication  = rbr::keyword<struct replication_tag>;

template<typename Param0, typename Param1> auto replicate( Param0 p0, Param1 p1 )
{
  auto const params = rbr::settings(p0,p1);
  return std::string( params[replication], params[letter] );
}

int main()
{
  std::cout << replicate( letter = 'c'   , replication = 10 ) << "\n";
  std::cout << replicate( replication = 7, letter = '*'     ) << "\n";
}
```

and can be run on [Compiler Explorer](https://godbolt.org/z/eszcch).

## Other functionalities

### Informations about settings

  + One can query the size of a `rbr::settings`, *ie* the number of named parameters inside it, using the
    `size()` member function.

    ``` c++
    #include <raberu.hpp>
    #include <iostream>

    template<int N> struct nth;
    template<int N> inline constexpr auto arg  = rbr::keyword<nth<N>>;

    template<typename... Ps> auto check_size(Ps... ps)
    {
      return rbr::settings(ps...).size();
    }

    int main()
    {
      std::cout << check_size(arg<0> = 1, arg<1> = 2., arg<3> = 3.f) << "\n";
    }
    ```

    See [the code in action here](https://godbolt.org/z/ea9bGj).

  + One can query if an instance of `rbr::settings` contains a particular keyword using the
    `contains()` member function.

    ``` c++
    #include <raberu.hpp>
    #include <iostream>

    template<int N> struct nth;
    template<int N> inline constexpr auto arg  = rbr::keyword<nth<N>>;

    template<typename... Ps> auto check_size(Ps... ps)
    {
      return rbr::settings(ps...).size();
    }

    int main()
    {
      auto s =  rbr::settings(arg<0> = 1, arg<1> = 2., arg<3> = 3.f);
      std::cout << std::boolalpha << s.contains(arg<0>) << "\n";
      std::cout << std::boolalpha << s.contains(arg<1>) << "\n";
      std::cout << std::boolalpha << s.contains(arg<2>) << "\n";
      std::cout << std::boolalpha << s.contains(arg<3>) << "\n";
    }
    ```

    See [the code in action here](https://godbolt.org/z/YMerh7).

### Error handling
What happens if you try to access a parameters through a keyword that was not used ?

  * First, using `rbr::settings::operator[]` directly will result in an hard error complaining about `rbr::unknown_key`.
    so your code can never compiles and retrieves undefined data from who knows where.

  * You can pass an default value to your keyword via the `|` operator for keyword. If the retrieval
    of said keyword is impossible, the default value will be returned instead.

    ``` c++
    #include <raberu.hpp>
    #include <string>
    #include <iostream>

    inline constexpr auto letter       = rbr::keyword<struct letter_tag>;
    inline constexpr auto replication  = rbr::keyword<struct replication_tag>;

    template<typename... Args> auto replicate( Args... args)
    {
      auto const params = rbr::settings(args... );
      return std::string( params[ replication | 1 ], params[ letter | '?' ] );
    }

    int main()
    {
      std::cout << replicate( letter = 'c' ) << "\n";
      std::cout << replicate( replication = 7 ) << "\n";
      std::cout << replicate() << "\n";
    }
    ```

    See [the code in action here](https://godbolt.org/z/coTWb4).

  * You can pass an [Callable Object](https://en.cppreference.com/w/cpp/named_req/Callable) to your
    keyword via the `|` operator for keyword. If the retrieval of said keyword is impossible,
    the callable will be called with the faulty keyword as a parameter. One possible application
    is to throw exceptions in case of errors.

    ``` c++
    #include <raberu.hpp>
    #include <string>
    #include <iostream>
    #include <stdexcept>

    inline constexpr auto letter       = rbr::keyword<struct letter_tag>;
    inline constexpr auto replication  = rbr::keyword<struct replication_tag>;

    template<typename... Args> auto replicate( Args... args)
    {
        auto const params = rbr::settings(args... );
        auto oops = [](auto)
        {
            throw std::logic_error("Missing letter keyword");
            return 0;
        };

        return std::string( params[ replication ], params[ letter | oops ] );
    }

    int main()
    {
      try
      {
        std::cout << replicate( replication = 7 ) << "\n";
      }
      catch( std::logic_error& e)
      {
        std::cout << "EXCEPTION: " << e.what() << "\n";
      }
    }
    ```

Seee [the code in action](https://godbolt.org/z/j4anM5).

### Keyword-less parameters
**RABERU** supports passing of parameters without keyword. In this case, they're associated with
an implicit keyword build from the exact type of the parameter. This basically turns
`rbr::settings` into a set of parameters. Such use-cases can arise but it requires a more strict
handling of keyword as the exact value type must be known to retrieve it.

``` c++
#include <raberu.hpp>
#include <iostream>

template<typename... Vs> auto typed_interface(Vs const&... vs ) noexcept
{
  rbr::settings s(vs...);
  return s[rbr::keyword<int>] * s[rbr::keyword<double>];
}

int main()
{
  std::cout << typed_interface(10   , 3.41) << "\n";
  std::cout << typed_interface(13.37, 100 ) << "\n";
}
```

Seee [the code in action](https://godbolt.org/z/bzGY9K).

## License
This library is licensed under the MIT License as specified in the LICENSE.md file.
If you use RABERU in your project or product, feel free to send us an email so we can
advertise it here.

```
The MIT License (MIT)

Copyright (c) 2020 Joel FALCOU

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
`
