//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <raberu.hpp>
#include <string>
#include <array>

struct foo { int    value = 42;   };
struct bar { double value = 4.2;  };
struct custom_tag;

using point = std::array<int,3>;

RBR_NAMED_PARAMETER(custom_tag  , custom_ );
RBR_NAMED_PARAMETER(float       , value_  );
RBR_NAMED_PARAMETER(std::string , name_   );
RBR_NAMED_PARAMETER(point       , coord_  );
RBR_NAMED_PARAMETER(int         , factor_ );
RBR_NAMED_PARAMETER(double      , ref_    );

namespace rbr
{
  template<> struct tag<foo> : type_<custom_tag> {};
  template<> struct tag<bar> : type_<custom_tag> {};
}

template<bool B> using bool_ =  std::bool_constant<B>;