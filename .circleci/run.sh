##==================================================================================================
## RABERU - Fancy Parameters Library
## Copyright 2020 Joel FALCOU
##
## Licensed under the MIT License <http://opensource.org/licenses/MIT>.
## SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

mkdir -p build/$VARIANT
cd build/$VARIANT
cmake ../.. -G Ninja $CMAKE_OPTIONS -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_CXX_FLAGS="$OPTIONS"
ninja unit  -j 8
ctest       -j 8
