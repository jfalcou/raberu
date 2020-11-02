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

TTS_CASE("Check settings(...) get behavior - simple parameters")
{
  using namespace std::literals;

  auto values = rbr::settings('1',2,3.f,4.,"5"s);

  TTS_EQUAL(get<char>(values)        , '1' );
  TTS_EQUAL(get<int>(values)         , 2   );
  TTS_EQUAL(get<float>(values)       , 3.f );
  TTS_EQUAL(get<double>(values)      , 4.  );
  TTS_EQUAL(get<std::string>(values) , "5"s);

  TTS_EQUAL(get<custom_tag>(rbr::settings(foo{})).value, 42  );
  TTS_EQUAL(get<custom_tag>(rbr::settings(bar{})).value, 4.2 );
}

TTS_CASE("Check settings(...) get behavior - named parameters")
{
  using namespace std::literals;

  auto values = rbr::settings(custom_ = foo{}, name_ = "john"s, value_ = 3.f);

  TTS_EQUAL(get<custom_tag>(values).value , 42      );
  TTS_EQUAL(get<float>(values)            , 3.f     );
  TTS_EQUAL(get<std::string>(values)      , "john"s );
}

TTS_CASE("Check settings(...) get constexpr behavior - simple parameters")
{
  constexpr auto values = rbr::settings('1',2,3.f,4.);

  TTS_EXPECT( bool_<get<char>(values)   == '1'  >::value );
  TTS_EXPECT( bool_<get<int>(values)    == 2    >::value );
  TTS_EXPECT( bool_<get<float>(values)  == 3.f  >::value );
  TTS_EXPECT( bool_<get<double>(values) == 4.   >::value );

  TTS_EXPECT( bool_<get<custom_tag>(rbr::settings(foo{})).value == 42 >::value );
  TTS_EXPECT( bool_<get<custom_tag>(rbr::settings(bar{})).value == 4.2>::value );
}

TTS_CASE("Check settings(...) get constexpr behavior - named parameters")
{
  constexpr point p{1,2,3};
  constexpr auto values = rbr::settings(custom_ = bar{}, coord_ = p, value_ = 3.f);

  TTS_EXPECT( bool_<get<custom_tag>(values).value == 4.2>::value );
  TTS_EXPECT( bool_<get<coord_tag>(values)        == p  >::value );
  TTS_EXPECT( bool_<get<float>(values)            == 3.f>::value );
}
