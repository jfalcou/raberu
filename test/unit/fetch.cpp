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

TTS_CASE("Check rbr::fetch behavior on options")
{
  using namespace std::literals;
  using namespace rbr::literals;

  TTS_EQUAL( (rbr::fetch(coord_   , coord_ = "Jane"s, value_ = 4.2f, is_modal_))      , "Jane"s );
  TTS_EQUAL( (rbr::fetch(value_   , coord_ = "Jane"s, value_ = 4.2f, is_modal_))      , 4.2f    );
  TTS_EQUAL( (rbr::fetch(is_modal_, coord_ = "Jane"s, value_ = 4.2f, is_modal_))      , true    );
  TTS_EQUAL( (rbr::fetch("flop"_kw | 66., coord_ = "Jane"s, value_ = 4.2f, is_modal_)), 66.     );

  TTS_EXPR_IS ( (rbr::fetch("flop"_kw, coord_ = "Jane"s, value_ = 4.2f, is_modal_))
              , rbr::unknown_key
              );
};

TTS_CASE("Check rbr::fetch behavior on settings")
{
  using namespace std::literals;
  using namespace rbr::literals;

  auto opts = rbr::settings(coord_ = "Jane"s, value_ = 4.2f, is_modal_);

  TTS_EQUAL( (rbr::fetch(coord_         , opts)), "Jane"s );
  TTS_EQUAL( (rbr::fetch(value_         , opts)), 4.2f    );
  TTS_EQUAL( (rbr::fetch(is_modal_      , opts)), true    );
  TTS_EQUAL( (rbr::fetch("flop"_kw | 66., opts)), 66.     );

  TTS_EXPR_IS( (rbr::fetch("flop"_kw, opts)), rbr::unknown_key );
};

TTS_CASE("Check rbr::fetch_t behavior on options")
{
  using namespace std::literals;
  using namespace rbr::literals;

  using opt1_t = decltype(coord_ = "Jane Doe"s);
  using opt2_t = decltype(value_ = 42.69f);
  using opt3_t = decltype(is_modal_);

  TTS_TYPE_IS( (rbr::result::fetch_t<coord_   , opt1_t, opt2_t, opt3_t>), std::string     );
  TTS_TYPE_IS( (rbr::result::fetch_t<value_   , opt1_t, opt2_t, opt3_t>), float           );
  TTS_TYPE_IS( (rbr::result::fetch_t<is_modal_, opt1_t, opt2_t, opt3_t>), bool            );
  TTS_TYPE_IS( (rbr::result::fetch_t<"flop"_kw, opt1_t, opt2_t, opt3_t>), rbr::unknown_key);
};

TTS_CASE("Check rbr::fetch_t behavior on settings")
{
  using namespace std::literals;
  using namespace rbr::literals;

  using opts_t = decltype(rbr::settings(coord_ = "Jane"s, value_ = 4.2f, is_modal_));

  TTS_TYPE_IS( (rbr::result::fetch_t<coord_   , opts_t>), std::string     );
  TTS_TYPE_IS( (rbr::result::fetch_t<value_   , opts_t>), float           );
  TTS_TYPE_IS( (rbr::result::fetch_t<is_modal_, opts_t>), bool            );
  TTS_TYPE_IS( (rbr::result::fetch_t<"flop"_kw, opts_t>), rbr::unknown_key);
};

TTS_CASE("Check keyword fetching behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  TTS_EQUAL( (coord_   (coord_ = "Jane"s, value_ = 4.2f, is_modal_)), "Jane"s             );
  TTS_EQUAL( (value_   (coord_ = "Jane"s, value_ = 4.2f, is_modal_)), 4.2f                );
  TTS_EQUAL( (is_modal_(coord_ = "Jane"s, value_ = 4.2f, is_modal_)), true                );
  TTS_EXPR_IS( ("flop"_kw(coord_ = "Jane"s, value_ = 4.2f, is_modal_)), rbr::unknown_key  );
  TTS_EQUAL( (("flop"_kw | 66.)(coord_ = "Jane"s, value_ = 4.2f, is_modal_)), 66. );
};
