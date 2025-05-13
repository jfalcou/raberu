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

  //====================================================================================================================
  //! @ingroup stng
  //! @brief Type indicating a keyword was not found in a given rbr::settings
  //====================================================================================================================
  struct unknown_key
  {
    //! Stream insertion operator
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, unknown_key const&) { return os << "rbr::unknown_key"; }
  };

  //====================================================================================================================
  //! @ingroup stng
  //! @brief  Option specifying the single type a keyword will accept.
  //! @tparam Type Type that the parametrized keyword will accept.
  //!
  //! @groupheader{Example}
  //! @include doc/only.cpp
  //====================================================================================================================
  template<typename Type>
  inline constexpr only_t<Type> only = {};

  //====================================================================================================================
  //! @ingroup stng
  //! @brief  Option specifying a traits that type should verify for being used as a keyword value.
  //! @tparam Traits Traits that the parametrized keyword will use to validate its value.
  //!
  //! @groupheader{Example}
  //! @include doc/checked.cpp
  //====================================================================================================================
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

    constexpr bool operator==(keyword_or const& s) const
    {
      return default_ = s.default_;
    }

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
  //! @brief Keyword definition class
  //!
  //! rbr::keyword defines a keyword, i.e an entity that can receive values and can be stored as part of a settings.
  //! It is defined by a unique type ID which can be an actual type or generated from rbr::id_ and an optional
  //! checking operations that will validate the value passed to the keyword is acceptable.
  //!
  //! rbr::keyword can also be used to define custom keyword type with specific behavior.
  //!
  //! @tparam ID    Keyword type being defined
  //! @tparam Check Potential type checker meta-function. By default, this is `void` to notify no check is performed.
  //!
  //! @groupheader{Example}
  //! @include doc/regular.cpp
  //!
  //====================================================================================================================
  template<typename ID, typename Checker>
  struct keyword
  {
    //! Keyword identifier type. This type can be used to identify a keyword in generic contexts.
    using keyword_identifier = keyword<ID>;

    //! Indicates that if the current keyword behaves as a flag.
    static constexpr bool is_flag = false;

    //! Default constructor
    constexpr keyword() noexcept {}

    //==================================================================================================================
    //! @brief Constructs a keyword from an ID and a checker type.
    //!
    //! @param id   Identifier of the keyword.
    //! @param chk  Object performing the compile-time verification of the keyword's value.
    //!
    //! @groupheader{Example}
    //! @include doc/only.cpp
    //==================================================================================================================
    constexpr keyword([[maybe_unused]] ID const& id, [[maybe_unused]] Checker const& chk) noexcept {}

    //! Equality comparison
    constexpr bool operator==(keyword const&) const = default;

    //==================================================================================================================
    //! @brief Assignment of a value to a keyword
    //!
    //! Bind a value to current [Keyword](@ref rbr::concepts::keyword) and returns an instance of
    //! an [Option](@ref rbr::concepts::option).
    //!
    //! @param v Bound value
    //! @return An rbr::option binding the keyword to `v`.
    //!
    //! @groupheader{Example}
    //! @code
    //! #include <raberu/raberu.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   using namespace rbr::literals;
    //!   std::cout << ("value"_kw = 42.1337) << "\n";
    //! }
    //! @endcode
    //==================================================================================================================
    template<typename Value>
    requires( Checker::template value<Value> )
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const { return {RBR_FWD(v)}; }

    template<typename Value>
    requires( !Checker::template value<Value> )
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const =delete;

    //==================================================================================================================
    //! @brief Add a default value to current keyword
    //!
    //! Create a keyword instance with the same identifier as the current one but carrying `v` as a default value.
    //! `v` is stored so it can be fetched later via rbr::settings if no keyword of the given identifier is found.
    //!
    //! @param v  Default value.
    //! @see rbr::settings
    //! @see rbr::fetch
    //==================================================================================================================
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
    //! Keyword identifier type. This type can be used to identify a keyword in generic contexts.
    using keyword_identifier      = flag<ID>;

    //! Keyword type used to generate this option.
    using keyword_type            = flag<ID>;

    //! Type of the internal value carried over by the flag.
    using stored_value_type       = bool;

    //! Indicates that if the current keyword behaves as a flag.
    static constexpr bool is_flag = true;

    //! Default constructor
    constexpr flag() noexcept {}

    //! Constructs a flag from an ID
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
