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
#ifndef OMNI_GEN_PTR_HPP
#define OMNI_GEN_PTR_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/type.hpp>
#include <omni/sync/scoped_lock.hpp>

namespace omni {
    class generic_ptr
    {
        public:
            generic_ptr() :
                OMNI_CTOR_FW(omni::generic_ptr)
                m_ptr(OMNI_NULL), m_id(0)
            {
                OMNI_D5_FW("created");
            }

            template < typename T >
            generic_ptr(T *const obj) : 
                OMNI_CTOR_FW(omni::generic_ptr)
                m_ptr(obj), m_id(omni::type_id<T>())
            {
                OMNI_DV5_FW("created with id of ", this->m_id);
            }

            generic_ptr(const generic_ptr& o) : 
                OMNI_CTOR_FW(omni::generic_ptr)
                m_ptr(o.m_ptr), m_id(o.m_id)
            {
                OMNI_DV5_FW("copied with id of ", this->m_id);
            }
            
            ~generic_ptr()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                this->invalidate();
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            static generic_ptr null()
            {
                return generic_ptr();
            }
            
            void invalidate()
            {
                this->m_ptr = OMNI_NULL;
                this->m_id = 0;
            }

            template < typename T >
            bool is_type() const
            { return this->m_id == omni::type_id<T>(); }
            
            bool valid() const { return (this->m_ptr != OMNI_NULL); }
            
            operator bool() const
            {
                return (this->m_ptr != OMNI_NULL);
            }
            
            bool operator!() const
            {
                return (!operator bool());
            }
            
            generic_ptr& operator=(const generic_ptr& o)
            {
                if (this != & o) {
                    OMNI_ASSIGN_FW(o)
                    this->m_ptr = o.m_ptr;
                    this->m_id = o.m_id;
                    OMNI_DV5_FW("assigned id ", this->m_id);
                }
                return *this;
            }

            template < typename T >
            const generic_ptr& operator=(T *const obj)
            {
                this->m_ptr = obj;
                this->m_id = omni::type_id<T>();
                OMNI_DV5_FW("set type id ", this->m_id);
                return *this;
            }

            template < typename T >
            operator T *const() const
            {
                if (this->m_id != omni::type_id<T>()) {
                    OMNI_ERR_RETV_FW("invalid cast detected", omni::exceptions::invalid_type_cast(), 0)
                }
                return static_cast<T *const>(
                    const_cast<void *const>(this->m_ptr)
                );
            }

            template < typename T >
            operator const T *const() const
            {
                if ((this->m_id != omni::type_id<T>()) && (this->m_id != omni::type_id<const T>())) {
                    OMNI_ERR_RETV_FW("invalid cast detected", omni::exceptions::invalid_type_cast(), 0);
                }
                return static_cast<const T *const>(this->m_ptr);
            }
            
            operator void *const() const { return const_cast<void*>(this->m_ptr); }
            
            operator const void *const() const { return this->m_ptr; }
            
            bool operator==(const generic_ptr& o) const
            {
                return (this->m_ptr == o.m_ptr && this->m_id == o.m_id);
            }
            
            bool operator!=(const generic_ptr& o) const
            {
                return !(*this == o);
            }
            
            OMNI_MEMBERS_FW(omni::generic_ptr) // disposing,name,type(),hash()
                
        private:
            const void* m_ptr;
            uint64_t m_id;
    };
    
    class generic_ptr_safe
    {
        public:
            generic_ptr_safe() :
                OMNI_CTOR_FW(omni::generic_ptr_safe)
                m_ptr(OMNI_NULL), m_id(0), m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                OMNI_D5_FW("created");
            }

            template < typename T >
            generic_ptr_safe(T *const obj) : 
                OMNI_CTOR_FW(omni::generic_ptr_safe)
                m_ptr(obj), m_id(omni::type_id<T>()), m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                OMNI_DV5_FW("created with id of ", this->m_id);
            }

            generic_ptr_safe(const generic_ptr_safe& o) : 
                OMNI_CTOR_FW(omni::generic_ptr_safe)
                m_ptr(o.m_ptr), m_id(o.m_id), m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                OMNI_DV5_FW("coppied with id of ", this->m_id);
            }
            
            ~generic_ptr_safe()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                this->invalidate();
                omni::sync::mutex_destroy(this->m_mtx);
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            static generic_ptr_safe null()
            {
                return generic_ptr_safe();
            }
            
            void invalidate()
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                this->m_ptr = OMNI_NULL;
                this->m_id = 0;
            }
            
            template < typename T >
            bool is_type() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return this->m_id == omni::type_id<T>();
            }

            bool valid() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return (this->m_ptr != OMNI_NULL);
            }
            
            operator bool() const
            {
                return this->valid();
            }
            
            bool operator!() const
            {
                return (!operator bool());
            }
            
            generic_ptr_safe& operator=(const generic_ptr_safe& o)
            {
                if (this != &o) {
                    OMNI_ASSIGN_FW(o)
                    omni::sync::scoped_lock<omni::sync::mutex_t> a1(&this->m_mtx);
                    omni::sync::scoped_lock<omni::sync::mutex_t> a2(&o.m_mtx);
                    this->m_ptr = o.m_ptr;
                    this->m_id = o.m_id;
                }
                return *this;
            }

            template < typename T >
            const generic_ptr_safe& operator=(T *const obj)
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                this->m_ptr = obj;
                this->m_id = omni::type_id<T>();
                OMNI_DV5_FW("set type id ", this->m_id);
                return *this;
            }

            template < typename T >
            operator T *const() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                if (this->m_id != omni::type_id<T>()) {
                    OMNI_ERR_RETV_FW("invalid cast detected", omni::exceptions::invalid_type_cast(), 0)
                }
                return static_cast<T *const>(
                    const_cast<void *const>(this->m_ptr)
                );
            }

            template < typename T >
            operator const T *const() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                if ((this->m_id != omni::type_id<T>()) && (this->m_id != omni::type_id<const T>())) {
                    OMNI_ERR_RETV_FW("invalid cast detected", omni::exceptions::invalid_type_cast(), 0);
                }
                return static_cast<const T *const>(this->m_ptr);
            }
            
            operator void *const() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return const_cast<void*>(this->m_ptr);
            }
            
            operator const void *const() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return this->m_ptr;
            }
            
            bool operator==(const generic_ptr_safe& o) const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> a1(&this->m_mtx);
                omni::sync::scoped_lock<omni::sync::mutex_t> a2(&o.m_mtx);
                return (this->m_ptr == o.m_ptr && this->m_id == o.m_id);
            }
            
            bool operator!=(const generic_ptr_safe& o) const
            {
                return !(*this == o);
            }
            
            OMNI_MEMBERS_FW(omni::generic_ptr_safe) // disposing,name,type(),hash()
                
        private:
            const void* m_ptr;
            uint64_t m_id;
            mutable omni::sync::mutex_t m_mtx;
    };
}

#endif // OMNI_GEN_PTR_HPP
