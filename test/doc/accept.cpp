/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#define TTS_MAIN
#include <tts/tts.hpp>

//! [Custom Accept]
#include <raberu/raberu.hpp>

// Defines a keyword type that only accept floating point value
struct real_keyword : rbr::keyword<real_keyword, rbr::traits_check<std::is_floating_point>>
{
  using parent = rbr::keyword<real_keyword, rbr::traits_check<std::is_floating_point>>;
  using parent::operator=;
};

inline constexpr real_keyword real = {};
//! [Custom Accept]

TTS_CASE("Check accept() customization point")
{
  TTS_EXPECT_COMPILES     (real , { real = 4.f;   } );
  TTS_EXPECT_NOT_COMPILES (real , { real = 8ULL;  } );
};
