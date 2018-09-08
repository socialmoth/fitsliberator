// The ESA/ESO/NASA FITS Liberator - http://code.google.com/p/fitsliberator
//
// Copyright (c) 2004-2010, ESA/ESO/NASA.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the names of the European Space Agency (ESA), the European 
//       Southern Observatory (ESO) and the National Aeronautics and Space 
//       Administration (NASA) nor the names of its contributors may be used to
//       endorse or promote products derived from this software without specific
//       prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL ESA/ESO/NASA BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// =============================================================================
//
// The ESA/ESO/NASA FITS Liberator uses NASA's CFITSIO library, libtiff, 
// TinyXML, Boost C++ Libraries, Object Access Library and Intel Threading 
// Building Blocks.
//
// =============================================================================
//
// Project Executive:
//   Lars Lindberg Christensen
//
// Technical Project Manager:
//   Lars Holm Nielsen
//
// Developers:
//   Kaspar Kirstein Nielsen & Teis Johansen
// 
// Technical, scientific support and testing: 
//   Robert Hurt
//   Davide De Martin
//
// =============================================================================

#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace FitsLiberator {
#ifdef UNICODE
    const wchar_t INDENT[] = L"    ";
#else
    const char INDENT[] = "    ";
#endif

    /** Output a new-line sequence to a specified stream.
        @param s Stream to output to. */
    inline std::basic_ostream<char>&
    newline(std::basic_ostream<char>& s) {
#ifdef WINDOWS
        s.put('\r');
        s.put('\n');
#else 
        s.put('\n');
#endif
        return s;
    }

    /** Output a new-line sequence to a specified stream.
        @param s Stream to output to. */
    inline std::basic_ostream<wchar_t>&
    newline(std::basic_ostream<wchar_t>& s) {
#ifdef WINDOWS
        s.put(L'\r');
        s.put(L'\n');
#else 
        s.put(L'\n');
#endif
        return s;
    }

    inline std::basic_ostream<char>&
    indent(std::basic_ostream<char>& s, int count) {
        while(count > 0) {
            s << INDENT;
            count -= 1;
        }
        return s;
    }

    inline std::basic_ostream<wchar_t>&
    indent(std::basic_ostream<wchar_t>& s, int count) {
        while(count > 0) {
            s << INDENT;
            count -= 1;
        }
        return s;
    }

    template<typename CharT>
    std::vector<std::basic_string<CharT>>
    split(std::basic_string<CharT> text, CharT delimiter)
    {
        auto tokens = std::vector<std::basic_string<CharT>>();
        auto stream = std::basic_istringstream<CharT>(text);
        auto token  = std::string();

        while (std::getline(stream, token, delimiter)) {
            tokens.push_back(std::move(token));
        }

        return tokens;
    }
}

#endif // __TEXT_HPP__