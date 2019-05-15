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
#include <omni/argparser.hpp>
#include <omni/exception.hpp>
#include <omni/strings.hpp>

omni::application::argparser::argparser() :
    OMNI_CTOR_FW(omni::application::argparser)
    m_args(),
    m_argc(0)
{
    OMNI_D5_FW("created");
}

omni::application::argparser::argparser(const omni::application::argparser &cp) :
    OMNI_CPCTOR_FW(cp)
    m_args(cp.m_args),
    m_argc(cp.m_argc)
{
    OMNI_D5_FW("copied");
}

omni::application::argparser::argparser(uint32_t ac, const char** av) :
    OMNI_CTOR_FW(omni::application::argparser)
    m_args(),
    m_argc(0)
{
    this->set(ac, av);
}

omni::application::argparser::argparser(uint32_t ac, const wchar_t** av) :
    OMNI_CTOR_FW(omni::application::argparser)
    m_args(),
    m_argc(0)
{
    this->set(ac, av);
}

omni::application::argparser::argparser(const omni::seq::std_string_t& av) :
    OMNI_CTOR_FW(omni::application::argparser)
    m_args(),
    m_argc(0)
{
    this->m_argc = static_cast<uint32_t>(av.size());
    omni::seq::std_string_t::const_iterator it = av.begin();
    while (it != av.end()) {
        omni::string_t tmp = omni::string::to_string_t(*it);
        this->m_args.push_back(tmp);
        ++it;
    }
    OMNI_D5_FW("created");
}

omni::application::argparser::argparser(const omni::seq::std_wstring_t& av) :
    OMNI_CTOR_FW(omni::application::argparser)
    m_args(),
    m_argc(0)
{
    this->m_argc = static_cast<uint32_t>(av.size());
    omni::seq::std_wstring_t::const_iterator it = av.begin();
    while (it != av.end()) {
        omni::string_t tmp = omni::string::to_string_t(*it);
        this->m_args.push_back(tmp);
        ++it;
    }
    OMNI_D5_FW("created");
}

omni::application::argparser::~argparser()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    this->m_args.clear();
    OMNI_CATCH_FW
}

omni::seq::string_t omni::application::argparser::argv() const
{
    omni::seq::string_t ret;
    std::copy(this->m_args.begin(), this->m_args.end(), std::back_inserter(ret));
    return ret;
}

omni::string_t omni::application::argparser::at(uint32_t index) const
{
    if (index > this->m_args.size() || this->m_args.empty()) {
        OMNI_ERR_RETV_FW("Invalid index specified: index out of range", omni::exceptions::index_out_of_range(), omni::string_t())
    }
    return this->m_args[index];
}

bool omni::application::argparser::contains(const std::string& sw) const
{
    if (sw.empty()) { return false; }
    omni::string_t tmp = omni::string::to_string_t(sw);
    return (this->_find(this->m_args.begin(), tmp) != this->m_args.end());
}

bool omni::application::argparser::contains(const std::wstring& sw) const
{
    if (sw.empty()) { return false; }
    omni::string_t tmp = omni::string::to_string_t(sw);
    return (this->_find(this->m_args.begin(), tmp) != this->m_args.end());
}

omni::string_t omni::application::argparser::get_arg(uint32_t index) const
{
    if (index > this->m_args.size() || this->m_args.empty()) {
        OMNI_ERR_RETV_FW("Invalid index specified: index out of range", omni::exceptions::index_out_of_range(), omni::string_t())
    }
    return this->m_args[index];
}

omni::string_t omni::application::argparser::get_switch(const std::string& sw) const
{
    if (sw.empty()) {
        OMNI_D1_FW("invalid switch specified");
        return omni::string_t();
    }
    omni::string_t tmp = omni::string::to_string_t(sw);
    omni::seq::string_t::const_iterator it = this->_find(this->m_args.begin(), tmp);
    if (it != this->m_args.end()) {
        if ((++it) != this->m_args.end()) {
            return omni::string_t(*it);
        }
    }
    return omni::string_t();
}

omni::string_t omni::application::argparser::get_switch(const std::wstring& sw) const
{
    if (sw.empty()) {
        OMNI_D1_FW("invalid switch specified");
        return omni::string_t();
    }
    omni::string_t tmp = omni::string::to_string_t(sw);
    omni::seq::string_t::const_iterator it = this->_find(this->m_args.begin(), tmp);
    if (it != this->m_args.end()) {
        if ((++it) != this->m_args.end()) {
            return omni::string_t(*it);
        }
    }
    return omni::string_t();
}

omni::seq::string_t omni::application::argparser::get_switches(const omni::string_t& sw) const
{
    if (sw.empty()) {
        OMNI_D1_FW("invalid switch specified");
        return omni::seq::string_t();
    }
    omni::seq::string_t ret;
    omni::seq::string_t::const_iterator f = this->_find(this->m_args.begin(), sw);
    while (f != this->m_args.end()) {
        if ((++f) != this->m_args.end()) {
            ret.push_back(*f);
            f = this->_find(f, sw);
        }
    }
    return ret;
}

omni::seq::string_t omni::application::argparser::get_range(std::size_t start, std::size_t end) const
{
    if (start > this->m_argc) {
        OMNI_ERR_RETV_FW("index out of range: start > argc", omni::exceptions::index_out_of_range(), omni::seq::string_t())
    }
    if (end > this->m_argc) {
        OMNI_ERR_RETV_FW("index out of range: end > argc", omni::exceptions::index_out_of_range(), omni::seq::string_t())
    }
    if (start > end) {
        OMNI_ERR_RETV_FW("start > end", omni::exceptions::index_out_of_range(), omni::seq::string_t())
    };
    omni::seq::string_t rng;
    omni::seq::string_t::const_iterator it = this->m_args.begin();
    for (std::size_t t = start; t > 0; --t) { ++it; }
    while (it != this->m_args.end() && start<=end) {
        rng.push_back(*it);
        ++it;
        ++start;
    }
    return rng;
}

void omni::application::argparser::set(uint32_t ac, const char** av)
{
    this->m_argc = ac;
    this->m_args.clear();
    for (ac = 0; ac < this->m_argc; ++ac) {
        this->m_args.push_back(omni::string::to_string_t(av[ac]));
    }
}

void omni::application::argparser::set(uint32_t ac, const wchar_t** av)
{
    this->m_argc = ac;
    this->m_args.clear();
    for (ac = 0; ac < this->m_argc; ++ac) {
        this->m_args.push_back(omni::string::to_string_t(av[ac]));
    }
}

void omni::application::argparser::set(const omni::seq::string_t& av)
{
    this->m_argc = static_cast<uint32_t>(av.size());
    this->m_args.clear();
    for (omni::seq::string_t::const_iterator it = av.begin(); it != av.end(); ++it) {
        this->m_args.push_back(*it);
    }
}

const omni::string_t omni::application::argparser::to_string_t() const
{
    return this->to_string_t(false);
}

const omni::string_t omni::application::argparser::to_string_t(bool includeArg1) const
{
    #if defined(OMNI_UNICODE)
        return this->to_wstring(includeArg1);
    #else
        return this->to_string(includeArg1);
    #endif
}

const std::string omni::application::argparser::to_string() const
{
    return this->to_string(false);
}

const std::string omni::application::argparser::to_string(bool includeArg1) const
{
    std::string ret, tmp;
    std::string q("\"");
    omni::seq::string_t::const_iterator it = this->m_args.begin();
    if (!includeArg1) { ++it; }
    while (it != this->m_args.end()) {
        tmp = omni::string::to_string(*it);
        if (omni::cstring::contains(tmp, " ")) {
            ret.append(q).append(tmp).append(q);
        } else {
            ret.append(tmp);
        }
        if (++it != this->m_args.end()) { ret.append(" "); }
    }
    return ret;
}

const std::wstring omni::application::argparser::to_wstring() const
{
    return this->to_wstring(false);
}

const std::wstring omni::application::argparser::to_wstring(bool includeArg1) const
{
    std::wstring ret, tmp;
    std::wstring q(L"\"");
    omni::seq::string_t::const_iterator it = this->m_args.begin();
    if (!includeArg1) { ++it; }
    while (it != this->m_args.end()) {
        tmp = omni::string::to_wstring(*it);
        if (omni::wstring::contains(tmp, L" ")) {
            ret.append(q).append(tmp).append(q);
        } else {
            ret.append(tmp);
        }
        if (++it != this->m_args.end()) { ret.append(std::wstring(L" ")); }
    }
    return ret;
}

omni::string_t omni::application::argparser::operator[](const std::string &sw) const
{
    return this->get_switch(omni::string::to_string_t(sw));
}

omni::string_t omni::application::argparser::operator[](const std::wstring &sw) const
{
    return this->get_switch(omni::string::to_string_t(sw));
}

omni::string_t omni::application::argparser::operator[](uint32_t index) const
{
    if (index > this->m_args.size() || this->m_args.empty()) {
        OMNI_ERR_RETV_FW("Invalid index specified: index out of range", omni::exceptions::index_out_of_range(), omni::string_t())
    }
    return this->m_args[index];
}

omni::application::argparser& omni::application::argparser::operator=(const omni::application::argparser &ap)
{
    if (this != &ap) {
        OMNI_ASSIGN_FW(ap);
        this->m_args.clear();
        this->m_args = ap.m_args;
        this->m_argc = static_cast<uint32_t>(this->m_args.size());
    }
    return *this;
}

bool omni::application::argparser::operator==(const omni::application::argparser &o) const
{
    if (this == &o) { return true; }
    return (this->m_argc == o.m_argc && this->m_args == o.m_args)
    OMNI_EQUAL_FW(o);
}

bool omni::application::argparser::operator!=(const omni::application::argparser &o) const
{
    return !(*this == o);
}

///////// start private methods /////////

omni::seq::string_t::const_iterator omni::application::argparser::_find(omni::seq::string_t::const_iterator it, const omni::string_t& f) const
{
    if (this->m_args.empty()) { return this->m_args.end(); }
    for (; it != this->m_args.end(); ++it) { if (f == (*it)) { break; } }
    return it;
}
