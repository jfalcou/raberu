//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#define TTS_MAIN
#include <raberu/raberu.hpp>
#include <tts/tts.hpp>
#include <type_traits>

template<typename T>
struct small_type : std::bool_constant<(sizeof(T) < 4)> {};

using namespace rbr::literals;

inline constexpr rbr::keyword<struct angle_, rbr::traits_check<std::is_floating_point> >  angle = {};
inline constexpr auto pattern = rbr::keyword( "pattern"_id, rbr::if_<small_type>);

TTS_CASE("Check constrained keyword::operator= behavior")
{
  rbr::settings s( angle = 3., pattern = 'z');
  TTS_EQUAL( s[angle]   , 3.  );
  TTS_EQUAL( s[pattern] , 'z' );
};
