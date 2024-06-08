//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <compare>
#include <ostream>
#include <type_traits>

//======================================================================================================================
//! @defgroup main Main RABERU components
//!
//! @ingroup  main
//! @{
//!   @defgroup kwds Keywords definitions and handling
//!   @brief    Functions and types to handle RABERU keywords
//! @}
//======================================================================================================================
namespace rbr
{
  //====================================================================================================================
  //! @ingroup kwds
  //! @brief Callable object wrapper for functional default value
  //! @tparam Func Callable object to keep
  //====================================================================================================================
  template<typename Func> struct call
  {
    constexpr call(Func f) : callable(f) {}
    constexpr auto perform() const { return callable(); }
    Func callable;
  };

  //====================================================================================================================
  //! @ingroup stng
  //! @brief Callable object wrapper for functional default value
  //! @tparam Keyword Keyword for the option
  //! @tparam Value   Value stored in the option
  //====================================================================================================================
  template<concepts::keyword Keyword, typename Value> struct option
  {
    using stored_value_type = std::decay_t<Value>;
    using keyword_type      = Keyword;

    constexpr stored_value_type operator()(keyword_type const&) const noexcept { return contents; }
    stored_value_type contents;
  };

  //====================================================================================================================
  //! @ingroup kwds
  //! @brief Base class for keyword definition
  //!
  //! rbr::as_keyword provides an CRTP base class for keyword-like types. It is internally used
  //! to provide specific keyword constructors but can be used to define user-defined keyword.
  //!
  //! @tparam Keyword Keyword type being defined
  //====================================================================================================================
  template<typename Keyword> struct as_keyword
  {
    /// Derived keyword type
    using tag_type  = Keyword;

    /// Keyword comparison
    inline constexpr auto operator<=>(as_keyword const&) const noexcept = default;

    //==================================================================================================================
    //! @brief Compile-time validation of value
    //!
    //! When a value is bound to a [Keyword](@ref rbr::concepts::keyword) to form an
    //! [Option](@ref rbr::concepts::option), one can validate this binding by checking arbitrary
    //! properties on the value type. This is done by the accept() member.
    //!
    //! If `Keyword` defines a `check` static template member function, it will be called to provide
    //! the return value of accept(). Otherwise, true is returned, thus automatically validating any
    //! value type.
    //!
    //! @tparam T Type to validate
    //! @return `true` if T is accepted by current keyword, `false` otherwise.
    //!
    //! ## Example:
    //! @snippet doc/accept.cpp Custom Accept
    //==================================================================================================================

    template<typename T>
    static constexpr bool accept()
    {
      if      constexpr(stdfix::same_as<std::remove_cvref_t<T>,as_keyword>)             return true;
      else if constexpr(_::checks_for<Keyword,T>)          return Keyword::template check<T>();
      else                                                                              return true;
    }

    //==================================================================================================================
    //! @brief Assignment of a value to a keyword
    //!
    //! Bind a value to current [Keyword](@ref rbr::concepts::keyword) and returns an instance of
    //! an [Option](@ref rbr::concepts::option).
    //!
    //! @param v Bound value
    //! @return An rbr::option binding the keyword to `v`.
    //==================================================================================================================
    template<typename Type>
    constexpr auto operator=(Type&& v) const noexcept requires( accept<Type>() )
    {
      return option<Keyword,Type>{RBR_FWD(v)};
    }

    //==================================================================================================================
    //! @brief Stream insertion function
    //!
    //! Display a textual description of current keyword and bound value over an output stream.
    //!
    //! If `Keyword` defines a `display` member variable, it will be used to perform this display.
    //! Otherwise, its value will be displayed along with either a user-defined identifier or its
    //! stringified typename.
    //!
    //! @param os Output stream
    //! @param v  Value bound to current keyword
    //! @return The up-to-date output stream
    //!
    //! ## Example:
    //! @snippet doc/show.cpp Custom Show
    //==================================================================================================================
    template<typename V> std::ostream& show(std::ostream& os, V const& v) const
    {
      if constexpr(_::displayable<Keyword,V>) return Keyword{}.display(os,v);
      else
      {
        if constexpr(_::identifiable<Keyword>) os << Keyword::identifier;
        else                                        os << '[' << _::type<Keyword>.name() << ']';

        return os << " : " << v << " (" << _::type<V>.name() << ')';
      }
    }

    /// Specify a default value for the keyword
    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires( accept<Type>() )
    {
      return _::type_or_<Keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    /// Specify a Callable object as a default value for the keyword
    template<typename Func> constexpr auto operator|(call<Func>&& v) const noexcept
    {
      return _::type_or_<Keyword,call<Func>>{RBR_FWD(v)};
    }

    //==================================================================================================================
    //! @brief Keyword fetching from options set
    //!
    //! @param o Set of options to inspect
    //! @return f current keyword is present in `o...`, return its bound value. Otherwise,
    //! returns an instance of rbr::unknown_key.
    //!
    //! ## Example:
    //! @include doc/keyword_fetch.cpp
    //==================================================================================================================
    template<concepts::option... Os>
    constexpr decltype(auto) operator()(Os&&... o) const { return fetch(Keyword{}, RBR_FWD(o)...); }
  };

  //====================================================================================================================
  //! @ingroup kwds
  //! @brief Checked keyword
  //!
  //! A Checked keyword is a keyword that verify if a value's type satisfies a predicates before
  //! binding it
  //!
  //! @tparam ID        Unique identifier for the keyword
  //! @tparam Checker   Unary template meta-function acting as predicate
  //====================================================================================================================
  template<typename ID, template<class> class Checker>
  struct checked_keyword : as_keyword<checked_keyword<ID, Checker>>
  {
    using as_keyword<checked_keyword<ID, Checker>>::operator=;
    template<typename T>  static constexpr bool check() { return Checker<T>::value; }

    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(_::self_identifiable<ID>) os << ID{};
      else
      {
        if constexpr(_::identifiable<ID>) os << ID::identifier;
        else os << '[' << _::type<ID>.name() << ']';
      }

      os << " ::: " << v << " (" << _::type<V>.name() << ") checked by '";
      return os << _::type<Checker<V>>.name() << '\'';
    }
  };

  //====================================================================================================================
  //! @ingroup kwds
  //! @brief Typed keyword
  //!
  //! A Typed keyword is a keyword that verify if a value's type is exactly matching a type.
  //!
  //! @tparam ID    Unique identifier for the keyword
  //! @tparam Type  Type to accept
  //====================================================================================================================
  template<typename ID, typename Type>
  struct typed_keyword  : as_keyword<typed_keyword<ID, Type>>
  {
    using as_keyword<typed_keyword<ID, Type>>::operator=;
    template<typename T>
    static constexpr bool check() { return std::is_same_v<std::remove_cvref_t<T>,Type>; }

    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(_::self_identifiable<ID>) os << ID{};
      else
      {
        if constexpr(_::identifiable<ID>) os << ID::identifier;
        else os << '[' << _::type<ID>.name() << ']';
      }

      return os << " : " << v << " of type '" << _::type<V>.name() << '\'';
    }
  };

  //====================================================================================================================
  //! @ingroup kwds
  //! @brief Regular keyword
  //!
  //! A Regular keyword is a keyword that accepts any types.
  //!
  //! @tparam ID    Unique identifier for the keyword
  //====================================================================================================================
  template<typename ID>
  struct any_keyword   : as_keyword<any_keyword<ID>>
  {
    using as_keyword<any_keyword<ID>>::operator=;

    /// ID type associated to the keyword
    using id_type = ID;

    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(_::self_identifiable<ID>) os << ID{};
      else
      {
        if constexpr(_::identifiable<ID>) os << ID::identifier;
        else os << '[' << _::type<ID>.name() << ']';
      }

      return os << " : " << v << " (" << _::type<V>.name() << ')';
    }
  };

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
  template<typename ID> struct flag_keyword
  {
    constexpr flag_keyword() {}
    constexpr flag_keyword(ID const&) {}

    /// ID type associated to the keyword
    using id_type = ID;

    template<typename T> static constexpr bool accept()
    {
      return std::is_same_v<std::true_type, T>;
    }

    std::ostream& show(std::ostream& os, bool) const
    {
      if constexpr(_::identifiable<ID>) os << ID::identifier;
      else if constexpr(_::self_identifiable<ID>) os << ID{};
      else os << '[' << _::type<ID>.name() << ']';

      return os << " : set";
    }

    using tag_type          = ID;
    using keyword_type      = flag_keyword;
    using stored_value_type = bool;

    template<typename Type>
    constexpr auto operator=(Type&&) const noexcept { return *this; }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept
    {
      return _::type_or_<flag_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Func> constexpr auto operator|(call<Func>&& v) const noexcept
    {
      return _::type_or_<flag_keyword,call<Func>>{RBR_FWD(v)};
    }

    constexpr auto operator()(keyword_type const&) const noexcept { return true; }

    template<typename O0, typename O1, typename... Os>
    constexpr decltype(auto) operator()(O0&&, O1&&, Os&&... ) const
    {
      return    stdfix::same_as<keyword_type, typename std::remove_cvref_t<O0>::keyword_type>
            ||  stdfix::same_as<keyword_type, typename std::remove_cvref_t<O1>::keyword_type>
            || (stdfix::same_as<keyword_type, typename std::remove_cvref_t<Os>::keyword_type> || ...);
    }
  };

  //====================================================================================================================
  //! @ingroup kwds
  //! @related rbr::flag_keyword
  //! @brief Create a flag keyword for reuse
  //! @param  id  Unique rbr::id_ for the keyword being built
  //! @return An instance of rbr::flag_keyword
  //! ## Example:
  //! @include doc/flag.cpp
  //====================================================================================================================
  template<typename Tag>
  constexpr flag_keyword<Tag>  flag([[maybe_unused]] Tag id) noexcept { return {}; }

  //====================================================================================================================
  //! @ingroup kwds
  //! @related rbr::any_keyword
  //! @brief Create a regular keyword for reuse
  //! @param  id  Unique rbr::id_ for the keyword being built
  //! @return An instance of rbr::any_keyword
  //! ## Example:
  //! @include doc/regular.cpp
  //====================================================================================================================
  template<typename ID>
  constexpr any_keyword<ID> keyword([[maybe_unused]] ID id) noexcept { return {}; }

  //====================================================================================================================
  //! @ingroup kwds
  //! @related rbr::checked_keyword
  //! @brief Create a checked keyword for reuse
  //! @tparam Checker Unary template meta-function to use for validation
  //! @param  id  Unique rbr::id_ for the keyword being built
  //! @return An instance of rbr::checked_keyword
  //! ## Example:
  //! @include doc/checked.cpp
  //====================================================================================================================
  template<template<class> class Checker, typename ID>
  constexpr checked_keyword<ID,Checker> keyword([[maybe_unused]] ID id) noexcept { return {}; }

  //====================================================================================================================
  //! @ingroup kwds
  //! @related rbr::typed_keyword
  //! @brief Create a typed Keyword for reuse
  //! @tparam Type Type accepted by the keyword
  //! @param  id  Unique rbr::id_ for the keyword being built
  //! @return An instance of rbr::checked_keyword
  //! ## Example:
  //! @include doc/checked.cpp
  //====================================================================================================================
  template<typename Type, typename ID>
  constexpr typed_keyword<ID, Type> keyword([[maybe_unused]] ID id) noexcept { return {}; }

  namespace literals
  {
    //==================================================================================================================
    //! @ingroup udls
    //! @related rbr::any_keyword
    //! @brief Forms an instance of rbr::any_keyword from a literal string
    //! @return An instance of rbr::any_keyword using the specified string as ID
    //==================================================================================================================
    template<str ID>
    constexpr auto operator""_kw() noexcept { return any_keyword<id_<ID>>{}; }

    //==================================================================================================================
    //! @ingroup udls
    //! @related rbr::flag_keyword
    //! @brief Forms an instance of rbr::flag_keyword from a literal string
    //! @return An instance of rbr::flag_keyword using the specified string as ID
    //==================================================================================================================
    template<str ID>
    constexpr auto operator""_fl() noexcept { return flag_keyword<id_<ID>>{}; }
  }
}
