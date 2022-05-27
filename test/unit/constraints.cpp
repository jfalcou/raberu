//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <raberu.hpp>
#include <tts/tts.hpp>
#include <type_traits>

struct real_type
{
  template<typename T> struct apply : std::is_floating_point<T> {};
};

struct small_type
{
  template<typename T> struct apply : std::bool_constant<(sizeof(T) < 4)> {};
};

using namespace rbr::literals;

inline constexpr rbr::checked_keyword<struct angle_, real_type >  angle = {};
inline constexpr auto pattern = rbr::keyword<small_type>( "pattern"_id);

TTS_CASE("Check constrainted keyword::operator= behavior")
{
  rbr::settings s( angle = 3., pattern = 'z');
  TTS_EQUAL( s[angle]   , 3.  );
  TTS_EQUAL( s[pattern] , 'z' );
};
