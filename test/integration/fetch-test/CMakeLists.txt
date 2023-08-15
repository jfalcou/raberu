##======================================================================================================================
##  RABERU - Fancy Named Parameter Library
##  Copyright : RABERU Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(raberu-fetch-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing FetchContent for branch ${GIT_BRANCH}")

# Enable FetchContent
include(FetchContent)

# Retrieve RABERU from relative git directory
FetchContent_Declare(raberu
  GIT_REPOSITORY "https://github.com/jfalcou/raberu.git"
  GIT_TAG ${GIT_BRANCH}
)

# make available
FetchContent_MakeAvailable(raberu)

add_executable(test_raberu ../main.cpp)
target_link_libraries(test_raberu PUBLIC raberu::raberu)
add_test(NAME test_raberu COMMAND test_raberu)
