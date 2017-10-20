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
#if !defined(OMNI_SCOPED_LOCK_HPP)
#define OMNI_SCOPED_LOCK_HPP 1
#include <omni/defs/global.hpp>
#include <omni/sync/lock.hpp>

namespace omni {
    namespace sync {
        template < typename T >
        class scoped_lock
        {
            public:
                explicit scoped_lock(T* l) : m_hndl(l)
                {
                    this->m_hndl->lock();
                }
                
                ~scoped_lock()
                {
                    this->m_hndl->unlock();
                }
                
                const T *const handle() const
                {
                    return this->m_hndl;
                }
                
                bool operator==(const scoped_lock& o) const
                {
                    return (this->m_hndl == o.m_hndl);
                }
                
                bool operator==(const T& o) const
                {
                    return (this->m_hndl == &o);
                }
                
                bool operator!=(const scoped_lock& o) const
                {
                    return !(this->m_hndl == o.m_hndl);
                }
                
                bool operator!=(const T& o) const
                {
                    return !(this->m_hndl == &o);
                }
                
            private:
                scoped_lock();
                scoped_lock(const scoped_lock& cp);
                scoped_lock& operator=(const scoped_lock& cp);
                
                T* m_hndl;
        };
        
        template <>
        class scoped_lock <omni::sync::mutex_t>
        {
            public:
                explicit scoped_lock(omni::sync::mutex_t* m) : m_mtx(m)
                {
                    omni::sync::mutex_lock(*this->m_mtx);
                }
                
                ~scoped_lock()
                {
                    omni::sync::mutex_unlock(*this->m_mtx);
                }

                const omni::sync::mutex_t *const handle() const
                {
                    return this->m_mtx;
                }
                
                bool operator==(const scoped_lock& o) const
                {
                    return (this->m_mtx == o.m_mtx);
                }
                
                bool operator==(const omni::sync::mutex_t& o) const
                {
                    return (this->m_mtx == &o);
                }
                
                bool operator!=(const scoped_lock& o) const
                {
                    return !(this->m_mtx == o.m_mtx);
                }
                
                bool operator!=(const omni::sync::mutex_t& o) const
                {
                    return !(this->m_mtx == &o);
                }
                
            private:
                scoped_lock();
                scoped_lock(const scoped_lock& cp);
                scoped_lock& operator=(const scoped_lock& cp);
                
                omni::sync::mutex_t* m_mtx;
        };
    }
}

#endif // OMNI_SCOPED_LOCK_HPP
