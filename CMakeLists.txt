##==================================================================================================
##  RABERU - Cmpact C++20 Tuple Toolbox
##  Copyright : RABERU Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.12)

##==================================================================================================
## Setup project
##==================================================================================================
project(raberu LANGUAGES CXX)
set(PROJECT_VERSION 1.0)

##==================================================================================================
## No in-source build
##==================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[raberu]: In-source build is not recommend")
endif()

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/raberu TYPE INCLUDE)

## =================================================================================================
## Exporting target for external use
## =================================================================================================
add_library(raberu_lib INTERFACE)
target_include_directories(raberu_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
target_compile_options( raberu_lib INTERFACE -Wno-gnu-string-literal-operator-template)
endif()

target_compile_features(raberu_lib INTERFACE cxx_std_20)
add_library(raberu::raberu ALIAS raberu_lib)

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


##==================================================================================================
## Add Doxygen building target
##==================================================================================================
find_package(Doxygen QUIET)

if (DOXYGEN_FOUND)
  message( STATUS "[raberu] Doxygen available")
else (DOXYGEN_FOUND)
  message( STATUS "[raberu] Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

if (DOXYGEN_FOUND)
  set(DOXYGEN_CONFIG ${PROJECT_SOURCE_DIR}/doc/Doxyfile)
  add_custom_target ( doxygen
                      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
                      COMMENT "[raberu] Generating API documentation with Doxygen"
                      VERBATIM
                    )
endif (DOXYGEN_FOUND)
