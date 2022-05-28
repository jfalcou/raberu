##==================================================================================================
##  RABERU - Cmpact C++20 Tuple Toolbox
##  Copyright : RABERU Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Compiler options
##==================================================================================================
add_library(raberu_test INTERFACE)

target_compile_features ( raberu_test INTERFACE  cxx_std_20 )
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( raberu_test INTERFACE /W3 /EHsc /Zc:preprocessor)
else()
  target_compile_options( raberu_test INTERFACE -Werror -Wall -Wextra)
endif()

target_include_directories( raberu_test INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                          )

##==================================================================================================
## Make test
##==================================================================================================
function(generate_test file)
  string(REPLACE ".cpp" ".exe" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})
  set(test "rbr-${base}")

  add_executable( ${test}  "${file}")
  target_link_libraries(${test} PUBLIC raberu_test)

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              )

  if (CMAKE_CROSSCOMPILING_CMD)
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:${test}>
            )
  else()
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND $<TARGET_FILE:${test}>
            )
  endif()

  target_include_directories( ${test}
                              PRIVATE
                              ${tts_SOURCE_DIR}/include
                              ${PROJECT_SOURCE_DIR}/test
                              ${PROJECT_SOURCE_DIR}/include
                            )

  add_dependencies(rbr-unit ${test})
endfunction()

add_custom_target(rbr-unit)

##==================================================================================================
## Actual tests
##==================================================================================================
include(${PROJECT_SOURCE_DIR}/test/unit.cmake)
include(${PROJECT_SOURCE_DIR}/test/doc.cmake)
