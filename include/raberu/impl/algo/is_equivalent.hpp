//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <raberu/impl/algo/keys_values.hpp>

namespace rbr
{
  //====================================================================================================================
  //! @ingroup stng
  //! @brief Checks the equivalence of two rbr::settings
  //!
  //! Two rbr::settings are equivalent if they contain the same exact set of keywords irregardless
  //! of their values or value types.
  //!
  //! @tparam S1 rbr::settings to compare
  //! @tparam S2 rbr::settings to compare
  //!
  //! ## Helper Value
  //! @code
  //! namespace rbr
  //! {
  //!   template<concepts::settings S1, concepts::settings S2>
  //!   inline constexpr bool is_equivalent_v = is_equivalent<S1,S2>::value;
  //! }
  //! @endcode
  //!
  //! Contains the result of a call to rbr::is_equivalent.
  //!
  //! ## Example:
  //! @include doc/is_equivalent.cpp
  //====================================================================================================================
  template<concepts::settings S1, concepts::settings S2>
  struct  is_equivalent
        : std::bool_constant<   _::is_equivalent< result::keywords_t<S1,_::keys>
                                                , result::keywords_t<S2,_::keys>
                                                >::value
                            &&  _::is_equivalent< result::keywords_t<S2,_::keys>
                                                , result::keywords_t<S1,_::keys>
                                                >::value
                            >
  {};

  template<concepts::settings S1, concepts::settings S2>
  inline constexpr bool is_equivalent_v = is_equivalent<S1,S2>::value;
}
