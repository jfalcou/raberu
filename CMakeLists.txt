##======================================================================================================================
##  RABERU - Fancy Named Parameter Library
##  Copyright : RABERU Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(raberu LANGUAGES CXX)

##======================================================================================================================
option( RABERU_BUILD_TEST          "Build tests   for Raberu"   ON  )
option( RABERU_BUILD_DOCUMENTATION "Build Doxygen for Raberu"   OFF )
option( RABERU_ENABLE_SANITIZERS   "Build tests with AddressSanitizer + UndefinedBehaviorSanitizer" OFF )
option( RABERU_ENABLE_COVERAGE     "Build tests with code coverage instrumentation"                 OFF )

##======================================================================================================================
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)

if(RABERU_BUILD_TEST)
  include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)
endif()

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)
copa_project_version(MAJOR 1 MINOR 1 PATCH 0 REPOSITORY https://github.com/jfalcou/raberu)

##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT RABERU_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Unit tests : ${RABERU_BUILD_TEST} (via RABERU_BUILD_TEST)")
  message(STATUS "[${PROJECT_NAME}] - Doxygen    : ${RABERU_BUILD_DOCUMENTATION} (via RABERU_BUILD_DOCUMENTATION)")
  message(STATUS "[${PROJECT_NAME}] - Sanitizers : ${RABERU_ENABLE_SANITIZERS} (via RABERU_ENABLE_SANITIZERS)")
  message(STATUS "[${PROJECT_NAME}] - Coverage   : ${RABERU_ENABLE_COVERAGE} (via RABERU_ENABLE_COVERAGE)")
  set(QUIET_OPTION "")
else()
  set(QUIET_OPTION "QUIET")
endif()

##======================================================================================================================
## Install Process setup
##======================================================================================================================
copa_setup_install( LIBRARY raberu
                    FEATURES cxx_std_20
                    DOC     ${PROJECT_SOURCE_DIR}/LICENSE.md
                    INCLUDE ${PROJECT_SOURCE_DIR}/include/raberu
                  )

##======================================================================================================================
## Setup doxygen
##======================================================================================================================
if(RABERU_BUILD_DOCUMENTATION)
  copa_setup_doxygen(${QUIET_OPTION}
                     TARGET raberu-doxygen
                     DESTINATION "${PROJECT_BINARY_DIR}/doc"
                     GODBOLT_LIBRARIES raberu
                     GODBOLT_COMPILER clang1600
                     GODBOLT_OPTIONS "-O3 -std=c++20 -DNDEBUG"
                     COLOR_HUE 0
                     COLOR_SATURATION 100
                     COLOR_LIGHTNESS 25)
endif()

##======================================================================================================================
## Standalone generation
##======================================================================================================================
copa_setup_standalone ( ${QUIET_OPTION}
                        FILE raberu.hpp SOURCE include ROOT raberu TARGET raberu-standalone
                        OUTPUT "${PROJECT_BINARY_DIR}"
                      )

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(RABERU_BUILD_TEST)
  if(RABERU_ENABLE_SANITIZERS)
    copa_setup_sanitizers(raberu_test ENABLE_ASAN ENABLE_UBSAN)
  endif()

  include(CTest)
  enable_testing()
  add_custom_target(raberu-unit)
  add_subdirectory(test)

  # After the test targets exist, so the coverage targets can depend on them
  if(RABERU_ENABLE_COVERAGE)
    copa_setup_coverage(raberu_test)
  endif()
endif()
