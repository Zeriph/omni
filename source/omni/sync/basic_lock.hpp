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
#if !defined(OMNI_BASIC_LOCK_HPP)
#define OMNI_BASIC_LOCK_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/sync/lock.hpp>
#include <omni/sync/auto_lock.hpp>
#include <omni/sync/scoped_lock.hpp>

namespace omni {
    namespace sync {
        class basic_lock
        {
            public:
                basic_lock() :
                    OMNI_CTOR_FW(omni::sync::basic_lock)
                    m_lokd(0), m_mtx()
                {
                    omni::sync::mutex_init(this->m_mtx);
                }
                
                explicit basic_lock(bool initialy_owned) :
                    OMNI_CTOR_FW(omni::sync::basic_lock)
                    m_lokd(0), m_mtx()
                {
                    omni::sync::mutex_init(this->m_mtx);
                    if (initialy_owned) { this->lock(); }
                }
                
                ~basic_lock()
                {
                    OMNI_DTOR_FW
                    if (this->locked()) {
                        OMNI_TERMINATE_FW("system mutex is locked on destruction")
                    }
                    omni::sync::mutex_destroy(this->m_mtx);
                    OMNI_D5_FW("destroyed");
                }
                
                const omni::sync::mutex_t handle() const
                {
                    return this->m_mtx;
                }
                
                bool locked() const
                {
                    return (this->m_lokd > 0);
                }
                
                void lock()
                {
                    omni::sync::mutex_lock(this->m_mtx);
                    ++this->m_lokd;
                }
                
                bool lock(uint32_t timeout_ms)
                {
                    if (omni::sync::mutex_lock(this->m_mtx, timeout_ms)) {
                        ++this->m_lokd;
                        return true;
                    }
                    return false;
                }
                
                void unlock()
                {
                    omni::sync::mutex_unlock(this->m_mtx);
                    --this->m_lokd;
                }
                
                bool trylock()
                {
                    if (omni::sync::mutex_trylock(this->m_mtx)) {
                        ++this->m_lokd;
                        return true;
                    }
                    return false;
                }
                
                bool operator==(const omni::sync::basic_lock& o) const
                {
                    if (this == &o) { return true; }
                    return this->m_lokd == o.m_lokd &&
                           &this->m_mtx == &o.m_mtx
                           OMNI_EQUAL_FW(o);
                }
                
                bool operator==(const omni::sync::mutex_t& o) const
                {
                    return (&this->m_mtx == &o);
                }
                
                bool operator!=(const omni::sync::basic_lock& o) const
                {
                    return !(*this == o);
                }
                
                bool operator!=(const omni::sync::mutex_t& o) const
                {
                    return !(&this->m_mtx == &o);
                }
                
                OMNI_MEMBERS_FW(omni::sync::basic_lock) // disposing,name,type(),hash()
                
            private:
                // defined but not implemented, should not be copied
                basic_lock(const omni::sync::basic_lock &cp);
                omni::sync::basic_lock& operator=(const omni::sync::basic_lock& other);
                
                volatile uint32_t m_lokd;
                omni::sync::mutex_t m_mtx;
        };
        
        /** Auto basic lock */
        typedef omni::sync::auto_lock<omni::sync::basic_lock> auto_basic_lock;
        
        /** Scoped basic lock */
        typedef omni::sync::scoped_lock<omni::sync::basic_lock> scoped_basic_lock;
    }
}

#endif // OMNI_BASIC_LOCK_HPP
