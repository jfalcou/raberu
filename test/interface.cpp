//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <tts/tts.hpp>
#include <raberu.hpp>
#include "common.hpp"

template<typename... Vs>
constexpr auto typed_interface(Vs const&... vs ) noexcept
{
  rbr::settings s(vs...);
  return s[rbr::keyword<int>] * s[rbr::keyword<double>];
}

template<typename... Vs>
constexpr auto named_interface(Vs const&... vs ) noexcept
{
  rbr::settings s(vs...);
  return s[factor_] * s[ref_];
}

TTS_CASE("Check settings(...) as function interface with simple parameters")
{
  TTS_EQUAL( typed_interface(10  , 3.41), 34.1 );
  TTS_EQUAL( typed_interface(3.41, 10  ), 34.1 );
}

TTS_CASE("Check settings(...) as function interface with named parameters")
{
  TTS_EQUAL( named_interface( factor_ = 10  , ref_    = 3.41 ), 34.1 );
  TTS_EQUAL( named_interface( ref_    = 3.41, factor_ = 10   ), 34.1 );
}

TTS_CASE("Check settings(...) as constexpr function interface with simple parameters")
{
  TTS_EXPECT( bool_< typed_interface(10  , 3.41) == 34.1>::value );
  TTS_EXPECT( bool_< typed_interface(3.41, 10  ) == 34.1>::value );
}

TTS_CASE("Check settings(...) as constexpr function interface with named parameters")
{
  TTS_EXPECT( bool_< named_interface( factor_ = 10  , ref_    = 3.41 ) == 34.1>::value );
  TTS_EXPECT( bool_< named_interface( ref_    = 3.41, factor_ = 10   ) == 34.1>::value );
}
