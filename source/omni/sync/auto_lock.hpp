/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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
                explicit auto_lock(T* l) : m_hndl(l)
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
                
                const T *const handle() const
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
                
                bool lock(std::size_t timeout_ms)
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
                auto_lock();
                auto_lock(const auto_lock& cp);
                auto_lock& operator=(const auto_lock& cp);
                
                T* m_hndl;
        };
        
        template <>
        class auto_lock <omni::sync::mutex_t>
        {
            public:
                explicit auto_lock(omni::sync::mutex_t* m) : m_hndl(m)
                {
                    if (this->m_hndl) { omni::sync::mutex_lock(*this->m_hndl); }
                    else {
                        OMNI_ERR_FW("invalid pointer", omni::exceptions::null_pointer_exception());
                    }
                }
                
                ~auto_lock()
                {
                    if (this->m_hndl) { omni::sync::mutex_unlock(*this->m_hndl); }
                    // don't error on destruction
                }

                const omni::sync::mutex_t *const handle() const
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
                
                bool lock(std::size_t timeout_ms)
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
                auto_lock();
                auto_lock(const auto_lock& cp);
                auto_lock& operator=(const auto_lock& cp);
                
                omni::sync::mutex_t* m_hndl;
        };
    }
}

#endif // OMNI_AUTO_LOCK_HPP
