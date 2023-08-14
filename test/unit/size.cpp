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

TTS_CASE("Check settings(...) size")
{
  using namespace std::literals;
  using namespace rbr::literals;

  TTS_EQUAL(rbr::settings("custom"_kw = foo {}).size(), 1);
  TTS_EQUAL(rbr::settings("custom"_kw = foo {}, "border"_fl).size(), 2);
  TTS_EQUAL(rbr::settings("custom"_kw = foo {}, "name"_kw = "john"s, "border"_fl).size(), 3);

  constexpr auto any = rbr::any_keyword<rbr::id_<"any">>{};
  auto set = rbr::settings(any = foo {});
  std::cout << set << "\n";
};

TTS_CASE("Check settings(...) constexpr size - named parameters")
{
  using namespace std::literals;
  using namespace rbr::literals;

  TTS_CONSTEXPR_EQUAL(rbr::settings("custom"_kw = foo{}).size(), 1);
  TTS_CONSTEXPR_EQUAL(rbr::settings("custom"_kw = foo{}, "value"_kw = 3.f).size(), 2);
  TTS_CONSTEXPR_EQUAL(rbr::settings("custom"_kw = foo{}, "coord"_kw = point{}, "value"_kw = 3.f).size(), 3);
};
