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

TTS_CASE("Check settings(...) get_or_eval behavior - simple parameters")
{
  auto values = rbr::settings(1337.42);
  auto or_else = []<typename T>(rbr::type_<T>) { return sizeof(T); };

  TTS_EQUAL(get_or_eval<char>  (values, or_else) , 1ULL    );
  TTS_EQUAL(get_or_eval<float> (values, or_else) , 4ULL    );
  TTS_EQUAL(get_or_eval<double>(values, or_else) , 1337.42 );
}

TTS_CASE("Check settings(...) get_or_eval constexpr behavior - simple parameters")
{
  constexpr auto values = rbr::settings(1337.42);
  auto or_else = []<typename T>(rbr::type_<T>) { return sizeof(T); };

  TTS_EXPECT( bool_<get_or_eval<char>  (values, or_else) == 1ULL   >::value );
  TTS_EXPECT( bool_<get_or_eval<float> (values, or_else) == 4ULL   >::value );
  TTS_EXPECT( bool_<get_or_eval<double>(values, or_else) == 1337.42>::value );
}