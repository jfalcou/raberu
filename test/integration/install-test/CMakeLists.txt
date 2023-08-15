##======================================================================================================================
##  RABERU - Fancy Named Parameter Library
##  Copyright : RABERU Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(raberu-install-test LANGUAGES CXX)
enable_testing()

find_package(raberu CONFIG REQUIRED)
add_executable(test_raberu ../main.cpp)
target_link_libraries(test_raberu PUBLIC raberu::raberu)
add_test(NAME test_raberu COMMAND test_raberu)
