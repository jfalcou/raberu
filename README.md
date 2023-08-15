<img src="https://raw.githubusercontent.com/jfalcou/raberu/main/doc/logo.png" alt="raberu Logo : Red parens in a red square box on white background" data-canonical-src="https://raw.githubusercontent.com/jfalcou/ofw/raberu/doc/logo.png" align="left"  width="12%" height="12%" />

# RABERU - The Fancy Named Parameters Library

**RABERU** provides a way to define and use named parameters, *i.e* a list of values assigned to
arbitrary keyword-like identifiers, to functions.

It does so by providing:

  * a protocol to define such keywords.
  * a type to process such aggregate of parameters.
  * a `constexpr`-compatible implementation for all of those.

# A Short Example

[See it live on Compiler Explorer](https://godbolt.org/z/oWjP44n57)

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
#include <raberu/raberu.hpp>
#include <iostream>
#include <string>

template<rbr::concepts::option P0, rbr::concepts::option P1>
auto replicate( P0 p0, P1 p1 )
{
  auto const params = rbr::settings(p0,p1);
  return std::string( params["replication"_kw], params["letter"_kw] );
}

int main()
{
  std::cout << replicate("replication"_kw = 9, "letter"_kw = 'z'   ) << "\n";
  std::cout << replicate("letter"_kw = '!'   , "replication"_kw = 3) << "\n";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Licence

This library is licensed under the [Boost Software License](https://opensource.org/licenses/BSL-1.0):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ none
Copyright : RABERU Project Contributors

Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the
software and accompanying documentation covered by this license (the "Software") to use, reproduce,
display, distribute, execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to do so, all subject to the
following:

The copyright notices in the Software and this entire statement, including the above license grant,
this restriction and the following disclaimer, must be included in all copies of the Software, in
whole or in part, and all derivative works of the Software, unless such copies or derivative works
are solely in the form of machine-executable object code generated by a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
NON-INFRINGEMENT. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE
BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
