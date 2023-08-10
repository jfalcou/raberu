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
#include <variant>
#include <tuple>

TTS_CASE("Check rbr::keywords")
{
  using namespace rbr::literals;

  auto opt = rbr::settings( "test"_kw = 1, "second"_kw = 3.5f, "last"_kw = 'z');
  using opt_t = decltype(opt);

  TTS_TYPE_IS ( rbr::result::keywords_t<opt_t>
              , (rbr::types< decltype("test"_kw), decltype("second"_kw), decltype("last"_kw) >)
              );

  TTS_EXPR_IS ( (std::tuple{"test"_kw, "second"_kw, "last"_kw})
              , (rbr::result::keywords_t<opt_t, std::tuple>)
              );

  TTS_EQUAL( (std::tuple{"test"_kw, "second"_kw, "last"_kw}), (rbr::keywords<std::tuple>(opt)));
};

TTS_CASE("Check rbr::values")
{
  using namespace rbr::literals;

  auto opt = rbr::settings( "test"_kw = 1, "second"_kw = 3.5f, "last"_kw = 'z');
  using opt_t = decltype(opt);

  TTS_TYPE_IS( rbr::result::values_t<opt_t>               , (rbr::types<int,float,char>)  );
  TTS_TYPE_IS( (rbr::result::values_t<opt_t,std::variant>), (std::variant<int,float,char>));
  TTS_EQUAL  ( (std::tuple{1,3.5f,'z'})                   , (rbr::values<std::tuple>(opt)));
};
