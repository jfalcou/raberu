//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <cstddef>
#include <type_traits>
#include <ostream>

//======================================================================================================================
//! @namespace rbr::concepts
//! @brief Raberu Concepts namespace
//======================================================================================================================
namespace rbr::concepts
{
  //====================================================================================================================
  //! @brief Keyword concept
  //!
  //! A Keyword type is able to be bound to a value as an [Option](@ref rbr::concepts::option)
  //====================================================================================================================
  template<typename K> concept keyword = requires( K k )
  {
    typename K::tag_type;
    { K::template accept<int>() } -> stdfix::same_as<bool>;
  };

  //====================================================================================================================
  //! @brief Option concept
  //!
  //! An Option type can be aggregated in a [Settings](@ref rbr::concepts::settings) and be
  //! fetched later
  //====================================================================================================================
  template<typename O> concept option = requires( O const& o )
  {
    { o(typename std::remove_cvref_t<O>::keyword_type{}) }
    -> stdfix::same_as<typename std::remove_cvref_t<O>::stored_value_type>;
  };

  //====================================================================================================================
  //! @brief Settings concept
  //!
  //! A Settings is a group of [Options](@ref rbr::concepts::option)
  //====================================================================================================================
  template<typename S> concept settings = requires( S const& s )
  {
    typename S::rbr_settings;
  };

  //====================================================================================================================
  //! @brief Exact match concept helper
  //!
  //! rbr::concepts::exactly is to be used to constraint functions template parameter to be an
  //! instantiation of a precise [Keyword](@ref rbr::concepts::keyword)
  //====================================================================================================================
  template<typename Option, auto Keyword>
  concept exactly = stdfix::same_as < typename Option::keyword_type
                                    , std::remove_cvref_t<decltype(Keyword)>
                                    >;
}

// Internal concepts
namespace rbr::_
{
  // Check for check()
  template<typename K, typename T>
  concept checks_for = requires(K)
  {
    { K::template check<T>() };
  };

  // Checks for identifier
  template<typename T>
  concept identifiable = requires(T t)
  {
    { t.identifier };
  };

  // Checks for identifier
  template<typename T>
  concept self_identifiable = requires(T t, std::ostream& os)
  {
    { os << t };
  };

  // Checks for display
  template<typename T, typename V>
  concept displayable = requires(T t, std::ostream& os, V v)
  {
    { t.display(os,v) };
  };

  // Concept to constraint size
  template<std::size_t N, std::size_t M>
  concept fits = (N <= M);
}
