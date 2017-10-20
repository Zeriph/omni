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
#ifndef OMNI_SMART_PTR_HPP
#define OMNI_SMART_PTR_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/sync/lock.hpp>
#include <omni/sync/scoped_lock.hpp>

namespace omni {
    template < typename T >
    class smart_ptr
    {
        public:
            /** Defines the underlying type of this instance */
            typedef T pointer_t;
            
            explicit smart_ptr(pointer_t *val = OMNI_NULL) :
                OMNI_CTOR_FW(omni::smart_ptr<T>)
                m_ptr(val),
                m_cnt(new unsigned long long(1))
            {
                OMNI_D5_FW("created by ptr");
            }
            
            smart_ptr(const smart_ptr<T> &cp) :
                OMNI_CPCTOR_FW(cp)
                m_ptr(cp.m_ptr), 
                m_cnt(cp.m_cnt)
            {
                this->_increment();
                OMNI_DV5_FW("created by copy, ref count = ", *this->m_cnt);
            }

            template < typename T1 >
            smart_ptr(smart_ptr<T1> &cp) :
                OMNI_CPCTOR_FW(cp)
                m_ptr(cp.m_ptr), 
                m_cnt(cp.m_cnt)
            {
                this->_increment();
                OMNI_DV5_FW("created by copy, ref count = ", *this->m_cnt);
            }
            
            ~smart_ptr()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                this->_decrement();
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }
            
            bool valid() const
            {
                return (this->m_ptr != OMNI_NULL);
            }
            
            operator bool() const
            {
                return valid();
            }
            
            bool operator!() const
            {
                return (!operator bool());
            }
            
            pointer_t& operator*() const
            {
                return *this->m_ptr;
            }

            pointer_t* operator->() const
            {
                return this->m_ptr;
            }
            
            bool operator==(const smart_ptr< T > &val) const
            {
                if (this == &val) { return true; }
                return (this->m_ptr == val.m_ptr && this->m_cnt == val.m_cnt)
                OMNI_EQUAL_FW(val);
            }
            
            bool operator!=(const smart_ptr< T > &val) const
            {
                return !(*this == val);
            }
            
            smart_ptr<T>& operator=(const smart_ptr<T> &val)
            {
                if (this != &val) {
                    this->_decrement();
                    OMNI_ASSIGN_FW(val)
                    this->m_ptr = val.m_ptr;
                    this->m_cnt = val.m_cnt;
                    this->_increment();
                }
                return *this;
            }
            
            template < typename T1 >
            smart_ptr& operator=(const smart_ptr<T1> &val)
            {
                if (this != &val) {
                    this->_decrement();
                    OMNI_ASSIGN_FW(val)
                    this->m_ptr = val.m_ptr;
                    this->m_cnt = val.m_cnt;
                    this->_increment();
                }
                return *this;
            }
            
            smart_ptr<T>& operator=(pointer_t *val)
            {
                if (this->m_ptr != val) {
                    this->_decrement();
                    #if defined(OMNI_TYPE_INFO)
                        this->m_type = omni::type_id< omni::smart_ptr<T> >();
                    #endif
                    this->m_ptr = val;
                    this->_increment();
                }
                return *this;
            }
            
            OMNI_MEMBERS_FW(omni::smart_ptr<T>) // disposing,name,type(),hash()
            
        private:
            inline void _decrement()
            {
                if (--*this->m_cnt == 0) {
                    OMNI_D5_FW("ref count == 0, freeing pointers");
                    delete this->m_cnt;
                    delete this->m_ptr;
                    this->m_cnt = OMNI_NULL;
                    this->m_ptr = OMNI_NULL;
                }
            }
            
            inline void _increment()
            {
                if (!this->m_cnt) { this->m_cnt = new unsigned long long(0); }
                ++*this->m_cnt;
            }
            
            #if defined(OMNI_TYPE_INFO)
                omni::type< omni::smart_ptr<T> > m_type;
            #endif
            T* m_ptr;
            unsigned long long* m_cnt;
    };
    
    template < typename T >
    class smart_ptr_safe
    {
        public:
            /** Defines the underlying type of this instance */
            typedef T pointer_t;
            
            explicit smart_ptr_safe(pointer_t *val = 0) :
                OMNI_CTOR_FW(omni::smart_ptr_safe<T>)
                m_ptr(val),
                m_cnt(new unsigned long long(1)),
                m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                OMNI_D5_FW("created by ptr");
            }

            smart_ptr_safe(const smart_ptr_safe<T> &cp) :
                OMNI_CPCTOR_FW(cp)
                m_ptr(cp.m_ptr), 
                m_cnt(cp.m_cnt),
                m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                this->_increment();
                OMNI_DV5_FW("created by copy, ref count = ", *this->m_cnt);
            }

            template < typename T1 >
            smart_ptr_safe(smart_ptr_safe<T1> &cp) :
                OMNI_CPCTOR_FW(cp)
                m_ptr(cp.m_ptr), 
                m_cnt(cp.m_cnt),
                m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                this->_increment();
                OMNI_DV5_FW("created by copy, ref count = ", *this->m_cnt);
            }
            
            ~smart_ptr_safe()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                this->_decrement();
                omni::sync::mutex_destroy(this->m_mtx);
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }
            
            bool valid() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return (this->m_ptr != 0);
            }
            
            operator bool() const
            {
                return this->valid();
            }
            
            bool operator!() const
            {
                return (!operator bool());
            }
            
            pointer_t& operator*() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return *this->m_ptr;
            }

            pointer_t* operator->() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return this->m_ptr;
            }
            
            bool operator==(const smart_ptr_safe< T > &val) const
            {
                if (this == &val) { return true; }
                omni::sync::scoped_lock<omni::sync::mutex_t> a1(&this->m_mtx);
                omni::sync::scoped_lock<omni::sync::mutex_t> a2(&val.m_mtx);
                return (this->m_ptr == val.m_ptr && this->m_cnt == val.m_cnt)
                OMNI_EQUAL_FW(val);
            }
            
            bool operator!=(const smart_ptr_safe< T > &val) const
            {
                return !(*this == val);
            }
            
            smart_ptr_safe<T>& operator=(const smart_ptr_safe<T> &val)
            {
                if (this != &val) {
                    this->_decrement();
                    omni::sync::mutex_lock(this->m_mtx);
                    omni::sync::mutex_lock(val.m_mtx);
                    OMNI_ASSIGN_FW(val)
                    this->m_ptr = val.m_ptr;
                    this->m_cnt = val.m_cnt;
                    omni::sync::mutex_unlock(this->m_mtx);
                    omni::sync::mutex_unlock(val.m_mtx);
                    this->_increment();
                }
                return *this;
            }
            
            template < typename T1 >
            smart_ptr_safe& operator=(const smart_ptr_safe<T1> &val)
            {
                if (this != &val) {
                    this->_decrement();
                    omni::sync::mutex_lock(this->m_mtx);
                    omni::sync::mutex_lock(val.m_mtx);
                    OMNI_ASSIGN_FW(val)
                    this->m_ptr = val.m_ptr;
                    this->m_cnt = val.m_cnt;
                    omni::sync::mutex_unlock(this->m_mtx);
                    omni::sync::mutex_unlock(val.m_mtx);
                    this->_increment();
                }
                return *this;
            }
            
            smart_ptr_safe<T>& operator=(pointer_t *val)
            {
                if (this->m_ptr != val) {
                    this->_decrement();
                    omni::sync::mutex_lock(this->m_mtx);
                    #if defined(OMNI_TYPE_INFO)
                        this->m_type = omni::type_id< omni::smart_ptr_safe<T> >();
                    #endif
                    this->m_ptr = val;
                    omni::sync::mutex_unlock(this->m_mtx);
                    this->_increment();
                }
                return *this;
            }
            
            OMNI_MEMBERS_FW(omni::smart_ptr_safe<T>) // disposing,name,type(),hash()
            
        private:
            inline void _decrement()
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                if (--*this->m_cnt == 0) {
                    OMNI_D5_FW("ref count == 0, freeing pointers");
                    delete this->m_cnt;
                    delete this->m_ptr;
                    this->m_cnt = 0;
                    this->m_ptr = 0;
                }
            }
            
            inline void _increment()
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                if (!this->m_cnt) { this->m_cnt = new unsigned long long(0); }
                ++*this->m_cnt;
            }
            
            #if defined(OMNI_TYPE_INFO)
                omni::type< omni::smart_ptr_safe<T> > m_type;
            #endif
            T* m_ptr;
            unsigned long long* m_cnt;
            mutable omni::sync::mutex_t m_mtx;
    };
}

#endif // OMNI_SMART_PTR_HPP
