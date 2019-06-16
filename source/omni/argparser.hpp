/*
 * Copyright (c), Zeriph Enterprises
 * All rights reserved.
 * 
 * Contributor(s):
 * Zechariah Perez, omni (at) zeriph (dot) com
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
#include <omni/sequence.hpp>
#include <omni/strings.hpp>
#include <omni/ostream.hpp>
#include <string>

namespace omni {
    namespace application {
        class argparser
        {
            public:
                argparser();
                argparser(const omni::application::argparser& cp);
                argparser(uint32_t ac, const char** av);
                argparser(uint32_t ac, const wchar_t** av);
                explicit argparser(const omni::seq::std_string_t& av);
                explicit argparser(const omni::seq::std_wstring_t& av);
                ~argparser();
                
                uint32_t argc() const { return this->m_argc; }
                omni::seq::string_t argv() const;
                omni::string_t at(uint32_t index) const;
                bool contains(const std::wstring& sw) const;
                bool contains(const std::string& sw) const;
                omni::string_t get_arg(uint32_t index) const;
                omni::string_t get_switch(const std::wstring& sw) const;
                omni::string_t get_switch(const std::string& sw) const;
                omni::seq::string_t get_switches(const omni::string_t& sw) const;
                omni::seq::string_t get_range(std::size_t start, std::size_t end) const;
                std::size_t size() const { return static_cast<std::size_t>(this->m_argc); }
                void set(uint32_t ac, const char** av);
                void set(uint32_t ac, const wchar_t** av);
                void set(const omni::seq::string_t& av);
                omni::string_t to_string_t() const;
                omni::string_t to_string_t(bool includeArg1) const;
                std::string to_string() const;
                std::string to_string(bool includeArg1) const;
                std::wstring to_wstring() const;
                std::wstring to_wstring(bool includeArg1) const;
                operator std::string() const { return this->to_string(false); }
                operator std::wstring() const { return this->to_wstring(false); }
                omni::string_t operator[](const std::string& sw) const;
                omni::string_t operator[](const std::wstring& sw) const;
                omni::string_t operator[](uint32_t index) const;
                omni::application::argparser& operator=(const omni::application::argparser& ap);
                bool operator==(const omni::application::argparser& o) const;
                bool operator!=(const omni::application::argparser& o) const;
                
                OMNI_MEMBERS_FW(omni::application::argparser) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::application::argparser)
                
            private:
                omni::seq::string_t::const_iterator _find(omni::seq::string_t::const_iterator it, const omni::string_t& f) const;
                omni::seq::string_t m_args;
                uint32_t m_argc;
        };
    }
}

#endif // OMNI_ARGPARSER_HPP
