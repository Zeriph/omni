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
#if !defined(OMNI_MUTEX_HPP)
#define OMNI_MUTEX_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/sync/lock.hpp>
#include <omni/sync/basic_lock.hpp> // included for convenience
#if defined(OMNI_MUTEX_OWNER)
    #include <omni/types/thread_t.hpp>
#endif

#if defined(OMNI_32BIT_MUTEX)
    #define OMNI_MTX_INT_FW uint32_t
#else
    #define OMNI_MTX_INT_FW uint64_t
#endif

namespace omni {
    namespace sync {
        class mutex
        {
            public:
                mutex();
                OMNI_EXPLICIT mutex(bool initially_owned);
                ~mutex(); // should not inherit
                const omni::sync::mutex_t handle() const;
                bool locked() const;
                void lock();
                bool lock(uint32_t timeout_ms);
                void unlock();
                bool trylock();
                bool operator==(const omni::sync::mutex& o) const;
                bool operator!=(const omni::sync::mutex& o) const;
                
                OMNI_MEMBERS_FW(omni::sync::mutex) // disposing,name,type(),hash()
                
            private:
                // defined but not implemented, should not be copied
                mutex(const omni::sync::mutex &cp);
                omni::sync::mutex& operator=(const omni::sync::mutex& other);
                
                volatile OMNI_MTX_INT_FW m_lokd;
                omni::sync::mutex_t m_mtx;
                #if defined(OMNI_SAFE_MUTEX)
                    mutable omni::sync::mutex_t m_imtx; // internal mutex
                #endif
                #if defined(OMNI_MUTEX_OWNER)
                    omni::sync::thread_t m_owner;
                #endif
        };
        
        typedef omni::sync::auto_lock<omni::sync::mutex> auto_mutex;
        typedef omni::sync::scoped_lock<omni::sync::mutex> scoped_mutex;
    }
}

#endif // OMNI_MUTEX_HPP
