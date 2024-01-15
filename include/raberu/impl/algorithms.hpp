//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <raberu/impl/helpers.hpp>
#include <raberu/impl/concepts.hpp>

namespace rbr::_
{
  template<typename K, concepts::keyword... Kept>
  struct filter
  {
    using type = _::keys<Kept...>;
    template<typename T> constexpr auto operator%(keys<T> const&) const
    {
      using kw_t = typename T::keyword_type;
      if constexpr(!stdfix::same_as<K, typename kw_t::keyword_identifier>)  return filter<K, Kept..., kw_t>{};
      else                                                                  return *this;
    }
  };

  template< typename K, typename S> struct select_keys;
  template< typename K, concepts::option... Os>
  struct  select_keys<K,rbr::settings<Os...>>
        : decltype((filter<typename K::keyword_identifier>{}  % ... %  _::keys<Os>{}))
  {
  };
}

namespace rbr
{
  //====================================================================================================================
  //! @ingroup stng
  //! @brief Retrieved a value via a keyword
  //!
  //! Retrieve the value bound to a given keyword `k` inside a variadic list of rbr::options.
  //! If such a keyword is not present, either an instance of rbr::unknown_key is returned or
  //! a default value or function call will be returned.
  //!
  //! @param k Keywords to check
  //! @param os Options to inspect
  //! @return If any, the value bound to `k`.
  //!
  //! ## Helper Types
  //! @code
  //! namespace rbr::result
  //! {
  //!   template<auto Keyword, typename... Sources> struct fetch
  //!
  //!   template<auto Keyword, typename... Sources>
  //!   using fetch_t = typename fetch<Keyword,Sources...>::type;
  //! }
  //! @endcode
  //!
  //! Return the type of a call to rbr::fetch.
  //!
  //! ## Example:
  //! @include doc/fetch.cpp
  //====================================================================================================================
  constexpr decltype(auto) fetch(concepts::keyword auto const& k, concepts::option auto const&... os)
  {
    auto const opts = settings(os...);
    return opts[k];
  }

  //! @overload
  template<concepts::keyword K, typename V, concepts::option... Os>
  constexpr decltype(auto) fetch(keyword_or<K, V> const& k, Os const&... os)
  {
    auto const opts = settings(os...);
    return opts[k];
  }

  //! @overload
  constexpr decltype(auto) fetch(concepts::keyword auto const& k, concepts::settings auto const& opts)
  {
    return opts[k];
  }

  //====================================================================================================================
  //! @ingroup stng
  //! @related rbr::settings
  //! @brief Merge two instances of rbr::settings
  //!
  //! Merge all options of `opts` and `defs`. If an options is present in both arguments, the one
  //! from `opts` is used.
  //!
  //! @param opts rbr::settings to merge
  //! @param defs rbr::settings acting as default value
  //! @return An instance of rbr::settings containing all options from `opts` and any options
  //!         from `defs` not present in `opts`.
  //! ## Example:
  //! @include doc/merge.cpp
  //====================================================================================================================
  template<typename... K1s, typename... K2s>
  constexpr auto merge(settings<K1s...> const& opts, settings<K2s...> const& defs) noexcept
  {
    auto selector = []<typename K, typename Opts>(K const&, Opts const& o, auto const& d)
                    {
                      constexpr K key;
                      if constexpr( Opts::contains(key) ) return (key = o.fetch(key));
                      else                                return (key = d.fetch(key));
                    };

    auto select = [&]<typename... Ks>(_::keys<Ks...> const&, auto const& os, auto const& ds)
    {
      return settings(selector(Ks{},os,ds)...);
    };

    return select(typename _::uniques < _::keys<typename K1s::keyword_type...>
                                      , _::keys<typename K2s::keyword_type...>
                                      >::type{},opts,defs);
  }

  //====================================================================================================================
  //! @ingroup stng
  //! @related rbr::settings
  //! @brief Remove an option from a rbr::settings
  //!
  //! Build a rbr::settings containing all options from s except for any option bound to the `k`
  //! rbr::keyword.
  //!
  //! @param k Keyword to remove
  //! @param s Original rbr::settings
  //! @return An instance of rbr::settings containing all options of `s` except those bound to `k`.
  //!
  //! ## Example:
  //! @include doc/drop.cpp
  //====================================================================================================================
  template<concepts::keyword K, concepts::option... O>
  [[nodiscard]] constexpr auto drop([[maybe_unused]] K const& k, settings<O...> const& s)
  {
    using selected_keys_t = typename _::select_keys<K,settings<O...>>::type;
    return [&]<typename ... Ks>( _::keys<Ks...> )
    {
      return rbr::settings{ (Ks{} = s.fetch(Ks{}) )...};
    }(selected_keys_t{});
  }

  namespace result
  {
    // VALUES & KEYWORDS
    template< typename Settings, template<typename...> class List = types> struct keywords;
    template< typename Settings, template<typename...> class List = types> struct values;

    template<typename... Opts, template<typename...> class List>
    struct keywords<settings<Opts...>, List>
    {
      using type = List<typename Opts::keyword_type...>;
    };

    template<typename... Opts, template<typename...> class List>
    struct values<settings<Opts...>, List>
    {
      using type = List<std::unwrap_reference_t<typename Opts::stored_value_type>...>;
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
  constexpr auto values(rbr::settings<Opts...>& s)
  {
    return result::values_t<rbr::settings<Opts...>,List>{ s[typename Opts::keyword_type{}]... };
  }

  template<concepts::settings S1, concepts::settings S2>
  inline constexpr bool is_equivalent_v =   _::is_equivalent< result::keywords_t<S1,_::keys>
                                                            , result::keywords_t<S2,_::keys>
                                                            >::value
                                        &&  _::is_equivalent< result::keywords_t<S2,_::keys>
                                                            , result::keywords_t<S1,_::keys>
                                                            >::value;

  //====================================================================================================================
  //! @ingroup stng
  //! @brief Checks the equivalence of two rbr::settings
  //!
  //! Two rbr::settings are equivalent if they contain the same exact set of keywords irregardless
  //! of their values or value types.
  //!
  //! @tparam S1 rbr::settings to compare
  //! @tparam S2 rbr::settings to compare
  //!
  //! ## Helper Value
  //! @code
  //! namespace rbr
  //! {
  //!   template<concepts::settings S1, concepts::settings S2>
  //!   inline constexpr bool is_equivalent_v = is_equivalent<S1,S2>::value;
  //! }
  //! @endcode
  //!
  //! Contains the result of a call to rbr::is_equivalent.
  //!
  //! ## Example:
  //! @include doc/is_equivalent.cpp
  //====================================================================================================================
  template<concepts::settings S1, concepts::settings S2>
  struct  is_equivalent : std::bool_constant<is_equivalent_v<S1,S2>>
  {};

  namespace result
  {
    //  FETCH
    template<auto Keyword, typename... Sources> struct fetch;

    template<auto Keyword, concepts::option... Os>
    struct fetch<Keyword, Os...>
    {
      using type = decltype( rbr::fetch(Keyword, std::declval<Os>()...) );
    };

    template<auto Keyword, concepts::settings Settings>
    struct fetch<Keyword, Settings>
    {
      using type = decltype( rbr::fetch(Keyword, std::declval<Settings>()) );
    };

    template<auto Keyword, typename... Sources>
    using fetch_t = typename fetch<Keyword,Sources...>::type;

    // DROP
    template<concepts::keyword K, concepts::option... O>
    struct drop
    {
      using type = decltype( rbr::drop(std::declval<K>(),std::declval<O>()...) );
    };

    template<concepts::keyword K, concepts::option... O>
    using drop_t = typename drop<K,O...>::type;

    // MERGE
    template<concepts::settings S1, concepts::settings S2>
    struct merge
    {
      using type = decltype( rbr::merge(std::declval<S1>(),std::declval<S2>()) );
    };

    template<concepts::settings S1, concepts::settings S2>
    using merge_t = typename merge<S1,S2>::type;
  }
}
