/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
#include <raberu.hpp>
#include <iostream>

using namespace rbr::literals;

inline constexpr auto is_modal = "is_modal"_fl;
inline constexpr auto autosave = rbr::flag("autosave"_id);

template<rbr::concepts::option... Params>
void check_options(Params const&... ps)
{
  auto s = rbr::settings(ps...);
  std::cout << "Modal window: " << std::boolalpha << s[is_modal] << " - "
            << "autosave: "     << std::boolalpha << s[autosave] << "\n";
}

int main()
{
  check_options();
  check_options(autosave);
  check_options(is_modal);
  check_options(autosave,is_modal);
  check_options(is_modal,autosave);
}
