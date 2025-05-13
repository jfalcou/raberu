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
// ## RABERU Concepts
//======================================================================================================================

//======================================================================================================================
//! @namespace rbr::concepts
//! @brief Raberu Concepts namespace
//======================================================================================================================
namespace rbr::concepts
{
  template<typename OS>
  concept stream = requires(OS& os, const char* s) { {os << s}; };

  //====================================================================================================================
  //! @brief Keyword concept
  //!
  //! A Keyword type is able to be bound to a value as an [Option](@ref rbr::concepts::option).
  //====================================================================================================================
  template<typename K>
  concept keyword = requires(K const& k) { typename K::keyword_identifier; };

  //====================================================================================================================
  //! @brief Keyword with Default concept
  //!
  //! A Keyword with Default type is usable when retrieving a settings value and by providing a default value if needed.
  //====================================================================================================================
  template<typename K, typename T>
  concept keyword_with_default = keyword<K> && requires(K const& k, T const d) { { k.default_value(d) }; };

  //====================================================================================================================
  //! @brief Option concept
  //!
  //! An Option type can be aggregated in a [Settings](@ref rbr::concepts::settings) and be fetched later.
  //====================================================================================================================
  template<typename O>
  concept option = requires(O const& o)
  {
    typename O::keyword_type;
    typename O::stored_value_type;
    { o.fetch(typename O::keyword_type{}) };
  };

  //====================================================================================================================
  //! @brief Settings concept
  //!
  //! A Settings is a group of [Options](@ref rbr::concepts::option)
  //====================================================================================================================
  template<typename S> concept settings = requires( S const& s ) { typename S::rbr_settings; };

  //====================================================================================================================
  //! @brief Exact match concept helper
  //!
  //! rbr::concepts::exactly is to be used to constraint functions template parameter to be an
  //! instantiation of a precise [Keyword](@ref rbr::concepts::keyword)
  //====================================================================================================================
  template<typename Option, auto Keyword>
  concept exactly = stdfix::same_as<typename Option::keyword_type, std::remove_cvref_t<decltype(Keyword)>>;
}
