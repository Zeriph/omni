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
#include <omni/util/version.hpp>
#include <omni/string/cstring.hpp>
#include <omni/string/wstring.hpp>

/* these defines are used (instead of just using the defaults)
to aid in compiler times and memory usage (the compiler doesn't
have to rearrange the variables on construction to match the way
the class is built, as well it doesn't have to do extra padding) */
#if defined(OMNI_DISPOSE_EVENT)
    #define OMNI_VERSION_DIS_FW disposing(),
    #define OMNI_VERSION_DISCP_FW disposing(cp.disposing),
#else
    #define OMNI_VERSION_DIS_FW 
    #define OMNI_VERSION_DISCP_FW
#endif
#if defined(OMNI_OBJECT_NAME)
    #define OMNI_VERSION_NAME_FW name(OMNI_STRW("omni::util::version")),
    #define OMNI_VERSION_NAMECP_FW name(cp.name),
#else
    #define OMNI_VERSION_NAME_FW 
    #define OMNI_VERSION_NAMECP_FW
#endif
#define OMNI_VERSION_CTOR_FW OMNI_VERSION_DIS_FW OMNI_VERSION_NAME_FW
#define OMNI_VERSION_CPCTOR_FW OMNI_VERSION_DISCP_FW OMNI_VERSION_NAMECP_FW

omni::util::version::version() :
    OMNI_VERSION_CTOR_FW
    m_maj(0), m_min(0), m_bld(0), m_rev(0)
{
    OMNI_DV5_FW("created version ", this->to_string_t());
}

omni::util::version::version(unsigned int mj) :
    OMNI_VERSION_CTOR_FW
    m_maj(mj), m_min(0), m_bld(0), m_rev(0)
{
    OMNI_DV5_FW("created version ", this->to_string_t());
}

omni::util::version::version(unsigned int mj, unsigned int mn) :
    OMNI_VERSION_CTOR_FW
    m_maj(mj), m_min(mn), m_bld(0), m_rev(0)
{
    OMNI_DV5_FW("created version ", this->to_string_t());
}

omni::util::version::version(unsigned int mj, unsigned int mn, unsigned int bld) :
    OMNI_VERSION_CTOR_FW
    m_maj(mj), m_min(mn), m_bld(bld), m_rev(0)
{
    OMNI_DV5_FW("created version ", this->to_string_t());
}

omni::util::version::version(unsigned int mj, unsigned int mn, unsigned int bld, unsigned int rev) :
    OMNI_VERSION_CTOR_FW
    m_maj(mj), m_min(mn), m_bld(bld), m_rev(rev)
{
    OMNI_DV5_FW("created version ", this->to_string_t());
}

omni::util::version::version(const std::string& str) :
    OMNI_VERSION_CTOR_FW
    m_maj(0), m_min(0), m_bld(0), m_rev(0)
{
    this->_copy(omni::util::version::_parse(str));
    OMNI_DV5_FW("created version ", this->to_string_t());
}

omni::util::version::version(const std::wstring& str) :
    OMNI_VERSION_CTOR_FW
    m_maj(0), m_min(0), m_bld(0), m_rev(0)
{
    this->_copy(omni::util::version::_parse(str));
    OMNI_DV5_FW("created version ", this->to_string_t());
}

omni::util::version::version(const omni::util::version& cp) :
    OMNI_VERSION_CPCTOR_FW
    m_maj(cp.m_maj), m_min(cp.m_min), m_bld(cp.m_bld), m_rev(cp.m_rev)
{
    OMNI_DV5_FW("created version ", this->to_string_t());
}

omni::util::version omni::util::version::_parse(const std::string& v)
{
    omni::util::version ret;
    if (!omni::util::version::_tryparse(v, ret)) {
        OMNI_ERR_FW("Invalid version string specified", omni::exceptions::invalid_version())
    }
    return ret;
}

omni::util::version omni::util::version::_parse(const std::wstring& v)
{
    omni::util::version ret;
    if (!omni::util::version::_tryparse(v, ret)) {
        OMNI_ERR_FW("Invalid version string specified", omni::exceptions::invalid_version())
    }
    return ret;
}

bool omni::util::version::_tryparse(const std::string& v, omni::util::version& out)
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
    if (it != s.end()) { out.m_maj = omni::cstring::type_cast<unsigned int>(*it); ++it; }
    if (it != s.end()) { out.m_min = omni::cstring::type_cast<unsigned int>(*it); ++it; }
    if (it != s.end()) { out.m_bld = omni::cstring::type_cast<unsigned int>(*it); ++it; }
    if (it != s.end()) { out.m_rev = omni::cstring::type_cast<unsigned int>(*it); ++it; }
    return true;
}

bool omni::util::version::_tryparse(const std::wstring& v, omni::util::version& out)
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
    if (it != s.end()) { out.m_maj = omni::wstring::type_cast<unsigned int>(*it); ++it; }
    if (it != s.end()) { out.m_min = omni::wstring::type_cast<unsigned int>(*it); ++it; }
    if (it != s.end()) { out.m_bld = omni::wstring::type_cast<unsigned int>(*it); ++it; }
    if (it != s.end()) { out.m_rev = omni::wstring::type_cast<unsigned int>(*it); ++it; }
    return true;
}
