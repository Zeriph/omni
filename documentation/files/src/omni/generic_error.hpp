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
#if !defined(OMNI_GENERIC_ERROR_HPP)
#define OMNI_GENERIC_ERROR_HPP 1

#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/strings.hpp>

namespace omni {
    class generic_error
    {
        public:
            typedef enum enum_t {
                SUCCESS,
                NONE,
                UNSPECIFIED,
                INVALID_INPUT,
                INVALID_RANGE,
                INVALID_SIZE,
                INVALID_HANDLE,
                DIVISION_BY_ZERO,
                NULL_POINTER_REFERENCE,
                CLOSED,
                COMPLETE
            } enum_t;
            
            static inline unsigned short COUNT()
            {
                return 11;
            }

            static inline enum_t DEFAULT_VALUE()
            {
                return SUCCESS;
            }

            static std::string to_string(enum_t v)
            {
                return _to_val<std::stringstream>(v);
            }
        
            static std::wstring to_wstring(enum_t v)
            {
                return _to_val<std::wstringstream>(v);
            }

            static enum_t parse(const std::string& val)
            {
                return _parse(val);
            }

            static enum_t parse(const std::wstring& val)
            {
                return _parse(val);
            }

            static bool try_parse(const std::string& val, enum_t& out)
            {
                return _try_parse(val, out);
            }

            static bool try_parse(const std::wstring& val, enum_t& out)
            {
                return _try_parse(val, out);
            }

            static bool try_parse(const std::string& val, generic_error& out)
            {
                return _try_parse(val, out);
            }

            static bool try_parse(const std::wstring& val, generic_error& out)
            {
                return _try_parse(val, out);
            }

            static bool is_valid(int32_t val)
            {
                return _valid(val);
            }

            generic_error() :
                OMNI_CTOR_FW(omni::generic_error)
                m_val(DEFAULT_VALUE())
            { }

            generic_error(const generic_error& cp) :
                OMNI_CPCTOR_FW(cp)
                m_val(cp.m_val)
            { }

            generic_error(enum_t val) : 
                OMNI_CTOR_FW(omni::generic_error)
                m_val(val)
            { }

            ~generic_error()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            unsigned short count() const
            {
                return COUNT();
            }

            enum_t value() const
            {
                return this->m_val;
            }

            std::string to_string() const
            {
                return to_string(this->m_val);
            }

            std::wstring to_wstring() const
            {
                return to_wstring(this->m_val);
            }

            bool operator!=(const generic_error& val) const
            {
                return !(*this == val);
            }
            
            bool operator!=(enum_t val) const
            {
                return (this->m_val != val);
            }
            
            generic_error& operator=(const generic_error& val)
            {
                if (this != &val) {
                    OMNI_ASSIGN_FW(val)
                    this->m_val = val.m_val;
                }
                return *this;
            }

            generic_error& operator=(enum_t val)
            {
                this->m_val = val;
                return *this;
            }

            generic_error& operator=(int32_t val)
            {
                if (!generic_error::is_valid(val)) {
                    OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                } else {
                    this->m_val = static_cast<enum_t>(val);
                }
                return *this;
            }

            generic_error operator|(const generic_error& val)
            {
                return generic_error(static_cast<enum_t>(this->m_val | val.m_val));
            }

            generic_error operator|(enum_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val | val));
            }

            generic_error operator|(int32_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val | val));
            }

            generic_error& operator|=(const generic_error& val)
            {
                this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                return *this;
            }

            generic_error& operator|=(enum_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val | val);
                return *this;
            }

            generic_error& operator|=(int32_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val | val);
                return *this;
            }

            generic_error operator&(const generic_error& val)
            {
                return generic_error(static_cast<enum_t>(this->m_val & val.m_val));
            }

            generic_error operator&(enum_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val & val));
            }

            generic_error operator&(int32_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val & val));
            }

            generic_error& operator&=(const generic_error& val)
            {
                this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                return *this;
            }

            generic_error& operator&=(enum_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val & val);
                return *this;
            }

            generic_error& operator&=(int32_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val & val);
                return *this;
            }
            
            generic_error& operator++()
            {
                this->m_val = static_cast<enum_t>(this->m_val + 1);
                return *this;
            }

            generic_error operator++(int dummy)
            {
                OMNI_UNUSED(dummy);
                generic_error ret(this->m_val);
                this->m_val = static_cast<enum_t>(this->m_val + 1);
                return ret;
            }

            generic_error& operator--()
            {
                this->m_val = static_cast<enum_t>(this->m_val - 1);
                return *this;
            }

            generic_error operator--(int dummy)
            {
                OMNI_UNUSED(dummy);
                generic_error ret(this->m_val);
                this->m_val = static_cast<enum_t>(this->m_val - 1);
                return ret;
            }

            generic_error operator~()
            {
                return generic_error(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
            }

            generic_error operator^(const generic_error& val)
            {
                return generic_error(static_cast<enum_t>(this->m_val ^ val.m_val));
            }

            generic_error operator^(enum_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val ^ val));
            }

            generic_error operator^(int32_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val ^ val));
            }

            generic_error& operator^=(const generic_error& val)
            {
                this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                return *this;
            }

            generic_error& operator^=(enum_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val ^ val);
                return *this;
            }

            generic_error& operator^=(int32_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val ^ val);
                return *this;
            }

            generic_error operator<<(const generic_error& val)
            {
                return generic_error(static_cast<enum_t>(this->m_val << val.m_val));
            }

            generic_error operator<<(enum_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val << val));
            }

            generic_error operator<<(int32_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val << val));
            }

            generic_error& operator<<=(const generic_error& val)
            {
                this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                return *this;
            }

            generic_error& operator<<=(enum_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val << val);
                return *this;
            }

            generic_error& operator<<=(int32_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val << val);
                return *this;
            }

            generic_error operator>>(const generic_error& val)
            {
                return generic_error(static_cast<enum_t>(this->m_val >> val.m_val));
            }

            generic_error operator>>(enum_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val >> val));
            }

            generic_error operator>>(int32_t val)
            {
                return generic_error(static_cast<enum_t>(this->m_val >> val));
            }

            generic_error& operator>>=(const generic_error& val)
            {
                this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                return *this;
            }

            generic_error& operator>>=(enum_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val >> val);
                return *this;
            }

            generic_error& operator>>=(int32_t val)
            {
                this->m_val = static_cast<enum_t>(this->m_val >> val);
                return *this;
            }

            bool operator<(const generic_error& val) const
            {
                return this->m_val < val.m_val;
            }

            bool operator<(enum_t val) const
            {
                return this->m_val < val;
            }

            bool operator<(int32_t val) const
            {
                return this->m_val < static_cast<enum_t>(val);
            }

            bool operator>(const generic_error& val) const
            {
                return this->m_val > val.m_val;
            }

            bool operator>(enum_t val) const
            {
                return this->m_val > val;
            }

            bool operator>(int32_t val) const
            {
                return this->m_val > val;
            }

            bool operator==(const generic_error& val) const
            {
                if (this == &val) { return true; }
                return this->m_val == val.m_val
                        OMNI_EQUAL_FW(val);
            }

            bool operator==(enum_t val) const
            {
                return this->m_val == val;
            }

            bool operator==(int32_t val) const
            {
                return this->m_val == val;
            }

            operator enum_t() const
            {
                return this->m_val;
            }

            operator std::string() const
            {
                return this->to_string();
            }

            operator std::wstring() const
            {
                return this->to_wstring();
            }

            OMNI_MEMBERS_FW(omni::generic_error) // disposing,name,type(),hash()
            
            OMNI_OSTREAM_FW(omni::generic_error)
            OMNI_OSTREAM_FN_FW(enum_t)

        private:
            enum_t m_val;

            template < typename S >
            static enum_t _parse(const S& val)
            {
                enum_t ret;
                if (_try_parse(val, ret)) { return ret; }
                OMNI_ERR_FW("invalid enum parse", omni::exceptions::invalid_enum())
                return DEFAULT_VALUE();
            }

            template < typename S >
            static bool _try_parse(const S& str, enum_t& out)
            {
                return _try_parse(omni::string::util::to_upper(str), out);
            }

            template < typename S >
            static bool _try_parse(const S& val, generic_error& out)
            {
                enum_t tmp;
                if (_try_parse(val, tmp)) {
                    out.m_val = tmp;
                    return true;
                }
                return false;
            }

            static bool _try_parse(const std::wstring& val, enum_t& out)
            {
                return _try_parse(omni::string::util::to_string(val), out);
            }

            static bool _try_parse(const std::string& val, enum_t& out)
            {
                if (!val.empty()) {
                    OMNI_S2E_FW(SUCCESS)
                    OMNI_S2E_FW(NONE)
                    OMNI_S2E_FW(UNSPECIFIED)
                    OMNI_S2E_FW(INVALID_INPUT)
                    OMNI_S2E_FW(INVALID_RANGE)
                    OMNI_S2E_FW(INVALID_SIZE)
                    OMNI_S2E_FW(INVALID_HANDLE)
                    OMNI_S2E_FW(DIVISION_BY_ZERO)
                    OMNI_S2E_FW(NULL_POINTER_REFERENCE)
                    OMNI_S2E_FW(CLOSED)
                    OMNI_S2E_FW(COMPLETE)
                }
                return false;
            }

            template < typename S >
            static std::basic_string< typename S::char_type > _to_val(enum_t v)
            {
                S ss;
                switch (v) {
                    OMNI_E2SS_FW(SUCCESS);
                    OMNI_E2SS_FW(NONE);
                    OMNI_E2SS_FW(UNSPECIFIED);
                    OMNI_E2SS_FW(INVALID_INPUT);
                    OMNI_E2SS_FW(INVALID_RANGE);
                    OMNI_E2SS_FW(INVALID_SIZE);
                    OMNI_E2SS_FW(INVALID_HANDLE);
                    OMNI_E2SS_FW(DIVISION_BY_ZERO);
                    OMNI_E2SS_FW(NULL_POINTER_REFERENCE);
                    OMNI_E2SS_FW(CLOSED);
                    OMNI_E2SS_FW(COMPLETE);
                    default:
                        ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                        break;
                }
                return ss.str();
            }

            static bool _valid(int32_t val)
            {
                return (
                    OMNI_I2EV_FW(SUCCESS) ||
                    OMNI_I2EV_FW(NONE) ||
                    OMNI_I2EV_FW(UNSPECIFIED) ||
                    OMNI_I2EV_FW(INVALID_INPUT) ||
                    OMNI_I2EV_FW(INVALID_RANGE) ||
                    OMNI_I2EV_FW(INVALID_SIZE) ||
                    OMNI_I2EV_FW(INVALID_HANDLE) ||
                    OMNI_I2EV_FW(DIVISION_BY_ZERO) ||
                    OMNI_I2EV_FW(NULL_POINTER_REFERENCE) ||
                    OMNI_I2EV_FW(CLOSED) ||
                    OMNI_I2EV_FW(COMPLETE)
                );
            }
    };
}

#endif // OMNI_GENERIC_ERROR_HPP
