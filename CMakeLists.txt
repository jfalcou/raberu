##==================================================================================================
##  RABERU - Fancy Parameters Library
##  Copyright 2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.2)

##==================================================================================================
## Setup project
##==================================================================================================
project(raberu LANGUAGES CXX)
set(PROJECT_VERSION 0.1.0)
set(PROJECT_DOC_DIR   ${PROJECT_SOURCE_DIR}/doc)

##==================================================================================================
## No in-source build
##==================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[raberu]: In-source build is not recommend")
endif()

##==================================================================================================
## Options
##==================================================================================================
option( RABERU_BUILD_TEST  "Build tests for raberu" ON )

##==================================================================================================
## Test target
##==================================================================================================
if( RABERU_BUILD_TEST )
  include(CTest)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
endif()
