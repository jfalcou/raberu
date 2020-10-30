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

TTS_CASE("Check settings(...) maybe_get behavior")
{
  auto values = rbr::settings(1337.42);

  TTS_EXPECT_NOT( maybe_get<char>  (values)          );
  TTS_EXPECT_NOT( maybe_get<float> (values)          );
  TTS_EXPECT    ( maybe_get<double>(values)          );
  TTS_EQUAL     (*maybe_get<double>(values), 1337.42 );
}

TTS_CASE("Check settings(...) maybe_get constexpr behavior")
{
  constexpr auto values = rbr::settings(1337.42);

  TTS_EXPECT_NOT( bool_< maybe_get<char>  (values).has_value()>::value);
  TTS_EXPECT_NOT( bool_< maybe_get<float> (values).has_value()>::value);
  TTS_EXPECT    ( bool_< maybe_get<double>(values).has_value()>::value);
  TTS_EXPECT    ( bool_<*maybe_get<double>(values) == 1337.42 >::value);
}

template<typename... Vs>
constexpr auto interface(Vs const&... vs ) noexcept
{
  rbr::settings s(vs...);
  return rbr::get<int>(s) * rbr::get<double>(s);
}

TTS_CASE("Check settings(...) as function interface")
{
  TTS_EQUAL( interface(10  , 3.41), 34.1 );
  TTS_EQUAL( interface(3.41, 10  ), 34.1 );
}

TTS_CASE("Check settings(...) as constexpr function interface")
{
  TTS_EXPECT( bool_< interface(10  , 3.41) == 34.1>::value );
  TTS_EXPECT( bool_< interface(3.41, 10  ) == 34.1>::value );
}
