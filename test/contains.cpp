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

TTS_CASE("Check settings(...) contains - simple parameters")
{
  TTS_EXPECT(contains<char>(rbr::settings ('3',2,1.f )));
  TTS_EXPECT(contains<int>(rbr::settings ('3',2,1.f )));
  TTS_EXPECT(contains<float>(rbr::settings ('3',2,1.f )));

  TTS_EXPECT_NOT(contains<double>(rbr::settings ('3',2,1.f )));
  TTS_EXPECT_NOT(contains<short>(rbr::settings ('3',2,1.f )));
  TTS_EXPECT_NOT(contains<void*>(rbr::settings ('3',2,1.f )));
}

TTS_CASE("Check settings(...) contains - named parameters")
{
  using namespace std::literals;

  TTS_EXPECT(contains<custom_tag>(rbr::settings (custom_ = foo{}, name_ = "john"s, value_ = 3.f)));
  TTS_EXPECT(contains<std::string>(rbr::settings (custom_ = foo{}, name_ = "john"s, value_ = 3.f)));
  TTS_EXPECT(contains<float>(rbr::settings (custom_ = foo{}, name_ = "john"s, value_ = 3.f)));

  TTS_EXPECT_NOT(contains<double>(rbr::settings (custom_ = foo{}, name_ = "john"s, value_ = 3.f)));
  TTS_EXPECT_NOT(contains<short>(rbr::settings (custom_ = foo{}, name_ = "john"s, value_ = 3.f)));
  TTS_EXPECT_NOT(contains<void*>(rbr::settings (custom_ = foo{}, name_ = "john"s, value_ = 3.f)));
}

TTS_CASE("Check settings(...) constexpr contains - simple parameters")
{
  TTS_EXPECT(bool_<contains<char>(rbr::settings ('3',2,1.f ))>::value  );
  TTS_EXPECT(bool_<contains<int>(rbr::settings ('3',2,1.f ))>::value   );
  TTS_EXPECT(bool_<contains<float>(rbr::settings ('3',2,1.f ))>::value );

  TTS_EXPECT_NOT(bool_<contains<double>(rbr::settings ('3',2,1.f ))>::value);
  TTS_EXPECT_NOT(bool_<contains<short>(rbr::settings ('3',2,1.f ))>::value );
  TTS_EXPECT_NOT(bool_<contains<void*>(rbr::settings ('3',2,1.f ))>::value );
}

TTS_CASE("Check settings(...) constexpr contains - named parameters")
{
  TTS_EXPECT(bool_<contains<custom_tag>(rbr::settings (custom_ = foo{}, coord_ = point{}, value_ = 3.f  ))>::value  );
  TTS_EXPECT(bool_<contains<point>(rbr::settings (custom_ = foo{}, coord_ = point{}, value_ = 3.f  ))>::value   );
  TTS_EXPECT(bool_<contains<float>(rbr::settings (custom_ = foo{}, coord_ = point{}, value_ = 3.f  ))>::value );

  TTS_EXPECT_NOT(bool_<contains<double>(rbr::settings (custom_ = foo{}, coord_ = point{}, value_ = 3.f  ))>::value);
  TTS_EXPECT_NOT(bool_<contains<short>(rbr::settings (custom_ = foo{}, coord_ = point{}, value_ = 3.f  ))>::value );
  TTS_EXPECT_NOT(bool_<contains<void*>(rbr::settings (custom_ = foo{}, coord_ = point{}, value_ = 3.f  ))>::value );
}
