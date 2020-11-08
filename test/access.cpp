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

TTS_CASE("Check settings(...) operator[t] behavior")
{
  using namespace std::literals;

  auto values = rbr::settings( coord_ = "Jane Doe"s, 42.69f);

  TTS_EQUAL(values[rbr::keyword<float>] , 42.69f     );
  TTS_EQUAL(values[coord_             ] , "Jane Doe"s);
}

TTS_CASE("Check settings(...) operator[t] life-time handling")
{
  using namespace std::literals;

  auto s =  "Jane Doe"s;
  float f = 42.69f;

  auto values = rbr::settings( coord_ = s, f);

  TTS_EQUAL(&values[rbr::keyword<float>] , &f);
  TTS_EQUAL(&values[coord_             ] , &s);
}

TTS_CASE("Check settings(...) operator[t] constexpr behavior")
{
  constexpr auto values = rbr::settings( coord_ = 75ULL, 42.69f );

  TTS_EXPECT( bool_<values[rbr::keyword<float>] == 42.69f>::value );
  TTS_EXPECT( bool_<values[coord_             ] == 75ULL >::value );
}

TTS_CASE("Check settings(...) operator[t | v] behavior")
{
  using namespace std::literals;

  auto values = rbr::settings( name_ = "Jane Doe"s);

  TTS_EQUAL(values[rbr::keyword<char>   | -99] , -99        );
  TTS_EQUAL(values[rbr::keyword<int>    | -99] , -99        );
  TTS_EQUAL(values[rbr::keyword<float>  | -99] , -99        );
  TTS_EQUAL(values[name_                | -99] , "Jane Doe"s);
}

TTS_CASE("Check settings(...) operator[t | v] life-time handling")
{
  using namespace std::literals;

  auto  s   =  "Jane Doe"s;
  auto  alt =  "Bob Ross"s;
  float f   = 42.69f;

  auto values = rbr::settings( coord_ = s, f);

  TTS_EQUAL(&values[rbr::keyword<float> | 13.37f  ] , &f);
  TTS_EQUAL(&values[coord_              | "test"s ] , &s);
  TTS_EQUAL(&values[name_               | alt     ] , &alt);
}

TTS_CASE("Check settings(...) operator[t | v] constexpr behavior")
{
  constexpr auto values = rbr::settings( coord_ = 75ULL );

  TTS_EXPECT( bool_<values[rbr::keyword<char>  | -99] == -99   >::value );
  TTS_EXPECT( bool_<values[rbr::keyword<int>   | -99] == -99   >::value );
  TTS_EXPECT( bool_<values[rbr::keyword<float> | -99] == -99   >::value );
  TTS_EXPECT( bool_<values[coord_              | -99] == 75ULL >::value );
}

TTS_CASE("Check settings(...) operator[t | func()] behavior")
{
  auto values = rbr::settings(value_ = 1337.42f);
  auto or_else = []<typename T>(rbr::keyword_type<T>) { return sizeof(T); };

  TTS_EQUAL(values[rbr::keyword<char>   | or_else                   ] , 1ULL    );
  TTS_EQUAL(values[rbr::keyword<double> | or_else                   ] , 8ULL    );
  TTS_EQUAL(values[value_               | or_else                   ] , 1337.42f);
  TTS_EQUAL(values[coord_               | [](auto) { return 42ULL; }] , 42ULL   );
}

TTS_CASE("Check settings(...) operator[t | func()] constexpr behavior")
{
  constexpr auto values = rbr::settings(value_ = 1337.42f);
  auto or_else = []<typename T>(rbr::keyword_type<T>) { return 42.69; };

  TTS_EXPECT( bool_<values[rbr::keyword<char>   | or_else ] == 42.69    >::value );
  TTS_EXPECT( bool_<values[rbr::keyword<double> | or_else ] == 42.69    >::value );
  TTS_EXPECT( bool_<values[value_               | or_else ] == 1337.42f >::value );
  TTS_EXPECT( bool_<values[custom_              | or_else ] == 42.69    >::value );
}
