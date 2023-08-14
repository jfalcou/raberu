##======================================================================================================================
##  RABERU - Fancy Named Parameter Library
##  Copyright : RABERU Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
copa_setup_test_targets()
set(root "${CMAKE_SOURCE_DIR}/test")

copa_glob_unit( PATTERN "unit/*.cpp"
                QUIET RELATIVE ${root} INTERFACE raberu_test DEPENDENCIES raberu-standalone
              )

copa_glob_unit( PATTERN "doc/*.cpp"
                QUIET RELATIVE ${root} INTERFACE raberu_test DEPENDENCIES raberu-standalone
              )
