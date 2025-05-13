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

// MSVC does not support incomplete types in concepts (?)
struct key {};

TTS_CASE("Check rbr::concepts::keyword concept")
{
  using namespace rbr::literals;

  // Direct type
  TTS_EXPECT(   rbr::concepts::keyword< rbr::flag<key>            > );
  TTS_EXPECT(   rbr::concepts::keyword< rbr::keyword<key>            > );
  TTS_EXPECT( ( rbr::concepts::keyword< rbr::keyword <key, rbr::only_t<double>>    >));
  TTS_EXPECT( ( rbr::concepts::keyword< rbr::keyword<key,rbr::traits_check<small_type>>>));

  // Predefined keyword object
  TTS_EXPECT(   rbr::concepts::keyword< decltype(custom_) > );
  TTS_EXPECT(   rbr::concepts::keyword< decltype(coord_ ) > );

  // Type from polymorphic constructor
  TTS_EXPECT(   rbr::concepts::keyword< decltype(rbr::keyword("any"_id)) > );
  TTS_EXPECT(   rbr::concepts::keyword< decltype(rbr::keyword("small"_id,::rbr::if_<small_type>)) > );
  TTS_EXPECT(   rbr::concepts::keyword< decltype(rbr::keyword("real_value"_id,::rbr::only<float>)) > );
  TTS_EXPECT(   rbr::concepts::keyword< decltype(rbr::flag("modal"_id)) > );

  // Type from literals
  TTS_EXPECT(   rbr::concepts::keyword< decltype("any"_kw) > );
  TTS_EXPECT(   rbr::concepts::keyword< decltype("modal"_fl) > );

  // Obviously wrong type
  TTS_EXPECT_NOT( rbr::concepts::keyword<float**> );
};

struct my_little_keyword : rbr::keyword<struct key, rbr::traits_check<small_type>>
{
  using parent = rbr::keyword<struct key, rbr::traits_check<small_type>>;
  using parent::operator=;
};

TTS_CASE("Check rbr::concepts::option concept")
{
  TTS_EXPECT( (rbr::concepts::option<rbr::option<rbr::keyword<struct key> , int>>) );
  TTS_EXPECT( (rbr::concepts::option<rbr::option<my_little_keyword        , int>>) );
  TTS_EXPECT( (rbr::concepts::option<rbr::flag<struct key>>) );
  TTS_EXPECT_NOT(rbr::concepts::option<float**> );
};

TTS_CASE("Check rbr::exactly concept")
{
  using namespace rbr::literals;

  auto param = (coord_ = 9);

  TTS_EXPECT( (rbr::concepts::exactly<decltype(param)              , coord_    >) );
  TTS_EXPECT( (rbr::concepts::exactly<decltype("local"_kw = 6.34f) , "local"_kw>) );
  TTS_EXPECT_NOT( (rbr::concepts::exactly<decltype("local"_kw = 77), coord_    >) );
};
