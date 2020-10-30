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

TTS_CASE("Check settings(...) size - simple parameters")
{
  TTS_EQUAL(rbr::settings (           ).size(), 0);
  TTS_EQUAL(rbr::settings ( 1         ).size(), 1);
  TTS_EQUAL(rbr::settings ( 2,1.f     ).size(), 2);
  TTS_EQUAL(rbr::settings ( "3",2,1.f ).size(), 3);
}

TTS_CASE("Check settings(...) size - named parameters")
{
  using namespace std::literals;

  TTS_EQUAL(rbr::settings ( custom_ = foo{} ).size()                                , 1);
  TTS_EQUAL(rbr::settings ( custom_ = foo{}, value_ = 3.f ).size()                  , 2);
  TTS_EQUAL(rbr::settings ( custom_ = foo{}, name_ = "john"s, value_ = 3.f ).size() , 3);
}

TTS_CASE("Check settings(...) constexpr size - simple parameters")
{
  TTS_EXPECT( bool_<rbr::settings (           ).size() == 0>::value );
  TTS_EXPECT( bool_<rbr::settings ( 1         ).size() == 1>::value );
  TTS_EXPECT( bool_<rbr::settings ( 2,1.f     ).size() == 2>::value );
  TTS_EXPECT( bool_<rbr::settings ( "3",2,1.f ).size() == 3>::value );
}

TTS_CASE("Check settings(...) constexpr size - named parameters")
{
  using namespace std::literals;

  TTS_EXPECT( bool_<rbr::settings ( custom_ = foo{} ).size()  == 1>::value);
  TTS_EXPECT( bool_<rbr::settings ( custom_ = foo{}, value_ = 3.f ).size()  == 2>::value);
  TTS_EXPECT( bool_<rbr::settings ( custom_ = foo{}, coord_ = point{}, value_ = 3.f ).size() == 3>::value);
}
