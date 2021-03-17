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
#if !defined(OMNI_AUTO_LOCK_HPP)
#define OMNI_AUTO_LOCK_HPP 1
#include <omni/defs/global.hpp>
#include <omni/sync/lock.hpp>

namespace omni {
    namespace sync {
        template < typename T >
        class auto_lock
        {
            public:
                OMNI_EXPLICIT auto_lock(T* l) : m_hndl(l)
                {
                    if (this->m_hndl) { this->m_hndl->lock(); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception())
                    }
                }
                
                ~auto_lock()
                {
                    if (this->m_hndl) { this->m_hndl->unlock(); }
                }
                
                const T* handle() const
                {
                    return this->m_hndl;
                }
                
                void lock()
                {
                    if (this->m_hndl) { this->m_hndl->lock(); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                }
                
                bool lock(uint32_t timeout_ms)
                {
                    if (this->m_hndl) { return this->m_hndl->lock(timeout_ms); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                    return false;
                }
                
                bool trylock()
                {
                    if (this->m_hndl) { return this->m_hndl->trylock(); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                    return false;
                }
                
                void unlock()
                {
                    if (this->m_hndl) { this->m_hndl->unlock(); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                }
                
                bool operator==(const auto_lock& o) const
                {
                    return (this->m_hndl == o.m_hndl);
                }
                
                bool operator==(const T& o) const
                {
                    return (this->m_hndl == &o);
                }
                
                bool operator!=(const auto_lock& o) const
                {
                    return !(this->m_hndl == o.m_hndl);
                }
                
                bool operator!=(const T& o) const
                {
                    return !(this->m_hndl == &o);
                }
                
            private:
                T* m_hndl;
                
                auto_lock();
                auto_lock(const auto_lock& cp);
                auto_lock& operator=(const auto_lock& cp);
        };
        
        template <>
        class auto_lock <omni::sync::mutex_t>
        {
            public:
                OMNI_EXPLICIT auto_lock(omni::sync::mutex_t* m) : m_hndl(m)
                {
                    if (this->m_hndl) { omni::sync::mutex_lock(*this->m_hndl); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                }
                
                ~auto_lock()
                {
                    if (this->m_hndl) { omni::sync::mutex_unlock(*this->m_hndl); }
                    // do not error on destruction
                }

                const omni::sync::mutex_t* handle() const
                {
                    return this->m_hndl;
                }
                
                void lock()
                {
                    if (this->m_hndl) { omni::sync::mutex_lock(*this->m_hndl); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                }
                
                bool lock(uint32_t timeout_ms)
                {
                    if (this->m_hndl) { return omni::sync::mutex_lock(*this->m_hndl, timeout_ms); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                    return false;
                }
                
                bool trylock()
                {
                    if (this->m_hndl) { return omni::sync::mutex_trylock(*this->m_hndl); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                    return false;
                }
                
                void unlock()
                {
                    if (this->m_hndl) { omni::sync::mutex_unlock(*this->m_hndl); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                }
                
                bool operator==(const auto_lock& o) const
                {
                    return (this->m_hndl == o.m_hndl);
                }
                
                bool operator==(const omni::sync::mutex_t& o) const
                {
                    return (this->m_hndl == &o);
                }
                
                bool operator!=(const auto_lock& o) const
                {
                    return !(this->m_hndl == o.m_hndl);
                }
                
                bool operator!=(const omni::sync::mutex_t& o) const
                {
                    return !(this->m_hndl == &o);
                }
                
            private:
                omni::sync::mutex_t* m_hndl;

                auto_lock();
                auto_lock(const auto_lock& cp);
                auto_lock& operator=(const auto_lock& cp);
        };
    }
}

#endif // OMNI_AUTO_LOCK_HPP
