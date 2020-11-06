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


using point = std::array<int,3>;

RBR_NAMED_PARAMETER_FROM_TAG(custom_tag  , custom_ );
RBR_NAMED_PARAMETER_FROM_TAG(coord_tag  , coord_  );

namespace rbr
{
  template<> struct tag<foo> : type_<custom_tag> {};
  template<> struct tag<bar> : type_<custom_tag> {};
}

RBR_NAMED_PARAMETER_FROM_TYPE(float       , value_  );
RBR_NAMED_PARAMETER_FROM_TYPE(std::string , name_   );
RBR_NAMED_PARAMETER_FROM_TYPE(int         , factor_ );
RBR_NAMED_PARAMETER_FROM_TYPE(double      , ref_    );

template<bool B> using bool_ =  std::bool_constant<B>;