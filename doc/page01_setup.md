# Setup

## Direct file download

1. Download the one header file `raberu.hpp` :
    ```
    wget https://raw.githubusercontent.com/jfalcou/raberu/main/include/raberu.hpp
    ```
2. Copy it in the location of your choice.

Using **Raberu** boils down to including `raberu.hpp` and compile using C++20.

``` bash
g++ my_app.cpp -I/path/to/raberu -std=c++20
```

## CMake FetchContent

You can also use CMake FetchContent operation and use the `raberu::raberu` library
target that our CMake exports.

``` cmake
##==================================================================================================
## Your project setup
##==================================================================================================
cmake_minimum_required(VERSION 3.2)
project(test_raberu LANGUAGES CXX)

include(FetchContent)

##==================================================================================================
## Fetch Raberu and disable its test targets
##==================================================================================================
set(KUMI_BUILD_TEST    OFF CACHE INTERNAL "OFF")
FetchContent_Declare( raberu
                      GIT_REPOSITORY https://github.com/jfalcou/raberu.git
                      GIT_TAG main
                    )

FetchContent_MakeAvailable(raberu)

##==================================================================================================
## Using Raberu
##==================================================================================================
add_executable( my_app my_app.cpp)
target_link_libraries(my_app raberu::raberu)
```

## CPM Integration
You can install **Raberu** directly via [CPM](https://github.com/cpm-cmake/CPM.cmake). After
[adding CPM to your CMake setup](https://github.com/cpm-cmake/CPM.cmake#adding-cpm), just
add the following commands:

```cmake
include(CPM)

CPMAddPackage ( NAME raberu
                URL https://github.com/jfalcou/raberu/archive/refs/tags/v2.0.zip
                VERSION 2.0
                OPTIONS "RABERU_BUILD_TEST OFF"
              )
```
