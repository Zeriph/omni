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
#if !defined(OMNI_ARGPARSER_HPP)
#define OMNI_ARGPARSER_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/seq_t.hpp>
#include <omni/strings.hpp>
#include <omni/ostream.hpp>
#include <deque>
#include <string>

namespace omni {
    namespace application {
        class argparser
        {
            public:
                argparser();
                argparser(const omni::application::argparser& cp);
                argparser(const unsigned int& ac, const char** av);
                argparser(const unsigned int& ac, const wchar_t** av);
                explicit argparser(const OMNI_SEQ_T<std::string>& av);
                explicit argparser(const OMNI_SEQ_T<std::wstring>& av);
                ~argparser();
                
                unsigned int argc() const { return this->m_argc; }
                OMNI_SEQ_T<omni::string_t> argv() const;
                omni::string_t at(const unsigned int& index) const;
                bool contains(const std::wstring& sw) const;
                bool contains(const std::string& sw) const;
                omni::string_t get_arg(const unsigned int& index) const;
                omni::string_t get_switch(const std::wstring& sw) const;
                omni::string_t get_switch(const std::string& sw) const;
                OMNI_SEQ_T<omni::string_t> get_switches(const omni::string_t& sw) const;
                OMNI_SEQ_T<omni::string_t> get_range(std::size_t start, std::size_t end) const;
                std::size_t size() const { return static_cast<std::size_t>(this->m_argc); }
                void set(const unsigned int& ac, const char** av);
                void set(const unsigned int& ac, const wchar_t** av);
                void set(const OMNI_SEQ_T<omni::string_t>& av);
                const omni::string_t to_string_t() const;
                const omni::string_t to_string_t(bool includeArg1) const;
                const std::string to_string() const;
                const std::string to_string(bool includeArg1) const;
                const std::wstring to_wstring() const;
                const std::wstring to_wstring(bool includeArg1) const;
                operator std::string() const { return this->to_string(false); }
                operator std::wstring() const { return this->to_wstring(false); }
                omni::string_t operator[](const std::string& sw) const;
                omni::string_t operator[](const std::wstring& sw) const;
                omni::string_t operator[](const unsigned int& index) const;
                omni::application::argparser& operator=(const omni::application::argparser& ap);
                bool operator==(const omni::application::argparser& o) const;
                bool operator!=(const omni::application::argparser& o) const;
                
                OMNI_MEMBERS_FW(omni::application::argparser) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::application::argparser)
                
            private:
                std::deque<omni::string_t>::const_iterator _find(std::deque<omni::string_t>::const_iterator it, const omni::string_t& f) const;
                
                #if defined(OMNI_TYPE_INFO)
                    omni::type<omni::application::argparser> m_type;
                #endif
                std::deque<omni::string_t> m_args;
                unsigned int m_argc;
        };
    }
}

#endif // OMNI_ARGPARSER_HPP
