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

TTS_CASE("Check settings(...).contains behavior")
{
  using namespace std::literals;

  rbr::settings values(custom_ = foo{}, name_ = "john"s, value_ = 3.f);

  TTS_EXPECT    ( values.contains(custom_)            );
  TTS_EXPECT    ( values.contains(name_)              );
  TTS_EXPECT    ( values.contains(value_)             );
  TTS_EXPECT_NOT( values.contains(rbr::keyword<char>) );
  TTS_EXPECT_NOT( values.contains(rbr::keyword<short>));
  TTS_EXPECT_NOT( values.contains(rbr::keyword<void*>));
}

TTS_CASE("Check settings(...).contains constexpr behavior")
{
  using namespace std::literals;

  rbr::settings values(custom_ = foo{}, name_ = "john"s, value_ = 3.f);

  TTS_EXPECT    ( bool_<values.contains(custom_)>::value            );
  TTS_EXPECT    ( bool_<values.contains(name_)  >::value            );
  TTS_EXPECT    ( bool_<values.contains(value_) >::value            );
  TTS_EXPECT_NOT( bool_<values.contains(rbr::keyword<char>) >::value);
  TTS_EXPECT_NOT( bool_<values.contains(rbr::keyword<short>)>::value);
  TTS_EXPECT_NOT( bool_<values.contains(rbr::keyword<void*>)>::value);
}
