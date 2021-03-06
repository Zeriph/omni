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
                OMNI_EXPLICIT scoped_lock(T* l) : m_hndl(l)
                {
                    this->m_hndl->lock();
                }
                
                ~scoped_lock()
                {
                    this->m_hndl->unlock();
                }
                
                T* handle() const
                {
                    return this->m_hndl;
                }
                
                bool operator==(const omni::sync::scoped_lock<T>& o) const
                {
                    return (this->m_hndl == o.m_hndl);
                }
                
                bool operator==(const T& o) const
                {
                    return (this->m_hndl == &o);
                }
                
                bool operator!=(const omni::sync::scoped_lock<T>& o) const
                {
                    return !(this->m_hndl == o.m_hndl);
                }
                
                bool operator!=(const T& o) const
                {
                    return !(this->m_hndl == &o);
                }
                
            private:
                T* m_hndl;

                scoped_lock();
                scoped_lock(const omni::sync::scoped_lock<T>& cp);
                scoped_lock& operator=(const omni::sync::scoped_lock<T>& cp);
        };
        
        template <>
        class scoped_lock <omni::sync::mutex_t>
        {
            public:
                OMNI_EXPLICIT scoped_lock(omni::sync::mutex_t* m) : m_mtx(m)
                {
                    omni::sync::mutex_lock(*this->m_mtx);
                }
                
                ~scoped_lock()
                {
                    omni::sync::mutex_unlock(*this->m_mtx);
                }

                omni::sync::mutex_t* handle() const
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
                omni::sync::mutex_t* m_mtx;

                scoped_lock();
                scoped_lock(const scoped_lock& cp);
                scoped_lock& operator=(const scoped_lock& cp);
        };
    }
}

#endif // OMNI_SCOPED_LOCK_HPP
