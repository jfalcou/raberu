//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <type_traits>
#include <utility>

namespace rbr
{
  // Lightweight container of value
  template<typename T, typename V> struct type_or_ { V value; };

  // Turn any type into a RegularType info carrier
  template<typename T> struct type_t
  {
    using type        = type_t<T>;
    template<typename V> constexpr auto operator=(V&& v) const noexcept;
    template<typename V> constexpr auto operator|(V&& value) const noexcept
    {
      return type_or_<T,V>{std::forward<V>(value)};
    }
  };

  template<typename T> inline constexpr type_t<T> type_ = {};

  namespace detail
  {
    // Turn a Type+Value pair into a Callable
    template<typename Callable> struct linked_value : Callable
    {
      constexpr linked_value( Callable f) noexcept : Callable(f) {}
      using Callable::operator();
    };

    // Build the type->value lambda capture
    template<typename Key, typename Value> constexpr auto link(Value v) noexcept
    {
      return linked_value( [v](Key const&) constexpr { return v; } );
    }

    // Type notifying that we can't find a given key
    struct unknown_key { template<typename... T> unknown_key(T&&...) {} };

    // Check if the key we used is correct
    template<typename T> inline constexpr bool is_unknown_v              = false;
    template<>           inline constexpr bool is_unknown_v<unknown_key> = true;

    // Aggregate lambdas and give them a operator(Key)-like interface
    template<typename... Ts> struct aggregator : Ts...
    {
      constexpr aggregator(Ts... t) noexcept : Ts(t)... {}
      using Ts::operator()...;

      template<typename K> constexpr auto operator()(type_t<K> const&) const noexcept
      {
        // If not found before, return the unknown_key value
        return unknown_key{};
      }
    };
  }

  // Build a key-value from an option object
  template<typename T>
  template<typename V> constexpr auto type_t<T>::operator=(V&& v) const noexcept
  {
    return detail::link<type_t<T>>(std::forward<V>(v));
  }

  // Extract tag from an Option
  template<typename O> struct tag { using type = type_t<O>; };
  template<typename O> using  tag_t = typename tag<O>::type;

  // settings is an unordered set of values accessible via their types
  template<typename... Ts> struct settings
  {
    using parent = detail::aggregator<detail::linked_value<Ts>...>;

    constexpr settings( detail::linked_value<Ts>... ts ) : content_( ts... ) {}

    template<typename... Vs>
    constexpr settings( Vs&&... v )
            : content_( detail::link<tag_t<std::decay_t<Vs>>>( std::forward<Vs>(v))... )
    {}

    static constexpr std::ptrdiff_t size() noexcept { return sizeof...(Ts); }

    // Type based interface
    template<typename T> static constexpr bool contains() noexcept
    {
      using found = decltype(std::declval<parent>()(tag_t<T>{}));
      return !detail::is_unknown_v<found>;
    }

    template<typename T> constexpr auto get() const noexcept
    {
      return content_(tag_t<T>{});
    }

    template<typename T, typename Value> constexpr auto get_or(Value&& v) const noexcept
    {
      if constexpr( contains<T>() ) return get<T>();
      else                          return std::forward<Value>(v);
    }

    template<typename T, typename Callable>
    constexpr decltype(auto) get_or_eval(Callable f) const
    {
      if constexpr( contains<T>() ) return get<T>();
      else                          return f( type_t<T>{} );
    }

    // Named options interface
    template<typename T> static constexpr bool contains(type_t<T> const&) noexcept
    {
      return contains<T>();
    }

    template<typename T>
    constexpr auto operator[](T const& tgt) const noexcept { return content_(tgt); }

    template<typename T, typename V>
    constexpr auto operator[](type_or_<T,V> const& tgt) const
    {
      if constexpr( std::is_invocable_v<V,type_t<T>> ) return get_or_eval<T>(tgt.value);
      else                                             return get_or<T>(tgt.value);
    }

    parent content_;
  };

  template<typename... Vs>
  settings( Vs&&... v ) ->  settings< decltype( detail::link< tag_t<std::decay_t<Vs>>  >
                                                            ( std::forward<Vs>(v) )
                                              )...
                                    >;

  // Free function helpers
  template<typename T, typename... Vs>
  constexpr std::ptrdiff_t size(settings<Vs...> const&) noexcept
  {
    return sizeof...(Vs);
  }

  template<typename T, typename... Vs>
  constexpr bool contains(settings<Vs...> const& s) noexcept
  {
    return s.template contains<T>();
  }

  template<typename T, typename... Vs>
  constexpr auto get(settings<Vs...> const& s) noexcept
  {
    return s.template get<T>();
  }

  template<typename T, typename V, typename... Vs>
  constexpr auto get_or(settings<Vs...> const& s, V&& v) noexcept
  {
    return s.template get_or<T>(std::forward<V>(v));
  }

  template<typename T, typename Callable, typename... Vs>
  constexpr decltype(auto) get_or_eval(settings<Vs...> const& s,Callable f) noexcept
  {
    return s.template get_or_eval<T>(f);
  }

  template<typename T, typename... Vs> constexpr auto maybe_get(settings<Vs...> const& s) noexcept
  {
    return s.template maybe_get<T>();
  }
}
