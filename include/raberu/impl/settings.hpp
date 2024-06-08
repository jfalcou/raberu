//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <cstddef>
#include <ostream>
#include <type_traits>

//==================================================================================================
//! @ingroup  main
//! @{
//!   @defgroup stng Settings definitions and handling
//!   @brief    Functions and types to handle RABERU settings
//! @}
//==================================================================================================

namespace rbr
{
  /// Type indicating that a [Keyword](@ref rbr::concepts::keyword) is not available
  struct unknown_key { using type = unknown_key; };

  // Option calls aggregator
  template<concepts::option... Ts> struct aggregator : Ts...
  {
    constexpr aggregator(Ts const&...t) noexcept : Ts(t)... {}
    using Ts::operator()...;

    template<concepts::keyword K> constexpr auto operator()(K const &) const noexcept
    {
      return unknown_key {};
    }
  };

  //================================================================================================
  //! @ingroup stng
  //! @brief Defines a group of options for processing
  //!
  //! rbr::settings acts as an aggregation of [Options](@ref rbr::concepts::option) (ie pair of
  //! [Keyword](@ref rbr::concepts::keyword)/value) that provides an user-interface for accessing
  //! or managing said [Options](@ref rbr::concepts::option) and to gather informations.
  //!
  //! @tparam Opts  List of [options](@ref rbr::concepts::option) aggregated
  //================================================================================================
  template<concepts::option... Opts> struct settings
  {
    using rbr_settings = void;
    using base = aggregator<Opts...>;

    /// Constructor from a variadic pack of rbr::concepts::option
    constexpr settings(Opts const&... opts) : content_(opts...) {}

    /// Number of options in current rbr::settings
    static constexpr std::ptrdiff_t size() noexcept { return sizeof...(Opts); }

    //==============================================================================================
    //! @brief Checks if a given rbr::keyword is stored inside rbr::settings
    //! @param kw Keyword to check
    //! @return An instance of `std::true_type` if current setting contains an option based on `kw`.
    //!         Otherwise, return an instance of `std::false_type`.
    //! ## Example:
    //! @include doc/contains.cpp
    //==============================================================================================
    template<concepts::keyword Key>
    static constexpr auto contains([[maybe_unused]] Key const& kw) noexcept
    {
      using found = decltype((std::declval<base>())(Key{}));
      return !stdfix::same_as<found, unknown_key>;
    }

    //==============================================================================================
    //! @brief Checks if rbr::settings contains at least one of maybe keyword
    //! @param ks Keywords to check
    //! @return An instance of `std::true_type` if current setting contains at least one option
    //!         based on any of the `ks`. Otherwise, return an instance of `std::false_type`.
    //! ## Example:
    //! @include doc/contains_any.cpp
    //==============================================================================================
    template<concepts::keyword... Keys>
    static constexpr auto contains_any(Keys... ks) noexcept { return (contains(ks) || ...); }

    //==============================================================================================
    //! @brief Checks if rbr::settings contains options based only on selected keywords
    //! @param ks Keywords to check
    //! @return An instance of `std::true_type` if current setting contains only options
    //!         based on any of the `ks`. Otherwise, return an instance of `std::false_type`.
    //! ## Example:
    //! @include doc/contains_only.cpp
    //==============================================================================================
    template<concepts::keyword... Keys>
    static constexpr auto contains_only([[maybe_unused]] Keys const&... ks) noexcept
    {
      using current_keys    = _::keys<typename Opts::keyword_type...>;
      using acceptable_keys = _::keys<Keys...>;
      using unique_set      = typename _::uniques<current_keys,acceptable_keys>::type;
      return  _::is_equivalent<unique_set, acceptable_keys>::value;
    }

    //==============================================================================================
    //! @brief Checks if rbr::settings contains no options based on any of the selected keywords
    //! @param ks Keywords to check
    //! @return An instance of `std::true_type` if current setting contains no options
    //!         based on any of the `ks`. Otherwise, return an instance of `std::false_type`.
    //! ## Example:
    //! @include doc/contains_none.cpp
    //==============================================================================================
    template<concepts::keyword... Keys>
    static constexpr auto contains_none(Keys... ks) noexcept { return !contains_any(ks...); }

    //==============================================================================================
    //! @brief Retrieved a value via a keyword
    //!
    //! Retrieve the value bound to a given keyword `k` inside current rbr::settings instance.
    //! If such a keyword is not present, either an instance of rbr::unknown_key is returned or
    //! a default value or function call will be returned.
    //!
    //! @param k Keywords to check
    //! @return If any, the value bound to `k`.
    //! ## Example:
    //! @include doc/subscript.cpp
    //==============================================================================================
    template<concepts::keyword Key> constexpr auto operator[](Key const& k) const noexcept
    {
      return content_(k);
    }

    //! @overload
    template<typename Keyword>
    constexpr auto operator[](flag_keyword<Keyword> const&) const noexcept
    {
      return contains(flag_keyword<Keyword>{});
    }

    //! @overload
    template<concepts::keyword Key, typename Value>
    constexpr auto operator[](_::type_or_<Key, Value> const & tgt) const
    {
      if constexpr( contains(Key{}) )                           return (*this)[Key{}];
      else  if constexpr( requires(Value t) { t.perform(); } )  return tgt.value.perform();
      else                                                      return tgt.value;
    }

    //! @related rbr::settings
    //! @brief Output stream insertion
    friend std::ostream& operator<<(std::ostream& os, settings const& s)
    {
      auto show = [&]<typename T, typename V>(T t, V const& v) -> std::ostream&
      {
        return t.show(os,v) << "\n";
      };

      (show(typename Opts::keyword_type{}, s[typename Opts::keyword_type{}]), ...);

      return os;
    }

    base content_;
  };

  /// rbr::settings deduction guide
  template<concepts::option... Opts>
  settings(Opts const&... opts) -> settings<Opts...>;
}
