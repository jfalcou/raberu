##======================================================================================================================
##  RABERU - Fancy Named Parameter Library
##  Copyright : RABERU Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.18)
project(raberu-cpm-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing CPM for branch ${GIT_BRANCH}")

# Setup CPM
include(cpm.cmake)

# Add dependencies
CPMAddPackage ( NAME raberu
                GIT_REPOSITORY "https://github.com/jfalcou/raberu.git"
                GIT_TAG "${GIT_BRANCH}"
                OPTIONS "RABERU_BUILD_TEST OFF"
              )

# Use RABERU
add_executable(test_raberu ../main.cpp)
target_link_libraries(test_raberu PUBLIC raberu::raberu)
add_test(NAME test_raberu COMMAND test_raberu)
