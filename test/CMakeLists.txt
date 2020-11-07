## -------------------------------------------------------------------------------------------------
##  RABERU - Fancy Parameters Library
##  Copyright 2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
## -------------------------------------------------------------------------------------------------

##==================================================================================================
## Compiler options
##==================================================================================================
if( MSVC )
  set( options /std:c++latest /W3 /EHsc )
else()
  set( options -std=c++20 -Wall -Wunused-parameter -Werror)
endif()

##==================================================================================================
## Setup TTS
##==================================================================================================
set(TTS_BUILD_TEST    OFF CACHE INTERNAL "OFF")
set(TTS_IS_DEPENDENT  ON  CACHE INTERNAL "ON")

include(FetchContent)
FetchContent_Declare( tts
                      GIT_REPOSITORY https://github.com/jfalcou/tts.git
                      GIT_TAG main
                    )

FetchContent_MakeAvailable(tts)

##==================================================================================================
## Make test
##==================================================================================================
function(generate_test root file)
  string(REPLACE ".cpp" ".exe" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})
  set(test "${root}.${base}")

  add_executable( ${test}  "${file}")
  target_compile_options  ( ${test} PUBLIC ${options} )

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              )

  if (CMAKE_CROSSCOMPILING_CMD)
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:${test}> --no-color --pass
            )
  else()
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND $<TARGET_FILE:${test}> --no-color --pass
            )
  endif()

  set_target_properties ( ${test} PROPERTIES
                          EXCLUDE_FROM_DEFAULT_BUILD TRUE
                          EXCLUDE_FROM_ALL TRUE
                          ${MAKE_UNIT_TARGET_PROPERTIES}
                        )

  target_include_directories( ${test}
                              PRIVATE
                              ${tts_SOURCE_DIR}/include
                              ${PROJECT_SOURCE_DIR}/test
                              ${PROJECT_SOURCE_DIR}/include
                            )

  add_dependencies(unit ${test})
endfunction()

##==================================================================================================
## Meta-target
##==================================================================================================
add_custom_target(unit)
add_custom_target(raberu.exe)
add_dependencies(unit raberu.exe)

##==================================================================================================
## Actual tests
##==================================================================================================
generate_test("raberu" "contains.cpp")
generate_test("raberu" "get.cpp")
generate_test("raberu" "get_or.cpp")
generate_test("raberu" "get_or_eval.cpp")
generate_test("raberu" "interface.cpp")
generate_test("raberu" "maybe_get.cpp")
generate_test("raberu" "size.cpp")
generate_test("raberu" "subscript.cpp")
