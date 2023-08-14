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

TTS_CASE("Check drop constexpr behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  constexpr rbr::settings v ( custom_ = foo {}
                            , "surname"_kw = 'z'
                            , value_ = 3.f
                            , "aligned"_fl
                            , is_transparent_
                            );

  // clang++-14 debug regression fix
  constexpr auto surname = "surname"_kw;
  constexpr auto aligned = "aligned"_fl;

  constexpr auto v0 = drop(is_transparent_, v);
  TTS_CONSTEXPR_EXPECT     (v0.contains(custom_)        );
  TTS_CONSTEXPR_EXPECT     (v0.contains(surname)        );
  TTS_CONSTEXPR_EXPECT     (v0.contains(value_)         );
  TTS_CONSTEXPR_EXPECT     (v0.contains(aligned)        );
  TTS_CONSTEXPR_EXPECT_NOT (v0.contains(is_transparent_));
  TTS_CONSTEXPR_EQUAL      (v0.size(), 4 );

  constexpr auto v1 = drop(aligned, v0);
  TTS_CONSTEXPR_EXPECT     (v1.contains(custom_)        );
  TTS_CONSTEXPR_EXPECT     (v1.contains(surname)        );
  TTS_CONSTEXPR_EXPECT     (v1.contains(value_)         );
  TTS_CONSTEXPR_EXPECT_NOT (v1.contains(aligned)        );
  TTS_CONSTEXPR_EXPECT_NOT (v1.contains(is_transparent_));
  TTS_CONSTEXPR_EQUAL      (v1.size(), 3 );

  constexpr auto v2 = drop(value_, v1);
  TTS_CONSTEXPR_EXPECT     (v2.contains(custom_)        );
  TTS_CONSTEXPR_EXPECT     (v2.contains(surname)        );
  TTS_CONSTEXPR_EXPECT_NOT (v2.contains(value_)         );
  TTS_CONSTEXPR_EXPECT_NOT (v2.contains(aligned)        );
  TTS_CONSTEXPR_EXPECT_NOT (v2.contains(is_transparent_));
  TTS_CONSTEXPR_EQUAL      (v2.size(), 2 );

  constexpr auto v3 = drop(surname, v2);
  TTS_CONSTEXPR_EXPECT     (v3.contains(custom_)        );
  TTS_CONSTEXPR_EXPECT_NOT (v3.contains(surname)        );
  TTS_CONSTEXPR_EXPECT_NOT (v3.contains(value_)         );
  TTS_CONSTEXPR_EXPECT_NOT (v3.contains(aligned)        );
  TTS_CONSTEXPR_EXPECT_NOT (v3.contains(is_transparent_));
  TTS_CONSTEXPR_EQUAL      (v3.size(), 1 );

  constexpr auto v4 = drop(custom_, v3);
  TTS_CONSTEXPR_EXPECT_NOT (v4.contains(custom_)        );
  TTS_CONSTEXPR_EXPECT_NOT (v4.contains(surname)        );
  TTS_CONSTEXPR_EXPECT_NOT (v4.contains(value_)         );
  TTS_CONSTEXPR_EXPECT_NOT (v4.contains(aligned)        );
  TTS_CONSTEXPR_EXPECT_NOT (v4.contains(is_transparent_));
  TTS_CONSTEXPR_EQUAL      (v4.size(), 0 );
};

TTS_CASE("Check drop behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  auto alg = "aligned"_fl;

  rbr::settings v ( custom_ = foo {}
                  , "surname"_kw = "john"s
                  , value_ = 3.f
                  , alg
                  , is_transparent_
                  );

  auto v0 = drop(is_transparent_, v);
  TTS_EXPECT     (v0.contains(custom_)         );
  TTS_EXPECT     (v0.contains("surname"_kw)    );
  TTS_EXPECT     (v0.contains(value_)          );
  TTS_EXPECT     (v0.contains(alg)    );
  TTS_EXPECT_NOT (v0.contains(is_transparent_) );
  TTS_EQUAL      (v0.size(), 4 );

  auto v1 = drop(alg, v0);
  TTS_EXPECT     (v1.contains(custom_)         );
  TTS_EXPECT     (v1.contains("surname"_kw)    );
  TTS_EXPECT     (v1.contains(value_)          );
  TTS_EXPECT_NOT (v1.contains(alg)    );
  TTS_EXPECT_NOT (v1.contains(is_transparent_) );
  TTS_EQUAL      (v1.size(), 3 );

  auto v2 = drop(value_, v1);
  TTS_EXPECT     (v2.contains(custom_)         );
  TTS_EXPECT     (v2.contains("surname"_kw)    );
  TTS_EXPECT_NOT (v2.contains(value_)          );
  TTS_EXPECT_NOT (v2.contains(alg)    );
  TTS_EXPECT_NOT (v2.contains(is_transparent_) );
  TTS_EQUAL      (v2.size(), 2 );

  auto v3 = drop("surname"_kw, v2);
  TTS_EXPECT     (v3.contains(custom_)         );
  TTS_EXPECT_NOT (v3.contains("surname"_kw)    );
  TTS_EXPECT_NOT (v3.contains(value_)          );
  TTS_EXPECT_NOT (v3.contains(alg)    );
  TTS_EXPECT_NOT (v3.contains(is_transparent_) );
  TTS_EQUAL      (v3.size(), 1 );

  auto v4 = drop(custom_, v3);
  TTS_EXPECT_NOT (v4.contains(custom_)         );
  TTS_EXPECT_NOT (v4.contains("surname"_kw)    );
  TTS_EXPECT_NOT (v4.contains(value_)          );
  TTS_EXPECT_NOT (v4.contains(alg)    );
  TTS_EXPECT_NOT (v4.contains(is_transparent_) );
  TTS_EQUAL      (v4.size(), 0 );
};
