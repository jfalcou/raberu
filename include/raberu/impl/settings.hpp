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

//==================================================================================================
//! @ingroup  main
//! @{
//!   @defgroup stng Settings definitions and handling
//!   @brief    Functions and types to handle RABERU settings
//! @}
//==================================================================================================

namespace rbr
{
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
  template<concepts::option... Options>
  struct settings : private Options...
  {
    using rbr_settings = void;

    /// Number of options in current rbr::settings
    static constexpr std::ptrdiff_t 	size () noexcept { return sizeof...(Options); }

    /// Constructor from a variadic pack of rbr::concepts::option
    constexpr explicit(sizeof...(Options) == 1)
    settings(Options... opts) : Options(std::move(opts))... {}

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
    template<concepts::keyword K>
    constexpr decltype(auto) operator[](K const&) const { return unwrap(typename K::keyword_identifier{}); }

    template<concepts::keyword_with_default<settings> K>
    constexpr decltype(auto) operator[](K const& key) const
    {
      // Fetch the option or unknwon_key
      decltype(auto) that = unwrap(typename K::keyword_identifier{});

      // If we can have a default value and it is needed due to unknwon_key being returned
      if constexpr(stdfix::same_as<std::remove_cvref_t<decltype(that)>, unknown_key>)
        return key.default_value(*this);
      else
        return that;
    }

    //==============================================================================================
    //! @brief Checks if rbr::settings contains a given keyword
    //! @param kw Keyword to check
    //! @return `true` if current setting contains an option based on the `kw`, and `false` otherwise.
    //! ## Example:
    //! @include doc/contains.cpp
    //==============================================================================================
    template<concepts::keyword Key>
    static constexpr auto contains([[maybe_unused]] Key const& kw) noexcept
    {
      if constexpr( requires{ std::declval<settings>().fetch(typename Key::keyword_identifier{}); } )
      {
        using found = decltype(std::declval<settings>().fetch(typename Key::keyword_identifier{}));
        return !stdfix::same_as<found, unknown_key>;
      }
      else
      {
        return false;
      }
    }

    //==============================================================================================
    //! @brief Checks if rbr::settings contains at least one of maybe keyword
    //! @param ks Keywords to check
    //! @return `true` if current setting contains at least one option based on any of the `ks`, and `false` otherwise.
    //! ## Example:
    //! @include doc/contains_any.cpp
    //==============================================================================================
    template<concepts::keyword... Keys>
    static constexpr auto contains_any(Keys... ks) noexcept { return (contains(ks) || ...); }

    //==============================================================================================
    //! @brief Checks if rbr::settings contains options based only on selected keywords
    //! @param ks Keywords to check
    //! @return `true` if current setting contains only options based on any of the `ks`, and `false` otherwise.
    //! ## Example:
    //! @include doc/contains_only.cpp
    //==============================================================================================
    template<concepts::keyword... Keys>
    static constexpr auto contains_only([[maybe_unused]] Keys const&... ks) noexcept
    {
      using current_keys    = _::keys<typename Options::keyword_type::keyword_identifier...>;
      using acceptable_keys = _::keys<typename Keys::keyword_identifier...>;
      using unique_set      = typename _::uniques<current_keys,acceptable_keys>::type;
      return  _::is_equivalent<unique_set, acceptable_keys>::value;
    }

    //==============================================================================================
    //! @brief Checks if rbr::settings contains no options based on any of the selected keywords
    //! @param ks Keywords to check
    //! @return `true` if current setting contains no options based on any of the `ks`, and `false` otherwise.
    //! ## Example:
    //! @include doc/contains_none.cpp
    //==============================================================================================
    template<concepts::keyword... Keys>
    static constexpr auto contains_none(Keys... ks) noexcept { return !contains_any(ks...); }

    using Options::fetch...;

    //! @related rbr::settings
    //! @brief Output stream insertion
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, settings const& s)
    {
      os << "{\n";
      ((os << "  " << static_cast<Options const&>(s) << "\n"),...);
      return os << "}";
    }

    private:
    // Automatically unpack reference_wrapper to actual reference
    template<typename K>
    constexpr decltype(auto) unwrap(K const& key) const
    {
      auto v = [&]()  { if constexpr(requires{ fetch(key); }) return fetch(key);
                        else                                  return unknown_key{};
                      }();
      return std::unwrap_reference_t<decltype(v)>(v);
    };
  };

  /// rbr::settings deduction guide
  template<concepts::option... Opts>
  settings(Opts const&... opts) -> settings<Opts...>;
}
