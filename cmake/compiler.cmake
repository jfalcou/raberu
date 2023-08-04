##======================================================================================================================
##  RABERU - Fancy Named Parameter Library
##  Copyright : RABERU Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Compiler options
##======================================================================================================================
add_library(raberu_test INTERFACE)

target_compile_features ( raberu_test INTERFACE  cxx_std_20 )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options( raberu_test INTERFACE /W3 /EHsc )
  else()
    target_compile_options( raberu_test INTERFACE -Werror -Wall -Wextra -Wunused-variable
                                                  -Wdocumentation -Wno-gnu-string-literal-operator-template
                          )
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( raberu_test INTERFACE /W3 /EHsc /Zc:preprocessor)
else()
  target_compile_options( raberu_test INTERFACE -Werror -Wall -Wextra -Wunused-variable)
endif()

target_include_directories( raberu_test INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                          ) 
