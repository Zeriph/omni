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
#if !defined(OMNI_HOST_HELPER_HPP)
#define OMNI_HOST_HELPER_HPP 1
#include <omni/types/net_t.hpp>
#include <omni/net/util.hpp>
#include <omni/defs/debug.hpp>

#if defined(OMNI_SAFE_HOST_HELPER)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_HSTHLPMTX_FW  ,m_mtx()
    #define OMNI_SAFE_HSTHLPLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_HSTHLPUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_HSTHLPALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_HSTHLPOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_HSTHLPMTX_FW
    #define OMNI_SAFE_HSTHLPLOCK_FW
    #define OMNI_SAFE_HSTHLPUNLOCK_FW
    #define OMNI_SAFE_HSTHLPALOCK_FW
    #define OMNI_SAFE_HSTHLPOALOCK_FW(o) 
#endif

// TODO: this might make more sense to be an 'endpoint' class

namespace omni {
    namespace net {
        /** The socket class is used to facilitate network communications */
        class host_helper {
            public:
                host_helper(const std::string& host) : m_host(host) { }

                std::string host() const
                {
                    OMNI_SAFE_HSTHLPALOCK_FW
                    return this->m_host;
                }

                uint32_t ipv4() const
                {
                    OMNI_SAFE_HSTHLPALOCK_FW
                    return 0;
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_HSTHLPLOCK_FW
                    s << omni::string::util::to_string_t(this->m_host);
                    OMNI_SAFE_HSTHLPUNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_HSTHLPLOCK_FW
                    s << this->m_host;
                    OMNI_SAFE_HSTHLPUNLOCK_FW
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_HSTHLPLOCK_FW
                    s << omni::string::util::to_wstring(this->m_host);
                    OMNI_SAFE_HSTHLPUNLOCK_FW
                    return s.str();
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::net::host_helper) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::host_helper)

            private:
                std::string m_host;
        };
    }
}

#endif // OMNI_HOST_HELPER_HPP
