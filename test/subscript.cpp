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

  TTS_EXPECT    ( values.contains(custom_));
  TTS_EXPECT    ( values.contains(name_)  );
  TTS_EXPECT    ( values.contains(value_) );
  TTS_EXPECT_NOT( values.contains(rbr::type_<char>));
  TTS_EXPECT_NOT( values.contains(rbr::type_<short>));
  TTS_EXPECT_NOT( values.contains(rbr::type_<void*>));
}

TTS_CASE("Check settings(...).contains constexpr behavior")
{
  using namespace std::literals;

  rbr::settings values(custom_ = foo{}, name_ = "john"s, value_ = 3.f);

  TTS_EXPECT    ( bool_<values.contains(custom_)>::value            );
  TTS_EXPECT    ( bool_<values.contains(name_)  >::value            );
  TTS_EXPECT    ( bool_<values.contains(value_) >::value            );
  TTS_EXPECT_NOT( bool_<values.contains(rbr::type_<char>) >::value);
  TTS_EXPECT_NOT( bool_<values.contains(rbr::type_<short>)>::value);
  TTS_EXPECT_NOT( bool_<values.contains(rbr::type_<void*>)>::value);
}

TTS_CASE("Check settings(...) operator[t | v] behavior")
{
  using namespace std::literals;

  auto values = rbr::settings( name_ = "Jane Doe"s);

  TTS_EQUAL(values[rbr::type_<char>   | -99] , -99        );
  TTS_EQUAL(values[rbr::type_<int>    | -99] , -99        );
  TTS_EQUAL(values[rbr::type_<float>  | -99] , -99        );
  TTS_EQUAL(values[name_              | -99] , "Jane Doe"s);
}

TTS_CASE("Check settings(...) operator[t | v] constexpr behavior")
{
  constexpr auto values = rbr::settings( coord_ = 75ULL );

  TTS_EXPECT( bool_<values[rbr::type_<char>  | -99] == -99   >::value );
  TTS_EXPECT( bool_<values[rbr::type_<int>   | -99] == -99   >::value );
  TTS_EXPECT( bool_<values[rbr::type_<float> | -99] == -99   >::value );
  TTS_EXPECT( bool_<values[coord_            | -99] == 75ULL >::value );
}

TTS_CASE("Check settings(...) operator[t | func()] behavior")
{
  auto values = rbr::settings(value_ = 1337.42f);
  auto or_else = []<typename T>(rbr::type_t<T>) { return sizeof(T); };

  TTS_EQUAL(values[rbr::type_<char>   | or_else                   ] , 1ULL    );
  TTS_EQUAL(values[rbr::type_<double> | or_else                   ] , 8ULL    );
  TTS_EQUAL(values[value_             | or_else                   ] , 1337.42f);
  TTS_EQUAL(values[coord_             | [](auto) { return 42ULL; }] , 42ULL   );
}

TTS_CASE("Check settings(...) operator[t | func()] constexpr behavior")
{
  constexpr auto values = rbr::settings(value_ = 1337.42f);
  auto or_else = []<typename T>(rbr::type_t<T>) { return 42.69; };

  TTS_EXPECT( bool_<values[rbr::type_<char>   | or_else ] == 42.69    >::value );
  TTS_EXPECT( bool_<values[rbr::type_<double> | or_else ] == 42.69    >::value );
  TTS_EXPECT( bool_<values[value_             | or_else ] == 1337.42f >::value );
  TTS_EXPECT( bool_<values[custom_            | or_else ] == 42.69    >::value );
}

TTS_CASE("Check settings(...) operator[ maybe(t) ] behavior")
{
  auto values = rbr::settings( coord_ = 8.84 );

  TTS_EXPECT_NOT( values[ maybe(rbr::type_<char>) ]       );
  TTS_EXPECT_NOT( values[ maybe(rbr::type_<int>)  ]       );
  TTS_EXPECT    ( values[ maybe(coord_)             ]       );
  TTS_EQUAL     (*values[ maybe(coord_)             ], 8.84 );
}

TTS_CASE("Check settings(...) operator[ maybe(t) ] constexpr behavior")
{
  constexpr point p{1,3,5};
  constexpr auto values = rbr::settings( coord_ = p);

  TTS_EXPECT_NOT( bool_< values[ maybe(rbr::type_<char>) ].has_value() >::value);
  TTS_EXPECT_NOT( bool_< values[ maybe(rbr::type_<int>)  ].has_value() >::value);
  TTS_EXPECT    ( bool_< values[ maybe(coord_)             ].has_value()>::value);
  TTS_EXPECT    ( bool_<*values[ maybe(coord_)             ] == p       >::value);
}
