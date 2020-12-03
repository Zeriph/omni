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
#ifndef OMNI_SMART_PTR_HPP
#define OMNI_SMART_PTR_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/sync/lock.hpp>
#include <omni/sync/scoped_lock.hpp>

/*
    TODO: make docugen note about how smart_ptr to an array pointer will not call delete[]
    (smart_ptr<obj[]> has to be smart_ptr<obj*>), if you want a smart_ptr<obj[]> use an STL
    container instead (like a std::vector<obj> or std::deque<obj>)
*/

#if !defined(OMNI_SMART_PTR_SIZE_T)
    /*
        This defines the underlying size type used by the smart pointer
        types. it is a hash-def because making a smart_ptr templated with
        a type and a size type would make the smart pointer class well
        more complicated than necessary; the hash-def allows platform
        specific size types to be utilized.
    */
    #define OMNI_SMART_PTR_SIZE_T uint64_t
#endif

namespace omni {
    template < typename T >
    class smart_ptr
    {
        public:
            /** Defines the underlying type of this instance */
            typedef T pointer_t;
            /** Specifies the underlying size type defined */
            typedef OMNI_SMART_PTR_SIZE_T size_type;

            smart_ptr() :
                OMNI_CTOR_FW(omni::smart_ptr<T>)
                m_ptr(OMNI_NULL),
                m_cnt(0)
            {
                OMNI_D5_FW("created empty smart_ptr");
            }
            
            OMNI_EXPLICIT smart_ptr(pointer_t* val) :
                OMNI_CTOR_FW(omni::smart_ptr<T>)
                m_ptr(val),
                m_cnt((val == OMNI_NULL) ? 0 : 1)
            {
                OMNI_D5_FW("created by ptr");
            }
            
            smart_ptr(const smart_ptr< T >& cp) :
                OMNI_CPCTOR_FW(cp)
                m_ptr(cp.m_ptr), 
                m_cnt(cp.m_cnt+1)
            {
                ++cp.m_cnt;
                OMNI_DV5_FW("created by copy, ref count = ", this->m_cnt);
            }
            
            ~smart_ptr()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                this->_decrement();
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            size_type count() const
            {
                return this->m_cnt;
            }

            smart_ptr& reset()
            {
                this->_decrement();
                this->m_ptr = OMNI_NULL;
                this->m_cnt = 0;
                return *this;
            }
            
            bool valid() const
            {
                return (this->m_ptr != OMNI_NULL);
            }

            T* value() const
            {
                return this->m_ptr;
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
            
            bool operator==(const smart_ptr< T >& val) const
            {
                if (this == &val) { return true; }
                return (this->m_ptr == val.m_ptr &&
                        this->m_cnt == val.m_cnt)
                        OMNI_EQUAL_FW(val);
            }
            
            bool operator!=(const smart_ptr< T >& val) const
            {
                return !(*this == val);
            }
            
            smart_ptr& operator=(const smart_ptr< T >& val)
            {
                if (this != &val) {
                    OMNI_ASSIGN_FW(val)
                    if (this->m_ptr != val.m_ptr) {
                        this->_decrement();
                        this->m_ptr = val.m_ptr;
                        if (this->m_ptr != OMNI_NULL) {
                            this->m_cnt = ++val.m_cnt;
                        }
                    }
                }
                return *this;
            }

            smart_ptr& operator=(pointer_t* val)
            {
                if (this->m_ptr != val) {
                    this->_decrement();
                    this->m_ptr = val;
                    if (this->m_ptr != OMNI_NULL) {
                        ++this->m_cnt;
                    }
                }
                return *this;
            }
            
            OMNI_MEMBERS_FW(omni::smart_ptr<T>) // disposing,name,type(),hash()

            static inline smart_ptr get_instance_reference(pointer_t* val)
            {
                smart_ptr ret(val);
                ++ret.m_cnt;
                return ret;
            }
            
        private:
            T* m_ptr;
            mutable size_type m_cnt;

            inline void _decrement()
            {
                if ((this->m_cnt > 0) && (--this->m_cnt == 0)) {
                    OMNI_D5_FW("ref count == 0, freeing pointers");
                    if (this->m_ptr != OMNI_NULL) {
                        OMNI_FREE(this->m_ptr);
                    }
                }
            }
    };
    
    template < typename T >
    class smart_ptr_safe
    {
        public:
            /** Defines the underlying type of this instance */
            typedef T pointer_t;
            /** Specifies the underlying size type defined */
            typedef OMNI_SMART_PTR_SIZE_T size_type;

            smart_ptr_safe() :
                OMNI_CTOR_FW(omni::smart_ptr_safe<T>)
                m_ptr(OMNI_NULL),
                m_cnt(0),
                m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                OMNI_D5_FW("created by ptr");
            }
            
            OMNI_EXPLICIT smart_ptr_safe(pointer_t* val) :
                OMNI_CTOR_FW(omni::smart_ptr_safe<T>)
                m_ptr(val),
                m_cnt((val == OMNI_NULL) ? 0 : 1),
                m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                OMNI_D5_FW("created by ptr");
            }

            smart_ptr_safe(const smart_ptr_safe<T>& cp) :
                OMNI_CPCTOR_FW(cp)
                m_ptr(), 
                m_cnt(),
                m_mtx()
            {
                omni::sync::mutex_init(this->m_mtx);
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&cp.m_mtx);
                this->m_cnt = ++cp.m_cnt;
                this->m_ptr = cp.m_ptr;
                OMNI_DV5_FW("created by copy, ref count = ", this->m_cnt);
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

            size_type count() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return this->m_cnt;
            }

            smart_ptr_safe& reset()
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                this->_dec_no_lock();
                this->m_ptr = OMNI_NULL;
                this->m_cnt = 0;
                return *this;
            }
            
            bool valid() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return (this->m_ptr != OMNI_NULL);
            }

            T const* value() const
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                return this->m_ptr;
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
            
            bool operator==(const smart_ptr_safe< T >& val) const
            {
                if (this == &val) { return true; }
                omni::sync::scoped_lock<omni::sync::mutex_t> a1(&this->m_mtx);
                omni::sync::scoped_lock<omni::sync::mutex_t> a2(&val.m_mtx);
                return (this->m_ptr == val.m_ptr &&
                        this->m_cnt == val.m_cnt)
                OMNI_EQUAL_FW(val);
            }
            
            bool operator!=(const smart_ptr_safe< T >& val) const
            {
                return !(*this == val);
            }
            
            smart_ptr_safe& operator=(const smart_ptr_safe<T>& val)
            {
                if (this != &val) {
                    omni::sync::mutex_lock(this->m_mtx);
                    omni::sync::mutex_lock(val.m_mtx);
                    OMNI_ASSIGN_FW(val)
                    if (this->m_ptr != val.m_ptr) {
                        this->_dec_no_lock();
                        this->m_ptr = val.m_ptr;
                        if (this->m_ptr != OMNI_NULL) {
                            this->m_cnt = ++val.m_cnt;
                        }
                    }
                    omni::sync::mutex_unlock(this->m_mtx);
                    omni::sync::mutex_unlock(val.m_mtx);
                }
                return *this;
            }

            smart_ptr_safe& operator=(pointer_t* val)
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                if (this->m_ptr != val) {
                    this->_dec_no_lock();
                    this->m_ptr = val;
                    if (this->m_ptr != OMNI_NULL) {
                        ++this->m_cnt;
                    }
                }
                return *this;
            }
            
            OMNI_MEMBERS_FW(omni::smart_ptr_safe<T>) // disposing,name,type(),hash()

            static inline smart_ptr_safe get_instance_reference(pointer_t* val)
            {
                smart_ptr_safe ret(val);
                ++ret.m_cnt;
                return ret;
            }
            
        private:
            T* m_ptr;
            mutable size_type m_cnt;
            mutable omni::sync::mutex_t m_mtx;

            inline void _decrement()
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                this->_dec_no_lock();
            }

            inline void _dec_no_lock()
            {
                if ((this->m_cnt > 0) && (--this->m_cnt == 0)) {
                    OMNI_D5_FW("ref count == 0, freeing pointers");
                    if (this->m_ptr != OMNI_NULL) {
                        OMNI_FREE(this->m_ptr);
                    }
                }
            }
            
            inline void _increment()
            {
                omni::sync::scoped_lock<omni::sync::mutex_t> alock(&this->m_mtx);
                ++this->m_cnt;
            }
    };
}

#endif // OMNI_SMART_PTR_HPP
