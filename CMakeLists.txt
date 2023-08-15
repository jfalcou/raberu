##======================================================================================================================
##  RABERU - Fancy Named Parameter Library
##  Copyright : RABERU Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(raberu LANGUAGES CXX)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)

##======================================================================================================================
option( RABERU_BUILD_TEST          "Build tests   for Raberu"   ON  )
option( RABERU_BUILD_DOCUMENTATION "Build Doxygen for Raberu"   OFF )

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)
copa_project_version(MAJOR 1 MINOR 1 PATCH 0)

##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT RABERU_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Unit tests : ${RABERU_BUILD_TEST} (via RABERU_BUILD_TEST)")
  message(STATUS "[${PROJECT_NAME}] - Doxygen    : ${RABERU_BUILD_DOCUMENTATION} (via RABERU_BUILD_DOCUMENTATION)")
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
  copa_setup_doxygen(${QUIET_OPTION} TARGET raberu-doxygen DESTINATION "${PROJECT_BINARY_DIR}/doc")
endif()

##======================================================================================================================
## Standalone generation
##======================================================================================================================
copa_setup_standalone ( ${QUIET_OPTION}
                        FILE raberu.hpp SOURCE include  DESTINATION standalone
                        ROOT raberu     TARGET raberu-standalone
                      )

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(RABERU_BUILD_TEST)
  enable_testing()
  add_custom_target(raberu-unit)
  add_subdirectory(test)
endif()
