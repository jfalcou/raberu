<img src="https://raw.githubusercontent.com/jfalcou/raberu/main/docs/logo.png" alt="raberu Logo : Red parens in a red square box on white background" data-canonical-src="https://raw.githubusercontent.com/jfalcou/ofw/raberu/docs/logo.png" align="left"  width="12%" height="12%" />

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
#include <raberu.hpp>
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

This library is licensed under the [MIT License](http://opensource.org/licenses/MIT):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ none
Copyright : RABERU Contributors & Maintainers

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
