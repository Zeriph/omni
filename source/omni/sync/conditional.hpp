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
#if !defined(OMNI_CONDITIONAL_HPP)
#define OMNI_CONDITIONAL_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/tick_t.hpp>
#include <omni/types/thread_t.hpp>
#include <omni/sync/lock.hpp>
#include <omni/sync/scoped_lock.hpp>
#include <omni/chrono/tick.hpp>

#if !defined(OMNI_OS_WIN)
    #include <errno.h> // errno
#endif

#if defined(OMNI_32BIT_CONDITIONAL)
    #define OMNI_COND_INT_FW uint32_t
#else
    #define OMNI_COND_INT_FW uint64_t
#endif

namespace omni {
    namespace sync {
        class conditional
        {
            public:
                conditional();
                OMNI_EXPLICIT conditional(bool initially_signaled);
                ~conditional() OMNI_DTOR_THROWS;
                void broadcast();
                void reset();
                
                inline bool signaled() const
                {
                    omni::sync::scoped_lock<omni::sync::mutex_t> slock(&this->m_wait);
                    return (this->m_signaled == 1);
                }
                
                void signal();
                bool wait();
                bool wait(uint32_t timeout_ms);
                bool operator==(const omni::sync::conditional& o);            
                bool operator!=(const omni::sync::conditional& o);
                
                OMNI_MEMBERS_FW(omni::sync::conditional) // disposing,name,type(),hash()
                
            private:
                // defined but not implemented, does not make sense to copy
                conditional(const omni::sync::conditional &cp);
                omni::sync::conditional& operator=(const omni::sync::conditional& other);
                
                void _init();
                
                omni::sync::cond_t m_signal;
                mutable omni::sync::mutex_t m_wait;
                OMNI_COND_INT_FW m_waitreq;
                volatile mutable OMNI_COND_INT_FW m_signaled;
        };
    }
}

#endif // OMNI_CONDITIONAL_HPP
