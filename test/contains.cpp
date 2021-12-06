//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include "common.hpp"
#include <raberu.hpp>
#include <tts/tts.hpp>

TTS_CASE("Check settings(...).contains behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  rbr::settings values( custom_ = foo {}, "surname"_kw = "john"s
                      , value_ = 3.f, "aligned"_fl,is_transparent_
                      );

  TTS_EXPECT(values.contains(custom_)         );
  TTS_EXPECT(values.contains("surname"_kw)    );
  TTS_EXPECT(values.contains(value_)          );
  TTS_EXPECT(values.contains(is_transparent_) );
  TTS_EXPECT(values.contains("aligned"_fl)    );

  TTS_EXPECT_NOT(values.contains(is_modal_    ));
  TTS_EXPECT_NOT(values.contains("compact"_fl ));
};

TTS_CASE("Check settings(...).contains constexpr behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  constexpr rbr::settings values("custom"_kw = foo {}, value_ = 3.f, is_modal_);

  TTS_CONSTEXPR_EXPECT(values.contains("custom"_kw) );
  TTS_CONSTEXPR_EXPECT(values.contains(value_ )     );
  TTS_CONSTEXPR_EXPECT(values.contains(is_modal_)   );

  TTS_CONSTEXPR_EXPECT_NOT(values.contains(is_transparent_) );
  TTS_CONSTEXPR_EXPECT_NOT(values.contains("compact"_fl   ) );
};

TTS_CASE("Check settings(...).contains_any behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  rbr::settings values( custom_ = foo {}, "surname"_kw = "john"s
                      , value_ = 3.f, "aligned"_fl,is_transparent_
                      );

  TTS_EXPECT    (values.contains_any(custom_, is_transparent_, "compact"_fl) );
  TTS_EXPECT_NOT(values.contains_any(is_modal_, "compact"_fl) );
};

TTS_CASE("Check settings(...).contains_any constexpr behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  constexpr rbr::settings values("custom"_kw = foo {}, value_ = 3.f, is_modal_);

  TTS_CONSTEXPR_EXPECT    (values.contains_any(value_, is_modal_, "custom"_kw) );
  TTS_CONSTEXPR_EXPECT_NOT(values.contains_any(is_transparent_, "compact"_fl) );
};

TTS_CASE("Check settings(...).contains_only behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  rbr::settings values( "kw1"_kw = 1,  "kw2"_kw = 1,  "kw3"_kw = 1 );

  TTS_EXPECT    (values.contains_only("kw1"_kw,  "kw2"_kw,  "kw3"_kw)           );
  TTS_EXPECT    (values.contains_only("kw1"_kw,  "kw3"_kw,  "kw2"_kw)           );
  TTS_EXPECT    (values.contains_only("kw1"_kw,  "kw3"_kw,  "kw2"_kw, "xyz"_kw) );

  TTS_EXPECT_NOT(values.contains_only("kw1"_kw,  "kw2"_kw));
  TTS_EXPECT_NOT(values.contains_only("kw1"_kw)           );
  TTS_EXPECT_NOT(values.contains_only("a"_kw)             );
  TTS_EXPECT_NOT(values.contains_only("a"_kw, "b"_kw)     );
};

TTS_CASE("Check settings(...).contains_only constexpr behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  constexpr rbr::settings values( "kw1"_kw = 1,  "kw2"_kw = 1,  "kw3"_kw = 1 );

  TTS_CONSTEXPR_EXPECT(values.contains_only("kw1"_kw,  "kw2"_kw,  "kw3"_kw)           );
  TTS_CONSTEXPR_EXPECT(values.contains_only("kw1"_kw,  "kw3"_kw,  "kw2"_kw)           );
  TTS_CONSTEXPR_EXPECT(values.contains_only("kw1"_kw,  "kw3"_kw,  "kw2"_kw, "xyz"_kw) );

  TTS_CONSTEXPR_EXPECT_NOT(values.contains_only("kw1"_kw,  "kw2"_kw));
  TTS_CONSTEXPR_EXPECT_NOT(values.contains_only("kw1"_kw)           );
  TTS_CONSTEXPR_EXPECT_NOT(values.contains_only("a"_kw)             );
  TTS_CONSTEXPR_EXPECT_NOT(values.contains_only("a"_kw, "b"_kw)     );
};

TTS_CASE("Check settings(...).contains_none behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  rbr::settings values( custom_ = foo {}, "surname"_kw = "john"s
                      , value_ = 3.f, "aligned"_fl,is_transparent_
                      );

  TTS_EXPECT    (values.contains_none(is_modal_, "compact"_fl) );
  TTS_EXPECT_NOT(values.contains_none(value_, is_transparent_) );
};

TTS_CASE("Check settings(...).contains_none constexpr behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  constexpr rbr::settings values("custom"_kw = foo {}, value_ = 3.f, is_modal_);

  TTS_CONSTEXPR_EXPECT    (values.contains_none(is_transparent_, "compact"_fl) );
  TTS_CONSTEXPR_EXPECT_NOT(values.contains_none(value_) );
};
