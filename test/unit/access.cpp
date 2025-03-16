//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#define TTS_MAIN

#include "common.hpp"
#include <raberu/raberu.hpp>
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
  TTS_EQUAL(values[name_ | "Bob Ross"s ], "Jane Doe"s);
  TTS_EQUAL(values["default_init"_fl  | -99  ], true);
  TTS_EQUAL(values["value"_kw         | -9.9 ], 65  );

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

TTS_CASE("Check settings(...) operator[t | func(settings)] behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  auto values = rbr::settings(name_ = "Jane Doe"s, "default_init"_fl, "value"_kw = 65);
  auto or_else = [](auto const& s) { return s.size() * s["value"_kw]; };

  TTS_EQUAL(values[name_              | or_else ], "Jane Doe"s);
  TTS_EQUAL(values["default_init"_fl  | or_else ], true       );
  TTS_EQUAL(values["value"_kw         | or_else ], 65         );

  TTS_EQUAL(values["perform_copy"_fl  | or_else ], 3*65);
  TTS_EQUAL(values["other_kw"_kw      | or_else ], 3*65);
};

TTS_CASE("Check settings(...) operator[t | func()] constexpr behavior")
{
  constexpr auto values  = rbr::settings(is_modal_,value_ = 1337.42f);
  auto           or_else = [](auto const&) { return 42.69; };

  TTS_CONSTEXPR_EQUAL(values[is_modal_  | or_else ], true     );
  TTS_CONSTEXPR_EQUAL(values[value_     | or_else ], 1337.42f );

  TTS_CONSTEXPR_EQUAL(values["perform_copy"_fl  | or_else ], 42.69);
  TTS_CONSTEXPR_EQUAL(values["other_kw"_kw      | or_else ], 42.69);
};
