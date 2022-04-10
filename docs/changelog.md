# Version 2.0 - Past Prologue

## Bug Fixes
* Moved from `pragma once` to `#ifndef` to allow for multiple raberu files to coexist in multiple projects.
* Fixed a regression in Visual Studio that affected ability to run tests.
* Fix #6 - Compile-time ID are now properly displayed and compared without any issues due to terminal `\0`.

## New Features
* Fix #4 - Simplify and generalize custom keyword generation
  A new CRTP class `rbr::as_keyword` streamlines the definition of compact keyword by users while
  supporting the whole range of built-in keywords. Associated documentation has been updated.

* Fix #2 - Implement direct keyword value access
  Keyword can now fetch themselves from a bundles of options. E.g

  ``` c++
  inline constexpr auto coord_    = "coord"_kw;
  inline constexpr auto is_modal_ = "is_modal"_fl;

  auto x = coord_(coord_ = "Jane"s, is_modal_);
  ```

* Fix #5 - Mass extractors for keyword and values
  `rbr::keywords` and`rbr::values` can be used to retrieve a tuple-like object containing all the
  keywords or values from a bundle of options.

* `rbr::get_type` is removed and is replaced by `rbr::fetch` and `rbr::result::fetch_t`.
  This functions provides an infix syntax for options access.

# Version 1.0 - Emissary

## First autonomous public release.

**RABERU** (ラベル組) is now independent of the OFW repository.
