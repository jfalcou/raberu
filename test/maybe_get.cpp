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

TTS_CASE("Check settings(...) maybe_get behavior - simple parameters")
{
  auto values = rbr::settings(1337.42);

  TTS_EXPECT_NOT( maybe_get<char>  (values)          );
  TTS_EXPECT_NOT( maybe_get<float> (values)          );
  TTS_EXPECT    ( maybe_get<double>(values)          );
  TTS_EQUAL     (*maybe_get<double>(values), 1337.42 );
}

TTS_CASE("Check settings(...) maybe_get behavior - named parameters")
{
  auto values = rbr::settings( coord_ = 8.84 );

  TTS_EXPECT_NOT( maybe_get<char>  (values)           );
  TTS_EXPECT_NOT( maybe_get<float> (values)           );
  TTS_EXPECT    ( maybe_get<coord_tag>(values)        );
  TTS_EQUAL     (*maybe_get<coord_tag>(values), 8.84  );
}

TTS_CASE("Check settings(...) maybe_get constexpr behavior - simple parameters")
{
  constexpr auto values = rbr::settings(1337.42);

  TTS_EXPECT_NOT( bool_< maybe_get<char>  (values).has_value()>::value);
  TTS_EXPECT_NOT( bool_< maybe_get<float> (values).has_value()>::value);
  TTS_EXPECT    ( bool_< maybe_get<double>(values).has_value()>::value);
  TTS_EXPECT    ( bool_<*maybe_get<double>(values) == 1337.42 >::value);
}

TTS_CASE("Check settings(...) maybe_get constexpr behavior - named parameters")
{
  constexpr point p{1,3,5};
  constexpr auto values = rbr::settings( coord_ = p);

  TTS_EXPECT_NOT( bool_< maybe_get<char>  (values).has_value()    >::value);
  TTS_EXPECT_NOT( bool_< maybe_get<float> (values).has_value()    >::value);
  TTS_EXPECT    ( bool_< maybe_get<coord_tag>(values).has_value() >::value);
  TTS_EXPECT    ( bool_<*maybe_get<coord_tag>(values) == p        >::value);
}
