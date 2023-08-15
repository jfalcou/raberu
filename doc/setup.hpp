#error DO NOT INCLUDE - DOCUMENTATION PURPOSE ONLY

//==================================================================================================
/**
  @page  setup  Setup

  @tableofcontents

  @section setup-source Install from the source

  Code source of **RABERU** is available on GitHub and can be retrieved via the following command:

  @code
  $ git clone https://github.com/jfalcou/raberu.git
  @endcode

  Once retrieved, you should have a `raberu` folder which contains the whole source code.

  Create a `build` directory here and enter it. Once in the `build` directory,
  you can use  **CMake** to generate the build system for **RABERU**. We recommend using
  Ninja but any build system is fine.

  @code
  $ mkdir build
  $ cd build
  $ cmake .. -G Ninja
  @endcode

  Once **CMake** completes, you can use the `install` target to build and install **RABERU**.
  By default, the library will be installed in the `/usr/local` directory, thus requiring
  root privileges.

  @code
  $ sudo ninja install
  @endcode

  You can select an alternative installation path by specifying the `CMAKE_INSTALL_PREFIX`
  option at configuration time.

  @code
  $ cmake .. -G Ninja -DCMAKE_INSTALL_PREFIX=path/to/install
  $ ninja install
  @endcode

  Once installed, **RABERU** is usable directly by providing the path to its installed files.

  @section setup-standalone Standalone setup

  You can also use **RABERU** via a single standalone file that can be vendored in your own project without
  having to deal with **RABERU** as a dependency.

  Simply use `wget` to fetch the latest version and place it where you want:

  @code
  wget https://raw.githubusercontent.com/jfalcou/raberu/main/standalone/raberu/raberu.hpp
  @endcode

  Use **RABERU** by just compiling your code with the include path pointing to the location of this single file.

  @section setup-fetchcontent CMake FetchContent

  You can also use CMake FetchContent operation and use the `raberu::raberu` library target that our CMake exports.

  @code{cmake}
  ##==================================================================================================
  ## Your project setup
  ##==================================================================================================
  cmake_minimum_required(VERSION 3.22)
  project(raberu-fetch LANGUAGES CXX)

  include(FetchContent)
  FetchContent_Declare(raberu GIT_REPOSITORY "https://github.com/jfalcou/raberu.git")
  FetchContent_MakeAvailable(raberu)

  add_executable(test_raberu ../main.cpp)
  target_link_libraries(test_raberu PUBLIC raberu::raberu)
  @endcode

  @section setup-cpm Setup with CPM

  The **RABERU** library can be setup using [CPM](https://github.com/cpm-cmake/CPM.cmake):

  @code{cmake}
  ##==================================================================================================
  ## Your project setup
  ##==================================================================================================
  cmake_minimum_required(VERSION 3.18)
  project(raberu-cpm LANGUAGES CXX)

  # Setup CPM - See https://github.com/cpm-cmake/CPM.cmake#adding-cpm
  include(cpm.cmake)

  CPMAddPackage ( NAME raberu
                  GIT_REPOSITORY "https://github.com/jfalcou/raberu.git"
                  OPTIONS "RABERU_BUILD_TEST OFF"
                )

  add_executable(test_raberu ../main.cpp)
  target_link_libraries(test_raberu PUBLIC raberu::raberu)
  @endcode
**/
//==================================================================================================
