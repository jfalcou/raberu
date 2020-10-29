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

//==================================================================================================
// Optional support for exception
//==================================================================================================
#if !defined(RABERU_NOEXCEPT)
#include <stdexcept>

namespace rbr
{
  //================================================================================================
  // Exception thrown when an unknown option is used
  //================================================================================================
  struct unknown_option_exception : virtual std::exception
  {
    virtual const char* what() const noexcept
    {
      return "[raberu] Exception - Attempt to retrieve unknown option from settings";
    }
  };
}
#else
namespace rbr
{
  //================================================================================================
  // Exception thrown when an unknown option is used
  //================================================================================================
  struct unknown_option_exception
  {
    const char* what() const noexcept { return nullptr; }
  };
}
#endif

//==================================================================================================
// Tag mechanism
//==================================================================================================
namespace rbr
{
  //================================================================================================
  // Extract tag from an Option
  //================================================================================================
  template<typename O> struct tag;

  template<typename O> requires requires { typename O::option_tag; }
  struct tag<O>
  {
    using type = typename O::option_tag;
  };

  template<typename O> using tag_t = typename tag<O>::type;

  //================================================================================================
  // Concept for options
  //================================================================================================
  template<typename Option> concept option = requires(Option o)
  {
    typename tag<Option>::type;
  };

  namespace detail
  {
    //==============================================================================================
    // Turn any type into a RegularType info carrier
    //==============================================================================================
    template<typename T> struct box { using type = box<T>; };
  }

  //================================================================================================
  // User-facing helper to build option type
  //================================================================================================
  template<typename T> using option_ = detail::box<T>;
}

//==================================================================================================
// Implementation elements
//==================================================================================================
namespace rbr::detail
{
  //================================================================================================
  // Turn a Type+Value pair into a Callable
  //================================================================================================
  template<typename Callable>
  struct typed_value : Callable
  {
    constexpr typed_value( Callable f) noexcept : Callable(f) {}
    using Callable::operator();
  };

  template<typename Callable> typed_value(Callable) -> typed_value<Callable>;

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
  struct unknown_option {};

  template<typename T> inline constexpr bool is_unknown_v                 = false;
  template<>           inline constexpr bool is_unknown_v<unknown_option> = true;

  //================================================================================================
  // Aggregate lambdas and give them a operator(Key)-like interface
  //================================================================================================
  template<typename... Ts> struct aggregator : Ts...
  {
    constexpr aggregator(Ts... t) noexcept : Ts(t)... {}

    using Ts::operator()...;

    template<typename K> constexpr auto operator()(box<K> const&) const noexcept
    {
      return unknown_option{};
    }

    template<typename K, typename U>
    constexpr decltype(auto) value_or(box<K> const& k, U&& u) const noexcept
    {
      // If calling without default would return the key, use the default
      using found = decltype(this->operator()(box<K>{}));

      if constexpr( is_unknown_v<found> ) return std::forward<U>(u);
      else                                return this->operator()(k);
    }
  };

  template<typename... Ts> aggregator(Ts...) -> aggregator<Ts...>;
}

//==================================================================================================
  // settings is an unordered set of value accessible via their type
//==================================================================================================
namespace rbr
{
  template<typename... Ts>
  struct settings : private detail::aggregator< detail::typed_value<Ts>...>
  {
    using parent = detail::aggregator<detail::typed_value<Ts>...>;

    constexpr settings(detail::typed_value<Ts>&&... opts) : parent(std::forward<Ts>(opts)...)
    {}

    template<option... Os>
    constexpr settings( Os&&... opts )
            : settings( detail::link< tag_t<std::decay_t<Os>> >( std::forward<Os>(opts))... )
    {}

    template<option Option> constexpr auto get() const noexcept
    {
      return parent::operator()(tag_t<Option>{});
    }

    template<option Option> constexpr std::optional<Option> maybe_get() const noexcept
    {
      return parent::value_or(tag_t<Option>{}, std::nullopt);
    }

    template<option Option> auto try_get() const
    {
      #if !defined(RABERU_NOEXCEPT)
      using tag = tag_t<Option>;
      using found = decltype(this->operator()(tag{}));

      if constexpr( detail::is_unknown_v<found> ) throw unknown_option_exception{};
      else                                        return get<Option>();
      #else
      return get<Option>();
      #endif
    }

    template<option Option, typename Value> constexpr auto get_or(Value&& v) const noexcept
    {
      return parent::value_or(tag_t<Option>{}, std::forward<Value>(v));
    }

    template<option Option, typename Callable> constexpr auto get_or_eval(Callable f) const noexcept
    {
      using tag = tag_t<Option>;
      using found = decltype(this->operator()(tag{}));

      if constexpr( detail::is_unknown_v<found> ) return f();
      else                                        return get<Option>();
    }
  };

  template<option... Os>
  settings( Os&&... opts ) -> settings< decltype( detail::link< tag_t<std::decay_t<Os>> >
                                                              ( std::forward<Os>(opts) )
                                                )...
                                      >;
}
