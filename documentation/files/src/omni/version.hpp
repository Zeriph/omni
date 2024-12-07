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
#include <omni/string/cstring.hpp>
#include <omni/string/wstring.hpp>

#if defined(OMNI_SAFE_VERSION)
    #include <omni/sync/basic_lock.hpp>
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_VER_MTX_FW m_mtx(),
    #define OMNI_VER_ALOCK_FW    omni::sync::scoped_lock<omni::sync::basic_lock> uuid12345(&this->m_mtx);
    #define OMNI_VER_OLOCK_FW(o) omni::sync::scoped_lock<omni::sync::basic_lock> uuid54321(&o.m_mtx);
    #define OMNI_VER_MLOCK_FW    this->m_mtx.lock();
    #define OMNI_VER_ULOCK_FW    this->m_mtx.unlock();
#else
    #define OMNI_SAFE_VER_MTX_FW
    #define OMNI_VER_ALOCK_FW
    #define OMNI_VER_OLOCK_FW(o)
    #define OMNI_VER_MLOCK_FW
    #define OMNI_VER_ULOCK_FW
#endif

/* these defines are used (instead of just using the defaults)
to aid in compiler times and memory usage (the compiler does not
have to rearrange the variables on construction to match the way
the class is built, as well it does not have to do extra padding) */
#if defined(OMNI_DISPOSE_EVENT)
    #define OMNI_VERSION_DIS_FW disposing(),
    #define OMNI_VERSION_DISCP_FW disposing(cp.disposing),
#else
    #define OMNI_VERSION_DIS_FW 
    #define OMNI_VERSION_DISCP_FW
#endif

#if defined(OMNI_OBJECT_NAME)
    #define OMNI_VERSION_NAME_FW name(OMNI_STRW("omni::version")),
    #define OMNI_VERSION_NAMECP_FW name(cp.name),
#else
    #define OMNI_VERSION_NAME_FW 
    #define OMNI_VERSION_NAMECP_FW
#endif
#define OMNI_VERSION_CTOR_FW OMNI_VERSION_DIS_FW OMNI_VERSION_NAME_FW OMNI_SAFE_VER_MTX_FW
#define OMNI_VERSION_CPCTOR_FW OMNI_VERSION_DISCP_FW OMNI_VERSION_NAMECP_FW OMNI_SAFE_VER_MTX_FW

#define OMNI_VMAJ_FW(x) ((0xFFFF000000000000 & (x)) >> 48)
#define OMNI_VMIN_FW(x) ((0x0000FFFF00000000 & (x)) >> 32)
#define OMNI_VBLD_FW(x) ((0x00000000FFFF0000 & (x)) >> 16)
#define OMNI_VREV_FW(x) (0x000000000000FFFF & (x))

#define OMNI_VM_FW(m)                ((static_cast<uint64_t>(m)) << 48)
#define OMNI_VMM_FW(m, i)            (((static_cast<uint64_t>(m)) << 48) | ((static_cast<uint64_t>(i)) << 32))
#define OMNI_VMMB_FW(m, i, b)        (((static_cast<uint64_t>(m)) << 48) | ((static_cast<uint64_t>(i)) << 32) | ((static_cast<uint64_t>(b)) << 16))
#define OMNI_VMMBR_FW(m, i, b, r)    (((static_cast<uint64_t>(m)) << 48) | ((static_cast<uint64_t>(i)) << 32) | ((static_cast<uint64_t>(b)) << 16) | (static_cast<uint64_t>(r)))

#define OMNI_VSMAJ_FW(val) ((val) << 48)
#define OMNI_VSMIN_FW(val) ((val) << 32)
#define OMNI_VSBLD_FW(val) ((val) << 16)
#define OMNI_VSREV_FW(val) ((val))

namespace omni {
    class version
    {
        public:
            version() :
                OMNI_VERSION_CTOR_FW
                m_ver(0)
            {
                OMNI_DV5_FW("created version ", this->to_string_t());
            }

            version(uint16_t mj) :
                OMNI_VERSION_CTOR_FW
                m_ver(OMNI_VM_FW(mj))
            {
                OMNI_DV5_FW("created version ", this->to_string_t());
            }

            version(uint16_t mj, uint16_t mn) :
                OMNI_VERSION_CTOR_FW
                m_ver(OMNI_VMM_FW(mj, mn))
            {
                OMNI_DV5_FW("created version ", this->to_string_t());
            }

            version(uint16_t mj, uint16_t mn, uint16_t bld) :
                OMNI_VERSION_CTOR_FW
                m_ver(OMNI_VMMB_FW(mj,mn,bld))
            {
                OMNI_DV5_FW("created version ", this->to_string_t());
            }

            version(uint16_t mj, uint16_t mn, uint16_t bld, uint16_t rev) :
                OMNI_VERSION_CTOR_FW
                m_ver(OMNI_VMMBR_FW(mj,mn,bld,rev))
            {
                OMNI_DV5_FW("created version ", this->to_string_t());
            }

            OMNI_EXPLICIT version(const std::string& str) :
                OMNI_VERSION_CTOR_FW
                m_ver(0)
            {
                omni::version tmp(omni::version::_parse(str));
                this->m_ver = tmp.m_ver;
                OMNI_DV5_FW("created version ", this->to_string_t());
            }

            OMNI_EXPLICIT version(const std::wstring& str) :
                OMNI_VERSION_CTOR_FW
                m_ver(0)
            {
                omni::version tmp(omni::version::_parse(str));
                this->m_ver = tmp.m_ver;
                OMNI_DV5_FW("created version ", this->to_string_t());
            }

            version(const omni::version& cp) :
                OMNI_VERSION_CPCTOR_FW
                m_ver(0)
            {
                OMNI_VER_OLOCK_FW(cp)
                this->m_ver = cp.m_ver;
                OMNI_DV5_FW("created version ", this->to_string_t());
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
                return ((this->_maj() & 0x0000000F) << 28) |
                       ((this->_min() & 0x000000FF) << 20) |
                       ((this->_bld() & 0x000000FF) << 12) |
                       (this->_rev() & 0x00000FFF);
            }
            
            // maj/major cannot be used as a name (some compilers complain)
            inline uint16_t major_number() const
            {
                OMNI_VER_ALOCK_FW
                return this->_maj();
            }
            
            // min/minor cannot be used as a name (some compilers complain)
            inline uint16_t minor_number() const
            {
                OMNI_VER_ALOCK_FW
                return this->_min();
            }
            
            inline uint16_t build() const
            {
                OMNI_VER_ALOCK_FW
                return this->_bld();
            }
            
            inline uint16_t revision() const
            {
                OMNI_VER_ALOCK_FW
                return this->_rev();
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
            
            omni::version& operator=(const omni::version& o)
            {
                OMNI_VER_ALOCK_FW
                OMNI_VER_OLOCK_FW(o)
                OMNI_ASSIGN_FW(o)
                this->m_ver = o.m_ver;
                return *this;
            }

            omni::version& operator=(const std::string& str)
            {
                OMNI_VER_ALOCK_FW
                omni::version tmp(omni::version::_parse(str));
                this->m_ver = tmp.m_ver;
                return *this;
            }

            omni::version& operator=(const std::wstring& str)
            {
                OMNI_VER_ALOCK_FW
                omni::version tmp(omni::version::_parse(str));
                this->m_ver = tmp.m_ver;
                return *this;
            }

            bool operator==(const std::string& str) const
            {
                OMNI_VER_ALOCK_FW
                omni::version t;
                if (!omni::version::_try_parse(str, t)) { return false; }
                return (*this == t);
            }

            bool operator==(const std::wstring& str) const
            {
                OMNI_VER_ALOCK_FW
                omni::version t;
                if (!omni::version::_try_parse(str, t)) { return false; }
                return (*this == t);
            }

            bool operator==(const omni::version& o) const
            {
                if (this == &o) { return true; }
                OMNI_VER_ALOCK_FW
                OMNI_VER_OLOCK_FW(0)
                return (this->m_ver == o.m_ver)
                        OMNI_EQUAL_FW(o);
            }

            bool operator!=(const omni::version &o) const
            {
                return !(*this == o);
            }
            
            OMNI_MEMBERS_FW(omni::version) // disposing,name,type(),hash()
            
            OMNI_OSTREAM_FW(omni::version)

            static inline omni::version parse(const std::string& str)
            {
                return omni::version::_parse(str);
            }

            static inline omni::version parse(const std::wstring& str)
            {
                return omni::version::_parse(str);
            }
            
            static inline bool try_parse(const std::string& str, omni::version& outval)
            {
                return omni::version::_try_parse(str, outval);
            }
            
            static inline bool try_parse(const std::wstring& str, omni::version& outval)
            {
                return omni::version::_try_parse(str, outval);
            }

        private:
            // FFFF 0000 0000 0000 maj
            // 0000 FFFF 0000 0000 min
            // 0000 0000 FFFF 0000 bld
            // 0000 0000 0000 FFFF rev
            uint64_t m_ver;
            #if defined(OMNI_SAFE_VERSION)
                mutable omni::sync::basic_lock m_mtx;
            #endif

            // maj/major cannot be used as a name (some compilers complain)
            inline uint16_t _maj() const
            {
                return static_cast<uint16_t>(OMNI_VMAJ_FW(this->m_ver));
            }
            
            // min/minor cannot be used as a name (some compilers complain)
            inline uint16_t _min() const
            {
                return static_cast<uint16_t>(OMNI_VMIN_FW(this->m_ver));
            }
            
            inline uint16_t _bld() const
            {
                return static_cast<uint16_t>(OMNI_VBLD_FW(this->m_ver));
            }
            
            inline uint16_t _rev() const
            {
                return static_cast<uint16_t>(OMNI_VREV_FW(this->m_ver));
            }

            template < typename STR, typename SS >
            inline STR _to_string_t() const
            {
                return this->_to_string< STR, SS >(4);
            }

            template < typename STR, typename SS >
            inline STR _to_string(uint8_t field_count) const
            {
                if (field_count == 0) { return STR(); }
                if (field_count > 4) { OMNI_ERR_FW("Invalid range specified", omni::exceptions::invalid_range()) }
                SS o;
                OMNI_VER_ALOCK_FW
                o << this->_maj();
                if (field_count > 1) { o << "." << this->_min(); }
                if (field_count > 2) { o << "." << this->_bld(); }
                if (field_count > 3) { o << "." << this->_rev(); }
                return o.str();
            }

            static omni::version _parse(const std::string& v)
            {
                omni::version ret;
                if (!_try_parse(v, ret)) {
                    OMNI_ERR_FW("Invalid version string specified", omni::exceptions::invalid_version())
                }
                return ret;
            }

            static omni::version _parse(const std::wstring& v)
            {
                omni::version ret;
                if (!_try_parse(v, ret)) {
                    OMNI_ERR_FW("Invalid version string specified", omni::exceptions::invalid_version())
                }
                return ret;
            }

            static bool _try_parse(const std::string& v, omni::version& ret)
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
                OMNI_VER_OLOCK_FW(ret)
                if (it != s.end()) { ret.m_ver |= OMNI_VSMAJ_FW(omni::cstring::type_cast<uint64_t>(*it)); ++it; }
                if (it != s.end()) { ret.m_ver |= OMNI_VSMIN_FW(omni::cstring::type_cast<uint64_t>(*it)); ++it; }
                if (it != s.end()) { ret.m_ver |= OMNI_VSBLD_FW(omni::cstring::type_cast<uint64_t>(*it)); ++it; }
                if (it != s.end()) { ret.m_ver |= OMNI_VSREV_FW(omni::cstring::type_cast<uint64_t>(*it)); ++it; }
                return true;
            }

            static bool _try_parse(const std::wstring& v, omni::version& ret)
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
                OMNI_VER_OLOCK_FW(ret)
                if (it != s.end()) { ret.m_ver |= OMNI_VSMAJ_FW(omni::wstring::type_cast<uint64_t>(*it)); ++it; }
                if (it != s.end()) { ret.m_ver |= OMNI_VSMIN_FW(omni::wstring::type_cast<uint64_t>(*it)); ++it; }
                if (it != s.end()) { ret.m_ver |= OMNI_VSBLD_FW(omni::wstring::type_cast<uint64_t>(*it)); ++it; }
                if (it != s.end()) { ret.m_ver |= OMNI_VSREV_FW(omni::wstring::type_cast<uint64_t>(*it)); ++it; }
                return true;
            }
    };
}

#endif // OMNI_VERSION_HPP
