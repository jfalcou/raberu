//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace rbr
{
  namespace result
  {
    template<typename Settings, template<typename...> class List = types> struct keywords;
    template<typename Settings, template<typename...> class List = types> struct values;

    template<typename... Opts, template<typename...> class List>
    struct keywords<settings<Opts...>, List>
    {
      using type = List<typename Opts::keyword_type...>;
    };

    template<typename... Opts, template<typename...> class List>
    struct values<settings<Opts...>, List>
    {
      using type = List<typename Opts::stored_value_type...>;
    };

    template<typename Settings, template<typename...> class List = types>
    using keywords_t = typename keywords<Settings,List>::type;

    template<typename Settings, template<typename...> class List = types>
    using values_t = typename values<Settings,List>::type;
  }

  //====================================================================================================================
  //! @ingroup stng
  //! @brief Retrieved the list of all keywords in a settings
  //!
  //! @tparam List  A n-ary template type to hold the result values
  //! @param s      Settings to inspect
  //! @return An instance of rbr::type containing all the keyword from a rbr::settings.
  //!
  //! ## Helper Types
  //! @code
  //! namespace rbr::result
  //! {
  //!   template<template<typename...> class List, typename Settings> struct keywords;
  //!
  //!   template<template<typename...> class List, typename Settings>
  //!   using keywords_t = typename keywords<List,Settings>::type;
  //! }
  //! @endcode
  //!
  //! Return the type of a call to rbr::keywords.
  //!
  //! ## Example:
  //! @include doc/keywords.cpp
  //====================================================================================================================
  template<template<typename...> class List, typename... Opts>
  constexpr auto keywords([[maybe_unused]]rbr::settings<Opts...> const& s)
  {
    return result::keywords_t<rbr::settings<Opts...>,List>{typename Opts::keyword_type{}...};
  }

  //====================================================================================================================
  //! @ingroup stng
  //! @brief Retrieved the list of all value stored in a settings
  //!
  //! @tparam List  A n-ary template type to hold the result
  //! @param s      Settings to inspect
  //! @return an instance of rbr::type containing all the values from a rbr::settings.
  //!
  //! ## Helper Types
  //! @code
  //! namespace rbr::result
  //! {
  //!   template<template<typename...> class List, typename Settings> struct values;
  //!
  //!   template<template<typename...> class List, typename Settings>
  //!   using values_t = typename values<List,Settings>::type;
  //! }
  //! @endcode
  //!
  //! Return the type of a call to rbr::values.
  //!
  //! ## Example:
  //! @include doc/values.cpp
  //====================================================================================================================
  template<template<typename...> class List, typename... Opts>
  constexpr auto values(rbr::settings<Opts...> const& s)
  {
    return result::values_t<rbr::settings<Opts...>,List>{ s[typename Opts::keyword_type{}]... };
  }
}
