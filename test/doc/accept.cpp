//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <tts/tts.hpp>

//! [Custom Accept]
#include <raberu.hpp>

// Defines a keyword type that only accept floating point value
struct real_keyword : rbr::as_keyword<real_keyword>
{
  template<typename T>
  static constexpr bool check = std::is_floating_point_v<T>;

  using rbr::as_keyword<real_keyword>::operator=;
};

inline constexpr real_keyword real = {};
//! [Custom Accept]

TTS_CASE("Check accept() customization point")
{
  TTS_EXPECT_COMPILES(real, { real = 4.f;   } );
  TTS_EXPECT_NOT_COMPILES(real, { real = 8ULL;  } );
};
