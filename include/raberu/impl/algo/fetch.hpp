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
  template<concepts::keyword K, concepts::option... Os>
  constexpr decltype(auto) fetch(K const& k, Os const&... os)
  {
    auto const opts = settings(os...);
    return opts[k];
  }

  //! @overload
  template<concepts::keyword K, typename V, concepts::option... Os>
  constexpr decltype(auto) fetch(_::type_or_<K, V> const& k, Os const&... os)
  {
    auto const opts = settings(os...);
    return opts[k];
  }

  //! @overload
  template<typename K, concepts::settings Settings>
  constexpr decltype(auto) fetch(K const& k, Settings const& opts)
  {
    return opts[k];
  }

  namespace result
  {
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
  }
}
