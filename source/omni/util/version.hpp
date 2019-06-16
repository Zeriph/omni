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
#if !defined(OMNI_VERSION_HPP)
#define OMNI_VERSION_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/string_t.hpp>
#include <omni/sequence.hpp>
#include <omni/ostream.hpp>
#include <omni/exception.hpp>

namespace omni {
    namespace util {
        class version
        {
            public:
                version();
                version(uint16_t mj);
                version(uint16_t mj, uint16_t mn);
                version(uint16_t mj, uint16_t mn, uint32_t bld);
                version(uint16_t mj, uint16_t mn, uint32_t bld, uint64_t rv);
                explicit version(const std::string& str);
                explicit version(const std::wstring& str);
                version(const omni::util::version& cp);
                
                virtual ~version()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                }
                
                static inline omni::util::version parse(const std::string& str)
                {
                    return omni::util::version::_parse(str);
                }
                
                static inline bool tryparse(const std::string& str, omni::util::version& out)
                {
                    return omni::util::version::_tryparse(str, out);
                }
                
                // maj/major can't be used as a name (some compilers complain)
                inline uint16_t major_number() const
                {
                    return this->m_maj;
                }
                
                // min/minor can't be used as a name (some compilers complain)
                inline uint16_t minor_number() const
                {
                    return this->m_min;
                }
                
                inline uint32_t build() const
                {
                    return this->m_bld;
                }
                
                inline uint64_t revision() const
                {
                    return this->m_rev;
                }
                
                inline omni::string_t to_string_t() const
                {
                    omni::sstream_t o;
                    o << this->m_maj << "." << this->m_min << "." <<
                         this->m_bld << "." << this->m_rev;
                    return o.str();
                }
                
                inline std::string to_string() const
                {
                    std::stringstream o;
                    o << this->m_maj << "." << this->m_min << "." <<
                         this->m_bld << "." << this->m_rev;
                    return o.str();
                }
                
                inline std::wstring to_wstring() const
                {
                    std::wstringstream o;
                    o << this->m_maj << "." << this->m_min << "." <<
                         this->m_bld << "." << this->m_rev;
                    return o.str();
                }
                
                operator std::string() const
                {
                    return this->to_string();
                }
                
                operator std::wstring() const
                {
                    return this->to_wstring();
                }
                
                omni::util::version& operator=(const omni::util::version& o)
                {
                    OMNI_ASSIGN_FW(o)
                    this->_copy(o);
                    return *this;
                }

                omni::util::version& operator=(const std::string& str)
                {
                    this->_copy(omni::util::version::_parse(str));
                    return *this;
                }

                omni::util::version& operator=(const std::wstring& str)
                {
                    this->_copy(omni::util::version::_parse(str));
                    return *this;
                }

                bool operator==(const std::string& str) const
                {
                    omni::util::version t;
                    if (!omni::util::version::_tryparse(str, t)) { return false; }
                    return (*this == t);
                }

                bool operator==(const std::wstring& str) const
                {
                    omni::util::version t;
                    if (!omni::util::version::_tryparse(str, t)) { return false; }
                    return (*this == t);
                }

                bool operator==(const omni::util::version& o) const
                {
                    if (this == &o) { return true; }
                    return (this->m_maj == o.m_maj &&
                            this->m_min == o.m_min &&
                            this->m_bld == o.m_bld &&
                            this->m_rev == o.m_rev)
                            OMNI_EQUAL_FW(o);
                }

                bool operator!=(const omni::util::version &o) const
                {
                    return !(*this == o);
                }
                
                OMNI_MEMBERS_FW(omni::util::version) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::util::version)
                
            private:
                static omni::util::version _parse(const std::string& v);
                static omni::util::version _parse(const std::wstring& v);
                static bool _tryparse(const std::string& v, omni::util::version& _out);
                static bool _tryparse(const std::wstring& v, omni::util::version& _out);
                
                void _copy(const omni::util::version& o)
                {
                    this->m_maj = o.m_maj;
                    this->m_min = o.m_min;
                    this->m_bld = o.m_bld;
                    this->m_rev = o.m_rev;
                }
                
                /** The major version number */
                uint16_t m_maj; // g++ doesn't like major/minor as member names???
                /** The minor version number */
                uint16_t m_min;
                /** The build version number */
                uint32_t m_bld;
                /** The revision number */
                uint64_t m_rev;
        };
    }
}

#endif // OMNI_VERSION_HPP
