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
#if !defined(OMNI_SPIN_HPP)
#define OMNI_SPIN_HPP 1
#include <omni/defs/global.hpp>
// DEV_NOTE: no asm in spin_lock, while fast, it introduces other issues on non x86 platforms, asm spin will be in another rev
#include <omni/sync/auto_lock.hpp>
#include <omni/sync/scoped_lock.hpp>
#include <omni/sync/this_thread.hpp>

/* DEV_NOTE: pthread_spin_lock, pthread_spin_unlock, pthread_spin_trylock on some platforms
are not within a global namespace i.e. ::pthread_spin_lock(&lock) will give the error:
expected id-expression before (, while pthread_spin_lock(&lock) resolves and works */

#if defined(OMNI_32BIT_SPIN)
    #define OMNI_SPIN_INT_FW uint32_t
#else
    #define OMNI_SPIN_INT_FW uint64_t
#endif

namespace omni {
    namespace sync {
        class spin_lock
        {
            public:
                spin_lock() :
                    OMNI_CTOR_FW(omni::sync::spin_lock)
                    m_lock(), m_lokd(0)
                {
                    this->_init();
                }
                
                OMNI_EXPLICIT spin_lock(bool initialy_owned) :
                    OMNI_CTOR_FW(omni::sync::spin_lock)
                    m_lock(), m_lokd(0)
                {
                    this->_init();
                    if (initialy_owned) { this->lock(); }
                }
                
                ~spin_lock() OMNI_DTOR_THROWS
                {
                    OMNI_DTOR_FW
                    if (this->m_lokd == 1) { this->unlock(); }
                    #if defined(OMNI_OS_WIN) || defined(OMNI_OS_APPLE)
                        this->m_lock = 0;
                    #else
                        int serr = ::pthread_spin_destroy(&this->m_lock);
                        if (serr != 0) {
                            OMNI_ERRV_FW("An error occurred destroying the spin lock: ", serr, omni::exceptions::spin_lock_exception(serr))
                        }
                    #endif
                }

                inline bool locked() const
                {
                    return this->m_lokd == 1;
                }
                
                void lock()
                {
                    #if defined(OMNI_OS_WIN)
                        // do not call omni::yield directly, just use the WinAPI
                        while (::InterlockedExchange(&this->m_lock, 1 ) == 1) { OMNI_THREAD_YIELD(); }
                    #elif defined(OMNI_OS_APPLE)
                        #if defined(OMNI_OS_MACOS)
                            ::os_unfair_lock_lock(this->m_lock);
                        #else
                            ::OSSpinLockLock(&this->m_lock);
                        #endif
                    #else
                        int serr = pthread_spin_lock(&this->m_lock);
                        if (serr != 0) {
                            OMNI_ERRV_FW("An error occurred on the spin lock: ", serr, omni::exceptions::spin_lock_exception(serr))
                        }
                    #endif
                    this->m_lokd = 1;
                }
                
                void unlock()
                {
                    #if defined(OMNI_OS_WIN)
                        ::InterlockedExchange(&this->m_lock, 0);
                    #elif defined(OMNI_OS_APPLE)
                        #if defined(OMNI_OS_MACOS)
                            ::os_unfair_lock_unlock(this->m_lock);
                        #else
                            ::OSSpinLockUnlock(&this->m_lock);
                        #endif
                    #else
                        pthread_spin_unlock(&this->m_lock);
                    #endif
                    this->m_lokd = 0;
                }
                
                bool trylock()
                {
                    #if defined(OMNI_OS_WIN)
                        this->m_lokd = ((::InterlockedExchange(&this->m_lock, 1) == 0) ? 1 : 0);
                    #elif defined(OMNI_OS_APPLE)
                        #if defined(OMNI_OS_MACOS)
                            this->m_lokd = (::os_unfair_lock_trylock(this->m_lock) ? 1 : 0);
                        #else
                            this->m_lokd = (::OSSpinLockTry(&this->m_lock) ? 1 : 0);
                        #endif
                    #else
                        this->m_lokd = ((pthread_spin_trylock(&this->m_lock) == 0) ? 1 : 0);
                    #endif
                    return this->m_lokd == 1;
                }
                
                bool operator==(const omni::sync::spin_lock& o)
                {
                    if (this == &o) { return true; }
                    return (this->m_lokd == o.m_lokd &&
                            &this->m_lock == &o.m_lock)
                    OMNI_EQUAL_FW(o);
                }
                
                bool operator!=(const omni::sync::spin_lock& o)
                {
                    return !(*this == o);
                }
                
                OMNI_MEMBERS_FW(omni::sync::spin_lock) // disposing,name,type(),hash()
                
            private:
                omni::sync::spin_lock_t m_lock;
                volatile mutable OMNI_SPIN_INT_FW m_lokd;

                // defined but not implemented, does not make sense to copy
                spin_lock(const omni::sync::spin_lock& cp);
                omni::sync::spin_lock& operator=(const omni::sync::spin_lock& other);
                
                inline void _init()
                {
                    #if defined(OMNI_OS_WIN) || defined(OMNI_OS_APPLE)
                        this->m_lock = 0;
                    #else
                        int serr = ::pthread_spin_init(&this->m_lock, PTHREAD_PROCESS_PRIVATE);
                        if (serr != 0) {
                            OMNI_ERRV_FW("An error occurred initializing the spin lock: ", serr, omni::exceptions::spin_lock_exception(serr))
                        }
                    #endif
                }
        };
        
        class spin_wait
        {
            public:
                spin_wait() :
                    OMNI_CTOR_FW(omni::sync::spin_wait)
                    m_sig(0) { }
                    
                OMNI_EXPLICIT spin_wait(bool initsig) :
                    OMNI_CTOR_FW(omni::sync::spin_wait)
                    m_sig(initsig ? 1 : 0) { }
                
                ~spin_wait()
                {
                    OMNI_DTOR_FW
                    this->signal();
                }

                inline void reset()
                {
                    this->m_sig = 0;
                }
                
                void reset(uint32_t sleep_ms)
                {
                    OMNI_SLEEP_INIT();
                    this->m_sig = 1;
                    OMNI_SLEEP(sleep_ms);
                    this->m_sig = 0;
                }
                
                inline bool signaled() const
                {
                    return this->m_sig == 1;
                }
                
                inline void signal()
                {
                    this->m_sig = 1;
                }

                inline void busy_wait() const
                {
                    while (this->m_sig == 0) {
                        OMNI_THREAD_YIELD();
                    }
                }

                bool busy_wait(uint32_t timeout_ms) const
                {
                    omni::chrono::monotonic::initialize();
                    omni::chrono::tick_t start = omni::chrono::monotonic_tick();
                    while ((this->m_sig == 0) && (omni::chrono::elapsed_ms(start) <= timeout_ms)) {
                        OMNI_THREAD_YIELD();
                    }
                    // if !this->m_sig, then the timeout failed
                    return (this->m_sig == 1);
                }
                
                inline void sleep_wait() const
                {
                    OMNI_SLEEP_INIT();
                    while (this->m_sig == 0) {
                        OMNI_SLEEP1();
                    }
                }

                bool sleep_wait(uint32_t timeout_ms) const
                {
                    OMNI_SLEEP_INIT();
                    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
                        omni::chrono::monotonic::initialize();
                    #endif
                    omni::chrono::tick_t start = omni::chrono::monotonic_tick();
                    while ((this->m_sig == 0) && (omni::chrono::elapsed_ms(start) <= timeout_ms)) {
                        OMNI_SLEEP1();
                    }
                    // if !this->m_sig, then the timeout failed
                    return (this->m_sig == 1);
                }
                
                bool operator==(const omni::sync::spin_wait& o) const
                {
                    if (this == &o) { return true; }
                    return (this->m_sig == o.m_sig)
                    OMNI_EQUAL_FW(o);
                }

                bool operator!=(const omni::sync::spin_wait& o) const
                {
                    return !(*this == o);
                }
                
                OMNI_MEMBERS_FW(omni::sync::spin_wait) // disposing,name,type(),hash()
                
            private:
                volatile mutable OMNI_SPIN_INT_FW m_sig;

                // defined but not implemented. should not be copied
                spin_wait(const omni::sync::spin_wait& cp); // C++1X delete 
                omni::sync::spin_wait& operator=(const omni::sync::spin_wait& other); // C++1X delete
        };
        
        class safe_spin_wait
        {
            public:
                safe_spin_wait() :
                    OMNI_CTOR_FW(omni::sync::safe_spin_wait)
                    m_mtx(), m_sig(0)
                {
                    omni::sync::mutex_init(this->m_mtx);
                }
                    
                OMNI_EXPLICIT safe_spin_wait(bool initsig) :
                    OMNI_CTOR_FW(omni::sync::safe_spin_wait)
                    m_mtx(), m_sig(initsig ? 1 : 0)
                {
                    omni::sync::mutex_init(this->m_mtx);
                }
                
                ~safe_spin_wait()
                {
                    OMNI_DTOR_FW
                    this->signal();
                    omni::sync::mutex_destroy(this->m_mtx);
                }

                void reset()
                {
                    omni::sync::mutex_lock(this->m_mtx);
                    this->m_sig = 0;
                    omni::sync::mutex_unlock(this->m_mtx);
                }
                
                void reset(uint32_t sleep_ms)
                {
                    OMNI_SLEEP_INIT();
                    omni::sync::mutex_lock(this->m_mtx);
                    this->m_sig = 1;
                    omni::sync::mutex_unlock(this->m_mtx);
                    OMNI_SLEEP(sleep_ms);
                    omni::sync::mutex_lock(this->m_mtx);
                    this->m_sig = 0;
                    omni::sync::mutex_unlock(this->m_mtx);
                }
                
                bool signaled() const
                {
                    omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                    return (this->m_sig == 1);
                }
                
                void signal()
                {
                    omni::sync::mutex_lock(this->m_mtx);
                    this->m_sig = 1;
                    omni::sync::mutex_unlock(this->m_mtx);
                }

                void busy_wait() const
                {
                    for(;;) {
                        omni::sync::mutex_lock(this->m_mtx);
                        if (this->m_sig == 1) {
                            omni::sync::mutex_unlock(this->m_mtx);
                            return;
                        }
                        omni::sync::mutex_unlock(this->m_mtx);
                        OMNI_THREAD_YIELD();
                    }
                }

                bool busy_wait(uint32_t timeout_ms) const
                {
                    omni::chrono::tick_t start = omni::chrono::monotonic_tick();
                    while (omni::chrono::elapsed_ms(start) <= timeout_ms) {
                        omni::sync::mutex_lock(this->m_mtx);
                        if (this->m_sig == 1) {
                            omni::sync::mutex_unlock(this->m_mtx);
                            return true;
                        }
                        omni::sync::mutex_unlock(this->m_mtx);
                        OMNI_THREAD_YIELD();
                    }
                    // if !this->m_sig, then the timeout failed
                    omni::sync::mutex_lock(this->m_mtx);
                    if (this->m_sig == 1) {
                        omni::sync::mutex_unlock(this->m_mtx);
                        return true;
                    }
                    omni::sync::mutex_unlock(this->m_mtx);
                    return false;
                }
                
                void sleep_wait() const
                {
                    OMNI_SLEEP_INIT();
                    for(;;) {
                        omni::sync::mutex_lock(this->m_mtx);
                        if (this->m_sig == 1) {
                            omni::sync::mutex_unlock(this->m_mtx);
                            return;
                        }
                        omni::sync::mutex_unlock(this->m_mtx);
                        OMNI_SLEEP1();
                    }
                }

                bool sleep_wait(uint32_t timeout_ms) const
                {
                    OMNI_SLEEP_INIT();
                    omni::chrono::tick_t start = omni::chrono::monotonic_tick();
                    while (omni::chrono::elapsed_ms(start) <= timeout_ms) {
                        omni::sync::mutex_lock(this->m_mtx);
                        if (this->m_sig == 1) {
                            omni::sync::mutex_unlock(this->m_mtx);
                            return true;
                        }
                        omni::sync::mutex_unlock(this->m_mtx);
                        OMNI_SLEEP1();
                    }
                    // if !this->m_sig, then the timeout failed
                    omni::sync::mutex_lock(this->m_mtx);
                    if (this->m_sig == 1) {
                        omni::sync::mutex_unlock(this->m_mtx);
                        return true;
                    }
                    omni::sync::mutex_unlock(this->m_mtx);
                    return false;
                }
                
                bool operator==(const omni::sync::safe_spin_wait& o) const
                {
                    if (this == &o) { return true; }
                    omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                    omni::sync::scoped_lock<omni::sync::mutex_t> alock2(&o.m_mtx);
                    return (this->m_sig == o.m_sig)
                    OMNI_EQUAL_FW(o);
                }

                bool operator!=(const omni::sync::safe_spin_wait& o) const
                {
                    return !(*this == o);
                }
                
                OMNI_MEMBERS_FW(omni::sync::safe_spin_wait) // disposing,name,type(),hash()
                
            private:
                mutable omni::sync::mutex_t m_mtx;
                volatile mutable OMNI_SPIN_INT_FW m_sig;
                
                // defined but not implemented. should not be copied
                safe_spin_wait(const omni::sync::safe_spin_wait& cp); // C++1X delete 
                omni::sync::safe_spin_wait& operator=(const omni::sync::safe_spin_wait& other); // C++1X delete
        };
        
        typedef omni::sync::auto_lock<omni::sync::spin_lock> auto_spin_lock;
        typedef omni::sync::scoped_lock<omni::sync::spin_lock> scoped_spin_lock;
    }
}

#endif // OMNI_SPIN_HPP
