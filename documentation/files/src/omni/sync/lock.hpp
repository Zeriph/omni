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
#if !defined(OMNI_SYNC_LOCK_HPP)
#define OMNI_SYNC_LOCK_HPP 1
#include <omni/types/lock_t.hpp>
#include <omni/chrono/tick.hpp>

namespace omni {
    namespace sync {
        inline void mutex_init(omni::sync::mutex_t& mtx)
        {
            #if defined(OMNI_OS_WIN)
                ::InitializeCriticalSection(&mtx);
            #else
                int lerr = 0;
                pthread_mutexattr_t mtxatr;
                if ((lerr = ::pthread_mutexattr_init(&mtxatr)) == 0)  {
                    if ((lerr = ::pthread_mutexattr_settype(&mtxatr,
                        #if defined(__linux__) && !defined(PTHREAD_MUTEX_RECURSIVE)
                            PTHREAD_MUTEX_RECURSIVE_NP
                        #else
                            PTHREAD_MUTEX_RECURSIVE
                        #endif
                    )) == 0)
                    {
                        if ((lerr = ::pthread_mutex_init(&mtx, &mtxatr)) == 0) {
                            lerr = ::pthread_mutexattr_destroy(&mtxatr);
                        }
                    }
                }
                if (lerr != 0) {
                    OMNI_ERRV_FW("system create mutex failed", lerr, omni::exceptions::mutex_system_exception("system create mutex failed", lerr))
                }
            #endif
        }
        
        inline void mutex_destroy(omni::sync::mutex_t& mtx)
        {
            #if defined(OMNI_OS_WIN)
                ::DeleteCriticalSection(&mtx);
            #else
                int lerr = ::pthread_mutex_destroy(&mtx);
                if (lerr != 0) {
                    OMNI_ERRV_FW("mutex destroy failed", lerr, omni::exceptions::mutex_system_exception("mutex destroy failed", lerr))
                }
            #endif
        }
        
        inline bool mutex_trylock(omni::sync::mutex_t& mtx)
        {
            #if defined(OMNI_OS_WIN)
                return (::TryEnterCriticalSection(&mtx) == TRUE);
            #else
                return (::pthread_mutex_trylock(&mtx) == 0);
            #endif
        }
        
        inline void mutex_lock(omni::sync::mutex_t& mtx)
        {
            #if defined(OMNI_OS_WIN)
                ::EnterCriticalSection(&mtx);
            #else
                int lerr = ::pthread_mutex_lock(&mtx);
                if (lerr != 0) {
                    OMNI_ERRV_FW("mutex lock failed", lerr, omni::exceptions::mutex_system_exception("mutex lock failed", lerr))
                }
            #endif
        }
        
        inline bool mutex_lock(omni::sync::mutex_t& mtx, uint32_t timeout_ms)
        {
            if (timeout_ms == 0) { return omni::sync::mutex_trylock(mtx); }
            #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
                omni::chrono::monotonic::initialize();
            #endif
            omni::chrono::tick_t start = omni::chrono::monotonic_tick();
            while (omni::chrono::elapsed_ms(start) <= timeout_ms) {
                if (omni::sync::mutex_trylock(mtx)) { return true; }
            }
            return false;
        }
        
        inline void mutex_unlock(omni::sync::mutex_t& mtx)
        {
            #if defined(OMNI_OS_WIN)
                ::LeaveCriticalSection(&mtx);
            #else
                int lerr = ::pthread_mutex_unlock(&mtx);
                if (lerr != 0) {
                    OMNI_ERRV_FW("mutex unlock failed", lerr, omni::exceptions::mutex_system_exception("mutex unlock failed", lerr))
                }
            #endif
        }
    }
}

#endif // OMNI_SYNC_LOCK_HPP
