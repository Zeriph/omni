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
#if !defined(OMNI_TIMER_T_HPP)
#define OMNI_TIMER_T_HPP 1
#include <omni/defs/global.hpp>
#include <omni/generic_ptr.hpp>
#include <omni/sync/basic_thread.hpp>
#include <omni/delegate/2.hpp>
#include <omni/sequence.hpp>

#define OMNI_TIMER_AUTO_FLAG_FW 1
#define OMNI_TIMER_RUN_FLAG_FW 2
#define OMNI_TIMER_STOP_FLAG_FW 4

namespace omni {
    namespace chrono {
        class timer_sync_type
        {
            public:
                typedef enum enum_t {
                    ASYNCHRONOUS,
                    SYNCHRONOUS,
                    DROP,
                    QUEUED
                } enum_t;
                
                static inline unsigned short COUNT()
                {
                    return 4;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return ASYNCHRONOUS;
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

                static bool try_parse(const std::string& val, timer_sync_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, timer_sync_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                timer_sync_type() :
                    OMNI_CTOR_FW(omni::chrono::timer_sync_type)
                    m_val(DEFAULT_VALUE())
                { }

                timer_sync_type(const timer_sync_type& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                timer_sync_type(enum_t val) : 
                    OMNI_CTOR_FW(omni::chrono::timer_sync_type)
                    m_val(val)
                { }

                ~timer_sync_type()
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

                bool operator!=(const timer_sync_type& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                timer_sync_type& operator=(const timer_sync_type& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                timer_sync_type& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                timer_sync_type& operator=(int32_t val)
                {
                    if (!timer_sync_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const timer_sync_type& val) const
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

                bool operator>(const timer_sync_type& val) const
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

                bool operator==(const timer_sync_type& val) const
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

                OMNI_MEMBERS_FW(omni::chrono::timer_sync_type) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::chrono::timer_sync_type)
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
                static bool _try_parse(const S& val, timer_sync_type& out)
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
                        OMNI_S2E_FW(ASYNCHRONOUS)
                        OMNI_S2E_FW(SYNCHRONOUS)
                        OMNI_S2E_FW(DROP)
                        OMNI_S2E_FW(QUEUED)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(ASYNCHRONOUS);
                        OMNI_E2SS_FW(SYNCHRONOUS);
                        OMNI_E2SS_FW(DROP);
                        OMNI_E2SS_FW(QUEUED);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        ASYNCHRONOUS ||
                        SYNCHRONOUS || 
                        DROP || 
                        QUEUED
                    );
                }
        };
        
        typedef struct timer_args {
            timer_args() :
                signal_time(),
                state_object()
                { }
            
            timer_args(const timer_args& cp) :
                signal_time(cp.signal_time),
                state_object(cp.state_object)
                { }
            
            timer_args(omni::chrono::tick_t st, const omni::generic_ptr& sobj) :
                signal_time(st),
                state_object(sobj)
                { }
                
            omni::chrono::timer_args& operator=(const omni::chrono::timer_args& o)
            {
                this->signal_time = o.signal_time;
                this->state_object = o.state_object;
                return *this;
            }
            
            bool operator==(const omni::chrono::timer_args& o) const
            {
                if (this == &o) { return true; }
                return (omni::chrono::equal(this->signal_time, o.signal_time) &&
                        this->state_object == o.state_object);
            }
            
            bool operator!=(const omni::chrono::timer_args& o) const
            {
                return !(*this == o);
            }
        
            omni::chrono::tick_t signal_time;
            omni::generic_ptr state_object;
        } timer_args;
        
        typedef omni::event2<void, omni::chrono::tick_t, const omni::generic_ptr&> timer_event;
        typedef omni::chrono::timer_event::delegate_t timer_delegate;
    }
}

#endif // OMNI_TIMER_T_HPP
