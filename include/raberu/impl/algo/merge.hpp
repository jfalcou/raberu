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
  //================================================================================================
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
  //================================================================================================
  template<concepts::option... K1s, concepts::option... K2s>
  constexpr auto merge(settings<K1s...> const& opts, settings<K2s...> const& defs) noexcept
  {
    auto selector = []<typename K, typename Opts>(K const&, Opts const& o, auto const& d)
                    {
                      constexpr K key;
                      if constexpr( Opts::contains(key) ) return (key = o[key]);
                      else                                return (key = d[key]);
                    };

    auto select = [&]<typename... Ks>(_::keys<Ks...> const&, auto const& os, auto const& ds)
    {
      return settings(selector(Ks{},os,ds)...);
    };

    return select(typename _::uniques<_::keys<typename K1s::keyword_type...>
                                          ,_::keys<typename K2s::keyword_type...>
                                          >::type{},opts,defs);
  }

  namespace result
  {
    template<concepts::settings S1, concepts::settings S2>
    struct merge
    {
      using type = decltype( rbr::merge(std::declval<S1>(),std::declval<S2>()) );
    };

    template<concepts::settings S1, concepts::settings S2>
    using merge_t = typename merge<S1,S2>::type;
  }
}
