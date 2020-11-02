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

TTS_CASE("Check settings(...) get_or behavior - simple parameters")
{
  auto values = rbr::settings(1337.42);

  TTS_EQUAL(get_or<char>  (values, -99) , -99     );
  TTS_EQUAL(get_or<int>   (values, -99) , -99     );
  TTS_EQUAL(get_or<float> (values, -99) , -99     );
  TTS_EQUAL(get_or<double>(values, -99) , 1337.42 );
}

TTS_CASE("Check settings(...) get_or behavior - named parameters")
{
  using namespace std::literals;

  auto values = rbr::settings( name_ = "Jane Doe"s);

  TTS_EQUAL(get_or<char>  (values, -99) , -99     );
  TTS_EQUAL(get_or<int>   (values, -99) , -99     );
  TTS_EQUAL(get_or<float> (values, -99) , -99     );
  TTS_EQUAL(get_or<std::string>(values, -99) , "Jane Doe"s );
}

TTS_CASE("Check settings(...) get_or constexpr behavior - simple parameters")
{
  constexpr auto values = rbr::settings(1337.42);

  TTS_EXPECT( bool_<get_or<char>  (values,-99) == -99    >::value );
  TTS_EXPECT( bool_<get_or<int>   (values,-99) == -99    >::value );
  TTS_EXPECT( bool_<get_or<float> (values,-99) == -99    >::value );
  TTS_EXPECT( bool_<get_or<double>(values,-99) == 1337.42>::value );
}

TTS_CASE("Check settings(...) get_or constexpr behavior - named parameters")
{
  constexpr auto values = rbr::settings( coord_ = 75ULL );

  TTS_EXPECT( bool_<get_or<char> (values,-99) == -99>::value );
  TTS_EXPECT( bool_<get_or<int>  (values,-99) == -99>::value );
  TTS_EXPECT( bool_<get_or<float>(values,-99) == -99>::value );
  TTS_EXPECT( bool_<get_or<coord_tag>(values,-99) == 75ULL >::value );
}
