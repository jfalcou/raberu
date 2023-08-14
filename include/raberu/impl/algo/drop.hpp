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
  namespace _
  {
    template<typename K, concepts::keyword... Kept>
    struct filter
    {
      using type = _::keys<Kept...>;

      template<typename T> constexpr auto operator+(keys<T> const&) const
      {
        using kw_t = typename T::keyword_type;
        if constexpr(!stdfix::same_as<K, typename kw_t::tag_type>)  return filter<K, Kept..., kw_t>{};
        else                                                        return *this;
      }
    };

    template< typename K, typename S> struct select_keys;

    template< typename K, concepts::option... Os>
    struct  select_keys<K,rbr::settings<Os...>>
          : decltype((filter<typename K::tag_type>{}  + ... +  _::keys<Os>{}))
    {
    };
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
      // Rebuild a new settings by going over the keys that we keep
      return rbr::settings{ (Ks{} = s[Ks{}] )...};
    }(selected_keys_t{});
  }

  namespace result
  {
    template<concepts::keyword K, concepts::option... O>
    struct drop
    {
      using type = decltype( rbr::drop(std::declval<K>(),std::declval<O>()...) );
    };

    template<concepts::keyword K, concepts::option... O>
    using drop_t = typename drop<K,O...>::type;
  }
}
