#error DO NOT INCLUDE - DOCUMENTATION PURPOSE ONLY

//==================================================================================================
/**
  \page tutorial RABERU 101

  @tableofcontents

  The **RABERU** library provides a way to define and use named parameters, *i.e* a list of values assigned to
  arbitrary keyword-like identifiers, to functions.

  It does so by providing:

    + a protocol to define such keywords.
    + a type to process such an aggregate of parameters.
    + a `constexpr`-compatible implementation for all of those.


  \section tutorial_01 Keyword, Options, Settings

  Let's define a small function - `replicate` - that takes a character `c` and an integer `n` as parameters and
  returns a string containing `c` repeated `n` times. As we want our users to have maximum flexibility, we will
  pass those parameters as keyword/value pairs.

  @include doc/tutorial01.cpp

  Let's decompose this code:

    + First, we define the `replicate` function. It takes two parameters, which model
      rbr::concepts::option, ensuring the parameters are valid **RABERU**  key/value pairs.
    + Those parameters are then turned into an instance of rbr::settings, which will provide the interface to query values from the bundle of parameters.
    + We retrieve the value associated with the `"replication"_kw` and `"letter"_kw` keywords.
    + In the `main` function, we call `replicate` by passing key/value pairs. Note that the keys are the same identifiers as those used inside the function. Their order is irrelevant.

 That's it. The `replicate` function can now take keyword arguments, and as long as the proper keywords are used, it will work as intended.

 \section tutorial_02 Flavor of Keywords

 \subsection tutorial-keywords Regular keywords

 Let's say you want to pass a compile-time unrolling factor to some algorithm.
 You can use a regular keyword as seen in the tutorial:

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 auto x = my_algorithm( "unroll"_kw = std::integral_constant<int,4>{});
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 This is working, but a bit verbose. Another issue can be that documenting the fact
 that your functions awaits a `"unroll"_kw` maybe cumbersome.

 A nicer way to simplify the user experience is to define a keyword variable preemptively.

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 inline constexpr auto unroll = "unroll"_kw;

 auto x = my_algorithm( unroll = std::integral_constant<int,4>{});
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 Slightly terser and far easier to document.
 You can also use the rbr::keyword factory that takes an ID and returns a keyword instance.

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 inline constexpr auto unroll = rbr::keyword("unroll"_id);

 auto x = my_algorithm( unroll = std::integral_constant<int,4>{});
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 \subsection  tutorial-flags Flags
 Sometimes, you want to check if a given parameter has been passed, but you don't really care about an associated value. Such keyword parameters are **flags**, carrying information about their sole presence without the need ot be bound to a value.

 They work similarly to regular keyword parameters but use the `_fl` user-defined literal
 or the rbr::flag factory. Their value can be retrieved via rbr::settings::operator[]. If present, the value returned is `std::true_type`, otherwise `std::false_type` is returned.

 @include doc/tutorial02.cpp

 \subsection tutorial-checked Checked keywords
 Regular keywords accept values of any type. The flag keyword implicitly behaves as a boolean parameter.
 What if you need to have a keyword accepting values of a specific type? Or, in more complex
 contexts, what if you need a keyword accepting values whose types satisfy an arbitrary set of
 constraints ?

 To do so, we'll need to use the rbr::keyword factory function that
 accepts an optional template parameter. If this template parameter is a type,
 the keyword is set up to only accept values of this exact type.

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 using namespace rbr::literals;

 // color can only accept an unsigned 32-bit integer
 auto color = rbr::keyword<std::uint32_t>("color"_id);
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 If this template parameter is a unary template meta-function `F`, the keyword is set up to only
 accept value which type satisfy `F<T>::value == true`.

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 using namespace rbr::literals;

 template<typename T> struct large_type
 {
   static constexpr auto value = sizeof(T) >= 4;
 };

 // entropy can only accept types of at least 32 bits
 inline constexpr auto entropy = rbr::keyword<large_type>( "entropy"_id);
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 \section tutorial_03 Settings

 Another important **RABERU** component is rbr::settings. It aggregates key/value pairs in a way that simplifies their
 exploitation. rbr::settings provides functions for retrieving values from keywords, inspecting the stored keywords, and more.

 \subsection tutorial-settings Defining a Settings
 rbr::settings can be directly constructed from an arbitrary list of options, ie values bound to
 a keyword. Once constructed, its operator[] can be used to fetch the value of a given keyword.

 @include doc/tutorial03.cpp

 \subsection tutorial-stream  Stream insertion
 rbr::settings can be streamed to display the list of keyword/value pairs it contains

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 #include <raberu/raberu.hpp>
 #include <iostream>

 int main()
 {
   using namespace rbr::literals;

   auto values = rbr::settings("size"_kw = 75ULL, "transparent"_fl, "value"_kw = 7.7f);

   std::cout << values << "\n";
 }
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 The expected output should be:
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 'size' : 75 (long long unsigned int)
 'transparent' : 1 (std::integral_constant<bool, true>)
 'value' : 7.7 (float)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**/
//==================================================================================================
