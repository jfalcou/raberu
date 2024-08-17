//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <raberu/impl/helpers.hpp>

//======================================================================================================================
// ## RABERU Options & Keywords
//======================================================================================================================
namespace rbr
{
  template<typename Type> struct only_t
  {
    template<typename U>
    static constexpr bool value = stdfix::same_as<Type,U>;
  };

  template<template<class> typename Traits> struct traits_check
  {
    template<typename U>
    static constexpr bool value = Traits<U>::value;
  };

  struct unknown_key
  {
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, unknown_key const&)
    {
      return os << "rbr::unknown_key";
    }
  };

  template<typename Type>
  inline constexpr only_t<Type> only = {};

  template<template<class> typename Traits>
  inline constexpr traits_check<Traits> if_ = {};

  //====================================================================================================================
  //! @ingroup stng
  //! @brief Callable object wrapper for functional default value
  //! @tparam Keyword Keyword for the option
  //! @tparam Value   Value stored in the option
  //====================================================================================================================
  template<typename Keyword, typename Value>
  struct option
  {
    /// Keyword identifier type
    using keyword_type      = typename Keyword::keyword_identifier;

    /// Type of the internal value carried over by the option
    using stored_value_type = Value;

    constexpr decltype(auto)  fetch(keyword_type const&) &      noexcept { return payload;            }
    constexpr decltype(auto)  fetch(keyword_type const&) &&     noexcept { return std::move(payload); }
    constexpr decltype(auto)  fetch(keyword_type const&) const& noexcept { return payload;            }

    //! @related rbr::option
    //! @brief Output stream insertion
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, option const& o)
    {
      if constexpr( requires{ display(os, Keyword{}, o.payload); } )
        return display(os, Keyword{}, o.payload);
      else
        return os << Keyword{} << " : " << o.payload << " (" << _::type<std::unwrap_ref_decay_t<Value>> << ")";
    }

    Value payload;
  };

  template<typename ID, typename Check = void> struct keyword;

  template<typename ID, typename Default>
  struct keyword_or
  {
    using keyword_identifier = typename ID::keyword_identifier;
    static constexpr bool is_flag = ID::is_flag;

    template<typename Value>
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const { return {RBR_FWD(v)}; }

    template<typename S>
    constexpr decltype(auto) default_value(S const& s) const noexcept
    {
      if constexpr(std::invocable<Default, S>)  return default_(s);
      else                                      return default_;
    }

    constexpr bool operator==(keyword_or const&) const = default;

    Default default_;
  };

  template<typename ID>
  struct keyword<ID,void>
  {
    using keyword_identifier = keyword<ID>;
    static constexpr bool is_flag = false;

    constexpr keyword() noexcept {}
    constexpr keyword(ID const&) noexcept {}

    template<typename Value>
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const { return {RBR_FWD(v)}; }

    template<typename Default>
    constexpr auto operator|(Default v) const noexcept { return keyword_or<keyword_identifier,Default>{std::move(v)}; }

    constexpr bool operator==(keyword const&) const = default;

    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, keyword const&)
    {
      if constexpr(requires{ os << ID{}; }) return os << ID{};
      else                                  return os << _::type<ID>;
    }
  };

  //====================================================================================================================
  //! @ingroup kwds
  //! @brief Base class for keyword definition
  //!
  //! rbr::keyword
  //!
  //! @tparam ID    Keyword type being defined
  //! @tparam Check Potential type checker meta-function. By default, this is `void` to notify no checks.
  //====================================================================================================================  template<typename ID>
  template<typename ID, typename Checker>
  struct keyword
  {
    using keyword_identifier = keyword<ID>;
    static constexpr bool is_flag = false;

    constexpr keyword() noexcept {}
    constexpr keyword(ID const&, Checker const&) noexcept {}

    constexpr bool operator==(keyword const&) const = default;

    //==================================================================================================================
    //! @brief Assignment of a value to a keyword
    //!
    //! Bind a value to current [Keyword](@ref rbr::concepts::keyword) and returns an instance of
    //! an [Option](@ref rbr::concepts::option).
    //!
    //! @param v Bound value
    //! @return An rbr::option binding the keyword to `v`.
    //==================================================================================================================
    template<typename Value>
    requires( Checker::template value<Value> )
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const { return {RBR_FWD(v)}; }

    template<typename Value>
    requires( !Checker::template value<Value> )
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const =delete;

    template<typename Default>
    constexpr auto operator|(Default v) const  { return keyword_or<keyword_identifier,Default>{std::move(v)}; }

    //! @related rbr::keyword
    //! @brief Output stream insertion
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, keyword const&)
    {
      if constexpr(requires{ os << ID{}; }) return os << ID{};
      else                                  return os << _::type<ID>;
    }
  };

  template<typename ID>
  keyword(ID const&) -> keyword<ID,void>;

  template<typename ID, typename Checker>
  keyword(ID const&, Checker const&) -> keyword<ID,Checker>;

//====================================================================================================================
  //! @ingroup kwds
  //! @brief Flag keyword
  //!
  //! A Flag keyword is a keyword which value is given by its mere presence. It accepts no binding
  //! and return a value convertible to `bool` when set in a rbr::settings.
  //!
  //! By design, a flag is also its own rbr::option.
  //!
  //! @tparam ID    Unique identifier for the keyword
  //====================================================================================================================
  template<typename ID>
  struct flag
  {
    using keyword_identifier      = flag<ID>;
    using keyword_type            = flag<ID>;
    using stored_value_type       = bool;
    static constexpr bool is_flag = true;

    constexpr flag() noexcept {}
    constexpr flag(ID const&) noexcept {}

    constexpr bool  fetch(keyword_identifier const&)  const noexcept { return true; }

    template<typename S>
    constexpr bool default_value(S const&) const noexcept { return false; }

    constexpr flag operator=(auto const&) const { return {}; }

    template<typename Default>
    constexpr auto operator|(Default v) const  { return keyword_or<keyword_identifier,Default>{std::move(v)}; }

    //! @related rbr::flag
    //! @brief Output stream insertion
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, flag const&)
    {
      if constexpr(requires{ os << ID{}; }) return os << ID{} << " : set";
      else                                  return os << _::type<ID> << " : set";
    }
  };

  inline namespace literals
  {
    //! @related rbr::keyword
    //! @brief User-defined literal for keyword specification
    template<str ID>
    constexpr auto operator""_kw() noexcept { return keyword<id_<ID>>{}; }

    //! @related rbr::flag
    //! @brief User-defined literal for flag specification
    template<str ID>
    constexpr auto operator""_fl() noexcept { return flag<id_<ID>>{}; }
  }
}
