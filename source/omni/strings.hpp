/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY ZERIPH AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ZERIPH AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(OMNI_STRING_HPP)
#define OMNI_STRING_HPP 1
#include <omni/defs/global.hpp>
#include <omni/string/util.hpp>

/* DEV_NOTE: including omni/strings.hpp gives you cstring and wstring library functionality
to easily operate on std::string, std::wstring, char and wchar_t referencing the
appropriate namespace (cstring for std::string and wstring for std::wstring). */
#if !defined(OMNI_NO_CSTRING_IMPL) // define this if you only want omni::wstring header
    #include <omni/string/cstring.hpp>
#endif
#if !defined(OMNI_NO_WSTRING_IMPL) // define this if you only want omni::cstring header
    #include <omni/string/wstring.hpp>
#endif

/* DEV_NOTE: for more information on the logic/idea behind the segregation, see the DEV_NOTE
in string/util.hpp */

#endif // OMNI_STRING_HPP
