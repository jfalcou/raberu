/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#define TTS_MAIN
#include <tts/tts.hpp>

//! [Custom Show]
#include <raberu.hpp>

// Defines a keyword type that only accept floating point value
struct price_keyword : rbr::as_keyword<price_keyword>
{
  using rbr::as_keyword<price_keyword>::operator=;

  std::ostream& display(std::ostream& os, auto const& v)
  {
    return os << "Price: " << v << '$';
  }
};

inline constexpr price_keyword price = {};
//! [Custom Show]

#include <sstream>

TTS_CASE("Check show() customization point")
{
  std::ostringstream os;

  auto s = rbr::settings(price = 4);
  os << s;

  TTS_EQUAL(os.str(), std::string{"Price: 4$\n"});
};
