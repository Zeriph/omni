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
#if !defined(OMNI_NET_VERSION_HPP)
#define OMNI_NET_VERSION_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/string_t.hpp>
#include <omni/sequence.hpp>
#include <omni/ostream.hpp>
#include <omni/exception.hpp>
#include <omni/string/cstring.hpp>
#include <omni/string/wstring.hpp>

#if defined(OMNI_SAFE_NET_VERSION)
    #include <omni/sync/basic_lock.hpp>
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_NVER_MTX_FW m_mtx(),
    #define OMNI_NVER_ALOCK_FW    omni::sync::scoped_lock<omni::sync::basic_lock> uuid12345(&this->m_mtx);
    #define OMNI_NVER_OLOCK_FW(o) omni::sync::scoped_lock<omni::sync::basic_lock> uuid54321(&o.m_mtx);
    #define OMNI_NVER_MLOCK_FW    this->m_mtx.lock();
    #define OMNI_NVER_ULOCK_FW    this->m_mtx.unlock();
#else
    #define OMNI_SAFE_NVER_MTX_FW
    #define OMNI_NVER_ALOCK_FW
    #define OMNI_NVER_OLOCK_FW(o)
    #define OMNI_NVER_MLOCK_FW
    #define OMNI_NVER_ULOCK_FW
#endif

/* these defines are used (instead of just using the defaults)
to aid in compiler times and memory usage (the compiler does not
have to rearrange the variables on construction to match the way
the class is built, as well it does not have to do extra padding) */
#if defined(OMNI_DISPOSE_EVENT)
    #define OMNI_NVER_DIS_FW disposing(),
    #define OMNI_NVER_DISCP_FW disposing(cp.disposing),
#else
    #define OMNI_NVER_DIS_FW 
    #define OMNI_NVER_DISCP_FW
#endif

#if defined(OMNI_OBJECT_NAME)
    #define OMNI_NVER_NAME_FW name(OMNI_STRW("omni::version")),
    #define OMNI_NVER_NAMECP_FW name(cp.name),
#else
    #define OMNI_NVER_NAME_FW 
    #define OMNI_NVER_NAMECP_FW
#endif
#define OMNI_NVER_CTOR_FW OMNI_NVER_DIS_FW OMNI_NVER_NAME_FW OMNI_SAFE_NVER_MTX_FW
#define OMNI_NVER_CPCTOR_FW OMNI_NVER_DISCP_FW OMNI_NVER_NAMECP_FW OMNI_SAFE_NVER_MTX_FW

namespace omni {
    namespace net {
        class version
        {
            public:
                version() :
                    OMNI_NVER_CTOR_FW
                    m_maj(0), m_min(0), m_bld(-1), m_rev(-1)
                {
                    OMNI_DV5_FW("created net version ", this->to_string_t());
                }

                version(int32_t mj) :
                    OMNI_NVER_CTOR_FW
                    m_maj(0), m_min(0), m_bld(-1), m_rev(-1)
                {
                    if (mj < 0) { OMNI_ERR_FW("Invalid version specified", omni::exceptions::invalid_version("major")) }
                    this->m_maj = mj;
                    OMNI_DV5_FW("created net version ", this->to_string_t());
                }

                version(int32_t mj, int32_t mn) :
                    OMNI_NVER_CTOR_FW
                    m_maj(mj), m_min(mn), m_bld(-1), m_rev(-1)
                {
                    if (mj < 0) { OMNI_ERR_FW("Invalid major version specified", omni::exceptions::invalid_version("major")) }
                    if (mn < 0) { OMNI_ERR_FW("Invalid minor version specified", omni::exceptions::invalid_version("minor")) }
                    this->m_maj = mj;
                    this->m_min = mn;
                    OMNI_DV5_FW("created net version ", this->to_string_t());
                }

                version(int32_t mj, int32_t mn, int32_t bld) :
                    OMNI_NVER_CTOR_FW
                    m_maj(mj), m_min(mn), m_bld(bld), m_rev(-1)
                {
                    if (mj < 0) { OMNI_ERR_FW("Invalid major version specified", omni::exceptions::invalid_version("major")) }
                    if (mn < 0) { OMNI_ERR_FW("Invalid minor version specified", omni::exceptions::invalid_version("minor")) }
                    if (bld < 0) { OMNI_ERR_FW("Invalid build version specified", omni::exceptions::invalid_version("build")) }
                    this->m_maj = mj;
                    this->m_min = mn;
                    this->m_bld = bld;
                    OMNI_DV5_FW("created net version ", this->to_string_t());
                }

                version(int32_t mj, int32_t mn, int32_t bld, int32_t rev) :
                    OMNI_NVER_CTOR_FW
                    m_maj(mj), m_min(mn), m_bld(bld), m_rev(rev)
                {
                    if (mj < 0) { OMNI_ERR_FW("Invalid major version specified", omni::exceptions::invalid_version("major")) }
                    if (mn < 0) { OMNI_ERR_FW("Invalid minor version specified", omni::exceptions::invalid_version("minor")) }
                    if (bld < 0) { OMNI_ERR_FW("Invalid build version specified", omni::exceptions::invalid_version("build")) }
                    if (rev < 0) { OMNI_ERR_FW("Invalid revision specified", omni::exceptions::invalid_version("revision")) }
                    this->m_maj = mj;
                    this->m_min = mn;
                    this->m_bld = bld;
                    this->m_rev = rev;
                    OMNI_DV5_FW("created net version ", this->to_string_t());
                }

                OMNI_EXPLICIT version(const std::string& str) :
                    OMNI_NVER_CTOR_FW
                    m_maj(0), m_min(0), m_bld(-1), m_rev(-1)
                {
                    omni::net::version tmp(omni::net::version::_parse(str));
                    this->m_maj = tmp.m_maj;
                    this->m_min = tmp.m_min;
                    this->m_bld = tmp.m_bld;
                    this->m_rev = tmp.m_rev;
                    OMNI_DV5_FW("created net version ", this->to_string_t());
                }

                OMNI_EXPLICIT version(const std::wstring& str) :
                    OMNI_NVER_CTOR_FW
                    m_maj(0), m_min(0), m_bld(-1), m_rev(-1)
                {
                    omni::net::version tmp(omni::net::version::_parse(str));
                    this->m_maj = tmp.m_maj;
                    this->m_min = tmp.m_min;
                    this->m_bld = tmp.m_bld;
                    this->m_rev = tmp.m_rev;
                    OMNI_DV5_FW("created net version ", this->to_string_t());
                }

                version(const omni::net::version& cp) :
                    OMNI_NVER_CPCTOR_FW
                    m_maj(0), m_min(0), m_bld(-1), m_rev(-1)
                {
                    OMNI_NVER_OLOCK_FW(cp)
                    OMNI_ASSIGN_FW(cp)
                    this->m_maj = cp.m_maj;
                    this->m_min = cp.m_min;
                    this->m_bld = cp.m_bld;
                    this->m_rev = cp.m_rev;
                    OMNI_DV5_FW("created net version ", this->to_string_t());
                }
                
                ~version()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                }

                int32_t hash_code() const
                {
                    OMNI_VER_ALOCK_FW
                    // DEV_NOTE: this is a comment from the .NET source on the Version class
                    // Let's assume that most version numbers will be pretty small and just
                    // OR some lower order bits together.
                    return ((this->m_maj & 0x0000000F) << 28) |
                           ((this->m_min & 0x000000FF) << 20) |
                           ((this->m_bld & 0x000000FF) << 12) |
                           (this->m_rev & 0x00000FFF);
                }
                
                // maj/major cannot be used as a name (some compilers complain)
                inline int32_t major_number() const
                {
                    OMNI_NVER_ALOCK_FW
                    return this->m_maj;
                }
                
                // min/minor cannot be used as a name (some compilers complain)
                inline int32_t minor_number() const
                {
                    OMNI_NVER_ALOCK_FW
                    return this->m_min;
                }
                
                inline int32_t build() const
                {
                    OMNI_NVER_ALOCK_FW
                    return this->m_bld;
                }
                
                inline int32_t revision() const
                {
                    OMNI_NVER_ALOCK_FW
                    return this->m_rev;
                }

                inline int16_t major_revision() const
                {
                    OMNI_NVER_ALOCK_FW
                    return static_cast<int16_t>(this->m_rev >> 16);
                }

                inline int16_t minor_revision() const
                {
                    OMNI_NVER_ALOCK_FW
                    return static_cast<int16_t>(this->m_rev & 0xFFFF);
                }
                
                inline omni::string_t to_string_t() const
                {
                    return this->_to_string_t<omni::string_t, omni::sstream_t>();
                }

                inline omni::string_t to_string_t(uint8_t field_count) const
                {
                    return this->_to_string<omni::string_t, omni::sstream_t>(field_count);
                }
                
                inline std::string to_string() const
                {
                    return this->_to_string_t<std::string, std::stringstream>();
                }
                
                inline std::string to_string(uint8_t field_count) const
                {
                    return this->_to_string<std::string, std::stringstream>(field_count);
                }
                
                inline std::wstring to_wstring() const
                {
                    return this->_to_string_t<std::wstring, std::wstringstream>();
                }

                inline std::wstring to_wstring(uint8_t field_count) const
                {
                    return this->_to_string<std::wstring, std::wstringstream>(field_count);
                }
                
                operator std::string() const
                {
                    return this->to_string();
                }
                
                operator std::wstring() const
                {
                    return this->to_wstring();
                }
                
                omni::net::version& operator=(const omni::net::version& o)
                {
                    OMNI_NVER_ALOCK_FW
                    OMNI_NVER_OLOCK_FW(o)
                    OMNI_ASSIGN_FW(o)
                    this->m_maj = o.m_maj;
                    this->m_min = o.m_min;
                    this->m_bld = o.m_bld;
                    this->m_rev = o.m_rev;
                    return *this;
                }

                omni::net::version& operator=(const std::string& str)
                {
                    OMNI_NVER_ALOCK_FW
                    omni::net::version tmp(omni::net::version::_parse(str));
                    this->m_maj = tmp.m_maj;
                    this->m_min = tmp.m_min;
                    this->m_bld = tmp.m_bld;
                    this->m_rev = tmp.m_rev;
                    return *this;
                }

                omni::net::version& operator=(const std::wstring& str)
                {
                    OMNI_NVER_ALOCK_FW
                    omni::net::version tmp(omni::net::version::_parse(str));
                    this->m_maj = tmp.m_maj;
                    this->m_min = tmp.m_min;
                    this->m_bld = tmp.m_bld;
                    this->m_rev = tmp.m_rev;
                    return *this;
                }

                bool operator==(const std::string& str) const
                {
                    OMNI_NVER_ALOCK_FW
                    omni::net::version t;
                    if (!omni::net::version::_try_parse(str, t)) { return false; }
                    return (*this == t);
                }

                bool operator==(const std::wstring& str) const
                {
                    OMNI_NVER_ALOCK_FW
                    omni::net::version t;
                    if (!omni::net::version::_try_parse(str, t)) { return false; }
                    return (*this == t);
                }

                bool operator==(const omni::net::version& o) const
                {
                    if (this == &o) { return true; }
                    OMNI_NVER_ALOCK_FW
                    OMNI_NVER_OLOCK_FW(o)
                    return (
                            this->m_maj == o.m_maj &&
                            this->m_min == o.m_min &&
                            this->m_bld == o.m_bld &&
                            this->m_rev == o.m_rev
                           )
                            OMNI_EQUAL_FW(o);
                }

                bool operator!=(const omni::net::version &o) const
                {
                    return !(*this == o);
                }
                
                OMNI_MEMBERS_FW(omni::net::version) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::net::version)

                static inline omni::net::version parse(const std::string& str)
                {
                    return omni::net::version::_parse(str);
                }

                static inline omni::net::version parse(const std::wstring& str)
                {
                    return omni::net::version::_parse(str);
                }
                
                static inline bool try_parse(const std::string& str, omni::net::version& out)
                {
                    return omni::net::version::_try_parse(str, out);
                }
                
                static inline bool try_parse(const std::wstring& str, omni::net::version& out)
                {
                    return omni::net::version::_try_parse(str, out);
                }

            private:
                int32_t m_maj;
                int32_t m_min;
                int32_t m_bld;
                int32_t m_rev;
                #if defined(OMNI_SAFE_VERSION)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                template < typename STR, typename SS >
                inline STR _to_string_t() const
                {
                    if (this->m_bld == -1) { return this->_to_string< STR, SS >(2); }
                    if (this->m_rev == -1) { return this->_to_string< STR, SS >(3); }
                    return this->_to_string< STR, SS >(4);
                }

                template < typename STR, typename SS >
                inline STR _to_string(uint8_t field_count) const
                {
                    if (field_count == 0) { return STR(); }
                    if (field_count > 4) { OMNI_ERR_FW("Invalid range specified", omni::exceptions::invalid_range()) }
                    SS o;
                    OMNI_NVER_ALOCK_FW
                    o << this->m_maj;
                    if (field_count > 1) { o << "." << this->m_min; }
                    if (field_count > 2) {
                        if (this->m_bld == -1) {
                            OMNI_ERR_FW("Invalid build version in to_string", omni::exceptions::invalid_version("build"))
                        }
                        o << "." << this->m_bld;
                    }
                    if (field_count > 3) {
                        if (this->m_rev == -1) {
                            OMNI_ERR_FW("Invalid revision in to_string", omni::exceptions::invalid_version("revision"))
                        }
                        o << "." << this->m_rev;
                    }
                    return o.str();
                }

                static omni::net::version _parse(const std::string& v)
                {
                    omni::net::version ret;
                    if (!_try_parse(v, ret)) {
                        OMNI_ERR_FW("Invalid version string specified", omni::exceptions::invalid_version())
                    }
                    return ret;
                }

                static omni::net::version _parse(const std::wstring& v)
                {
                    omni::net::version ret;
                    if (!_try_parse(v, ret)) {
                        OMNI_ERR_FW("Invalid version string specified", omni::exceptions::invalid_version())
                    }
                    return ret;
                }

                static bool _try_parse(const std::string& v, omni::net::version& ret)
                {
                    omni::seq::std_string_t s = omni::cstring::split(v, ".");
                    if (s.size() > 4) {
                        return false;
                    }
                    omni::seq::std_string_t::const_iterator it = s.begin();
                    while (it != s.end()) {
                        if (it->empty() || !omni::cstring::is_numeric(*it)) {
                            return false;
                        }
                        ++it;
                    }
                    it = s.begin();
                    OMNI_NVER_OLOCK_FW(ret)
                    if (it != s.end()) { ret.m_maj = omni::cstring::type_cast<int32_t>(*it); ++it; }
                    if (it != s.end()) { ret.m_min = omni::cstring::type_cast<int32_t>(*it); ++it; }
                    if (it != s.end()) { ret.m_bld = omni::cstring::type_cast<int32_t>(*it); ++it; }
                    if (it != s.end()) { ret.m_rev = omni::cstring::type_cast<int32_t>(*it); ++it; }
                    return true;
                }

                static bool _try_parse(const std::wstring& v, omni::net::version& ret)
                {
                    omni::seq::std_wstring_t s = omni::wstring::split(v, L".");
                    if (s.size() > 4) {
                        return false;
                    }
                    omni::seq::std_wstring_t::const_iterator it = s.begin();
                    while (it != s.end()) {
                        if (it->empty() || !omni::wstring::is_numeric(*it)) {
                            return false;
                        }
                        ++it;
                    }
                    it = s.begin();
                    OMNI_NVER_OLOCK_FW(ret)
                    if (it != s.end()) { ret.m_maj = omni::wstring::type_cast<int32_t>(*it); ++it; }
                    if (it != s.end()) { ret.m_min = omni::wstring::type_cast<int32_t>(*it); ++it; }
                    if (it != s.end()) { ret.m_bld = omni::wstring::type_cast<int32_t>(*it); ++it; }
                    if (it != s.end()) { ret.m_rev = omni::wstring::type_cast<int32_t>(*it); ++it; }
                    return true;
                }
        };
    }
}

#endif // OMNI_NET_VERSION_HPP
