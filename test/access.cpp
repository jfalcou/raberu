//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <iostream>
#include "common.hpp"
#include <raberu.hpp>
#include <tts/tts.hpp>

TTS_CASE("Check settings(...) operator[t] behavior")
{
  using namespace std::literals;

  auto values = rbr::settings(coord_ = "Jane Doe"s, is_modal_);

  TTS_EQUAL(values[coord_]         , "Jane Doe"s );
  TTS_EQUAL(values[is_modal_]      , true        );
  TTS_EQUAL(values[is_transparent_], false       );
};

TTS_CASE("Check settings(...) operator[t] constexpr behavior")
{
  constexpr auto values = rbr::settings(coord_ = 75ULL, is_transparent_, "value"_kw = 42.69f);

  TTS_CONSTEXPR_EQUAL(values["value"_kw]      , 42.69f);
  TTS_CONSTEXPR_EQUAL(values[coord_]          , 75ULL );
  TTS_CONSTEXPR_EQUAL(values[is_transparent_] , true  );
  TTS_CONSTEXPR_EQUAL(values[is_modal_]       , false );
};

TTS_CASE("Check settings(...) operator[t | v] behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  auto values = rbr::settings(name_ = "Jane Doe"s, "default_init"_fl, "value"_kw = 65);

  TTS_EQUAL(values[name_              | "Bob Ross"s ], "Jane Doe"s);
  TTS_EQUAL(values["default_init"_fl  | -99         ], true       );
  TTS_EQUAL(values["value"_kw         | -9.9        ], 65         );

  TTS_EQUAL(values["perform_copy"_fl  | -99 ], -99);
  TTS_EQUAL(values["other_kw"_kw      | -9.9], -9.9);
};

TTS_CASE("Check settings(...) operator[t | v] constexpr behavior")
{
  using namespace rbr::literals;

  constexpr auto values = rbr::settings("default_init"_fl, coord_ = 75ULL);

  TTS_CONSTEXPR_EQUAL(values[coord_             | -99], 75ULL);
  TTS_CONSTEXPR_EQUAL(values["default_init"_fl  | -99], true);

  TTS_CONSTEXPR_EQUAL(values["perform_copy"_fl | -99], -99);
  TTS_CONSTEXPR_EQUAL(values["other_kw"_kw     | -9.9], -9.9);
};

TTS_CASE("Check settings(...) operator[t | func()] behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  auto values = rbr::settings(name_ = "Jane Doe"s, "default_init"_fl, "value"_kw = 65);
  auto or_else = [&]() { return values.size() * values["value"_kw]; };

  TTS_EQUAL(values[name_              | rbr::call(or_else) ], "Jane Doe"s);
  TTS_EQUAL(values["default_init"_fl  | rbr::call(or_else) ], true       );
  TTS_EQUAL(values["value"_kw         | rbr::call(or_else) ], 65         );

  TTS_EQUAL(values["perform_copy"_fl  | rbr::call(or_else) ], 3*65);
  TTS_EQUAL(values["other_kw"_kw      | rbr::call(or_else) ], 3*65);
};

TTS_CASE("Check settings(...) operator[t | func()] constexpr behavior")
{
  constexpr auto values  = rbr::settings(is_modal_,value_ = 1337.42f);
  auto           or_else = []() { return 42.69; };

  TTS_CONSTEXPR_EQUAL(values[is_modal_  | rbr::call(or_else) ], true     );
  TTS_CONSTEXPR_EQUAL(values[value_     | rbr::call(or_else) ], 1337.42f );

  TTS_CONSTEXPR_EQUAL(values["perform_copy"_fl  | rbr::call(or_else) ], 42.69);
  TTS_CONSTEXPR_EQUAL(values["other_kw"_kw      | rbr::call(or_else) ], 42.69);
};
