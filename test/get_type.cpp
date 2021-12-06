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

TTS_CASE("Check get_type<S,K> behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  auto values     = rbr::settings(coord_ = "Jane Doe"s, value_ = 42.69f, is_modal_);
  using options_t = decltype(values);

  TTS_TYPE_IS( (rbr::get_type_t<options_t, coord_   >), std::string      );
  TTS_TYPE_IS( (rbr::get_type_t<options_t, value_   >), float            );
  TTS_TYPE_IS( (rbr::get_type_t<options_t, is_modal_>), std::true_type   );
  TTS_TYPE_IS( (rbr::get_type_t<options_t, "flop"_kw>), rbr::unknown_key );
};

TTS_CASE("Check get_type<S,K,O> behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  auto values     = rbr::settings(coord_ = "Jane Doe"s, value_ = 42.69f, is_modal_);
  using options_t = decltype(values);

  TTS_TYPE_IS( (rbr::get_type_t<options_t, coord_   , void*>), std::string    );
  TTS_TYPE_IS( (rbr::get_type_t<options_t, value_   , void*>), float          );
  TTS_TYPE_IS( (rbr::get_type_t<options_t, is_modal_, void*>), std::true_type );
  TTS_TYPE_IS( (rbr::get_type_t<options_t, "flop"_kw, void*>), void*          );
};
