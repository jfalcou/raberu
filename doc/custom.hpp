#error DO NOT INCLUDE - DOCUMENTATION PURPOSE ONLY

//==================================================================================================
/**
  \page custom Tutorial: Customizing Keyword

  @tableofcontents

  \section custom_01 Pre-bound Keyword

  Sometimes you wish you could have a terser syntax for keyword parameters.
  Let's say you want to pass a compile-time unrolling factor to some algorithm.

  @code
  // This is working but a bit verbose
  using namespace rbr::literals;
  inline constexpr auto unroll = rbr::keyword("unrolling"_id);

  auto x = my_algorithm( unroll = std::integral_constant<int,4>{});
  @endcode

  One idea is to defines a **pre-bound keyword parameter**, i.e constructs an inline
  variable initialized with the result of the assignment of a value to a keyword.

  @code
  using namespace rbr::literals;
  inline constexpr auto unrolling = rbr::keyword("unrolling"_id);

  template<int N> inline constexpr auto unroll = (unrolling = std::integral_constant<int,N>{});
  @endcode

  `unroll<N>` is now ready to be passed around. To retrieve it, you'll need to use
  the `unrolling` keyword.

  @include doc/tutorial04.cpp

  \section custom_02 Custom Keywords

  The keywords provided by **RABERU** can also be extended to propose a better user experience.
  This includes using user-defined type instead of **RABERU** long symbol to improve diagnostic
  , complex checks or provide custom display when using stream insertion of settings.

  \subsection custom-extension  Extending Keywords
  Let's start again with our unrolling option. This time we want to be able to be sure nobody
  will use it with a non integral constant value and to display the value in a more informative way.
  To do so, we can inherits from `rbr::keyword`, a CRTP enabled base class:

  @code
  struct unrolling : rbr::keyword<unrolling>
  {
    template<int N>
    constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
    {
      return rbr::option<unrolling,std::integral_constant<int,N>>{};
    }
  };

  template<int N>
  inline constexpr auto unroll = (unrolling{} = std::integral_constant<int, N>{});
  @endcode

  What if we call `f( unrolling{} = 3.f );` ? Well, we go this error message:

  @code
  example.cpp:25:18: error: no viable overloaded '='
    f( unrolling{} = 3.f );
       ~~~~~~~~~~~ ^ ~~~
  <source>:8:18: note: candidate template ignored: could not match 'integral_constant<int, N>' against 'float'
    constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
  @endcode

  \subsection custom-display Keywords Display
  Let's now improve the output of the option. Currently, the output is like:

  @code
  [unrolling] : 8 (std::integral_constant<int, 8>)
  @endcode

  A bit verbose especially for end-user.
  Keyword-like entity can specialize a `display` member function to replace this output by a custom one.

  @code
  struct unrolling : rbr::keyword<unrolling>
  {
    template<int N>
    constexpr auto operator=(std::integral_constant<int,N> const&) const noexcept
    {
      return rbr::option<unrolling,std::integral_constant<int,N>>{};
    }

    friend std::ostream& display(std::ostream& os, unrolling const&, auto v) { return os << "Unroll Factor: " << v; }
  };

  template<int N>
  inline constexpr auto unroll = (unrolling{} = std::integral_constant<int, N>{});
  @endcode

  The `display` member takes the output stream and the actual value of the option to be displayed.
  One can then arrange those as they see fit, leading to a better output:

  @include doc/tutorial05.cpp

**/
//==================================================================================================
