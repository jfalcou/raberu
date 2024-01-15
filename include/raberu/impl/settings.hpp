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

#pragma once

namespace rbr
{
  template<concepts::option... Options>
  struct settings : private Options...
  {
    using rbr_settings = void;

    static constexpr std::ptrdiff_t 	size () noexcept { return sizeof...(Options); }

    constexpr explicit(sizeof...(Options) == 1)
    settings(Options... opts) : Options(std::move(opts))... {}

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

    template<concepts::keyword... Keys>
    static constexpr auto contains_any(Keys... ks) noexcept { return (contains(ks) || ...); }

    template<concepts::keyword... Keys>
    static constexpr auto contains_only([[maybe_unused]] Keys const&... ks) noexcept
    {
      using current_keys    = _::keys<typename Options::keyword_type::keyword_identifier...>;
      using acceptable_keys = _::keys<typename Keys::keyword_identifier...>;
      using unique_set      = typename _::uniques<current_keys,acceptable_keys>::type;
      return  _::is_equivalent<unique_set, acceptable_keys>::value;
    }

    template<concepts::keyword... Keys>
    static constexpr auto contains_none(Keys... ks) noexcept { return !contains_any(ks...); }

    using Options::fetch...;

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
}
