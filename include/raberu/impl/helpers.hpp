//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <type_traits>
#include <concepts>

//======================================================================================================================
//! @namespace rbr
//! @brief Main Raberu namespace
//======================================================================================================================
namespace rbr
{
  //======================================================================================================================
  //! @defgroup main Main RABERU components
  //! @{
  //!   @defgroup kwds Keywords definitions and handling
  //!   @brief    Functions and types to handle RABERU keywords
  //! @}
  //======================================================================================================================

  //====================================================================================================================
  //! @namespace rbr::result
  //! @brief Raberu helper traits namespace
  //====================================================================================================================
  namespace result {}
}

//======================================================================================================================
//! @defgroup utility   Helper types and function
//! @brief    Tools for interacting with RABERU components
//======================================================================================================================

#define RBR_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

// Helpers for working on list of keys as unique lists - needed by merge and some contains_*
namespace rbr::_
{
  template<typename... Ks> struct keys {};

  template<typename K, typename Ks> struct contains;

  template<typename... Ks, typename K>
  struct  contains<K, keys<Ks...>> : std::bool_constant<(std::same_as<K,Ks> || ...)>
  {};

  template<typename K, typename Ks, bool>  struct append_if_impl;

  template<typename... Ks, typename K> struct append_if_impl<K,keys<Ks...>,true>
  {
    using type = keys<Ks...>;
  };

  template<typename... Ks, typename K> struct append_if_impl<K,keys<Ks...>,false>
  {
    using type = keys<Ks...,K>;
  };

  template<typename K, typename Ks> struct append_if;

  template<typename K, typename Ks>
  struct append_if : append_if_impl<K,Ks, contains<K, Ks>::value>
  {};

  template<typename K1, typename K2> struct uniques;

  template<typename K1s, typename K2, typename... K2s>
  struct  uniques<K1s, keys<K2,K2s...>>
        : uniques< typename append_if<K2,K1s>::type, keys<K2s...> >
  {};

  template<typename K1s> struct  uniques<K1s, keys<>> { using type = K1s; };

  template<typename K1, typename K2> struct contain_all;

  template<typename K1s, typename... K2s>
  struct  contain_all<K1s, keys<K2s...>> : std::bool_constant<(contains<K2s,K1s>::value && ...)>
  {};

  template<typename K1s>  struct  contain_all<K1s   , keys<>>  : std::false_type {};
  template<typename K2s>  struct  contain_all<keys<>, K2s   >  : std::false_type {};
  template<>              struct  contain_all<keys<>,keys<>>   : std::true_type  {};

  template<typename K1, typename K2>
  struct is_equivalent : std::bool_constant<contain_all<K2,K1>::value && contain_all<K2,K1>::value>
  {};
}

namespace rbr
{
  //====================================================================================================================
  //! @ingroup utility
  //! @brief Lightweight variadic type list
  //====================================================================================================================
  template<typename... T> struct types {};
}
