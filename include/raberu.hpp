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
#include <optional>
#include <utility>

namespace rbr
{
  //==============================================================================================
  // Turn any type into a RegularType info carrier
  //==============================================================================================
  template<typename T> struct type_
  {
    using type = type_<T>;
    template<typename V> constexpr auto operator=(V&& v) const noexcept;
  };
}

namespace rbr::detail
{
  //================================================================================================
  // Turn a Type+Value pair into a Callable
  //================================================================================================
  template<typename Callable> struct typed_value : Callable
  {
    constexpr typed_value( Callable f) noexcept : Callable(f) {}
    using Callable::operator();
  };

  //================================================================================================
  // Build the type->value lambda capture
  //================================================================================================
  template<typename Key, typename Value> constexpr auto link(Value v) noexcept
  {
    return typed_value( [v](Key const&) constexpr { return v; } );
  }

  //================================================================================================
  // Type notifying that we can't find a given key
  //================================================================================================
  struct unknown_key {};

  template<typename T> inline constexpr bool is_unknown_v              = false;
  template<>           inline constexpr bool is_unknown_v<unknown_key> = true;

  //================================================================================================
  // Aggregate lambdas and give them a operator(Key)-like interface
  //================================================================================================
  template<typename... Ts> struct aggregator : Ts...
  {
    constexpr aggregator(Ts... t) noexcept : Ts(t)... {}

    using Ts::operator()...;

    template<typename K> constexpr auto operator()(type_<K> const&) const noexcept
    {
      return unknown_key{};
    }

    template<typename K, typename U>
    constexpr decltype(auto) value_or(type_<K> const& k, U&& u) const noexcept
    {
      using found = decltype(this->operator()(type_<K>{}));
      if constexpr( is_unknown_v<found> ) return std::forward<U>(u);
      else                                return this->operator()(k);
    }
  };
}

namespace rbr
{
  //================================================================================================
  // Extract tag from an Option
  //================================================================================================
  template<typename T>
  template<typename V> constexpr auto type_<T>::operator=(V&& v) const noexcept
  {
    return detail::link<type_<T>>(std::forward<V>(v));
  }

  //================================================================================================
  // Extract tag from an Option
  //================================================================================================
  template<typename O> struct tag
  {
    using type = type_<O>;
  };

  template<typename O> using tag_t = typename tag<O>::type;
}

//==================================================================================================
// Tag macro
//==================================================================================================
#define RBR_NAMED_PARAMETER(TAG,NAME) inline constexpr ::rbr::type_<TAG> const NAME = {}

namespace rbr
{
  //==================================================================================================
  // settings is an unordered set of values accessible via their types
  //==================================================================================================
  template<typename... Ts> struct settings
  {
    using parent = detail::aggregator<detail::typed_value<Ts>...>;

    constexpr settings( detail::typed_value<Ts>... ts )
            : content_( ts... )
    {}

    template<typename... Vs>
    constexpr settings( Vs&&... v )
            : content_( detail::link<tag_t<std::decay_t<Vs>>>( std::forward<Vs>(v))... )
    {}

    static constexpr std::ptrdiff_t size() noexcept { return sizeof...(Ts); }

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
      return content_.value_or(tag_t<T>{}, std::forward<Value>(v));
    }

    template<typename T, typename Callable>
    constexpr decltype(auto) get_or_eval(Callable f) const noexcept
    {
      if constexpr( contains<T>() ) return get<T>();
      else                          return f( type_<T>{} );
    }

    template<typename T> constexpr auto maybe_get() const noexcept
    {
      if constexpr( contains<T>() ) return std::optional{get<T>()};
      else                          return std::optional<detail::unknown_key>{};
    }

    parent content_;
  };

  template<typename... Vs>
  settings( Vs&&... v ) ->  settings< decltype( detail::link< tag_t<std::decay_t<Vs>>  >
                                                            ( std::forward<Vs>(v) )
                                              )...
                                    >;

  //================================================================================================
  // Free function helpers
  //================================================================================================
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
