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
#if !defined(OMNI_DELEGATE2_HPP)
#define OMNI_DELEGATE2_HPP 1
#include <omni/defs/delegate_def.hpp>
#include <omni/types/invoke_t.hpp>

namespace omni {
    template < typename Ret, typename PT1, typename PT2 >
    class delegate2
    {
        public:
            typedef Ret ret_t;
            typedef PT1 p1_t;
            typedef PT2 p2_t;

            typedef ret_t (*functor)(void* extObj, p1_t val1, p2_t val2);
            typedef ret_t (*function_ptr)(p1_t val1, p2_t val2);
            
            delegate2() :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(OMNI_NULL),
                m_target(OMNI_NULL)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate");
            }
            
            delegate2(const delegate2< Ret, PT1, PT2 >& cp) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(cp.m_method),
                m_target(cp.m_target)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("copied delegate");
            }
            
            delegate2(function_ptr fnptr) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(reinterpret_cast<functor>(fnptr)),
                m_target(OMNI_NULL)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate with function pointer");
            }
            
            delegate2(void* obj, functor mthd) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(mthd),
                m_target(obj)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate with target and method");
            }
            
            ~delegate2() OMNI_DTOR_THROWS
            {
                OMNI_TRY_FW
                this->unbind();
                OMNI_SAFE_DGATE_DTOR_FW
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            inline void bond(function_ptr fnptr)
            {
                this->_bind(OMNI_NULL, reinterpret_cast<functor>(fnptr));
            }
            
            template < ret_t (*fnptr)(p1_t, p2_t) >
            inline void bond()
            {
                this->_bind(OMNI_NULL, &_anon_param_fn<fnptr>);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            inline void bond(T& obj)
            {
                this->_bind(static_cast<void*>(&obj), &_member_param_fn<T, fnptr>);
            }

            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            inline void bond(const T& obj)
            {
                this->_bind(static_cast<void*>(const_cast<T*>(&obj)), &_member_param_fn<T, fnptr>);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            inline void bond(const T *const obj)
            {
                this->_bind(static_cast<void*>(const_cast<T *const>(obj)), &_member_param_fn<T, fnptr>);
            }

            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            inline void bond_const(const T& obj)
            {
                this->_bind(static_cast<void*>(const_cast<T*>(&obj)), &_member_param_fn_const<T, fnptr>);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            inline void bond_const(const T *const obj)
            {
                this->_bind(static_cast<void*>(const_cast<T *const>(obj)), &_member_param_fn_const<T, fnptr>);
            }
            
            template < ret_t (*fnptr)(p1_t, p2_t) >
            static delegate2 bind()
            {
                return delegate2(OMNI_NULL, &_anon_param_fn<fnptr>);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            static delegate2 bind(T& obj)
            {
                return delegate2(&obj, &_member_param_fn<T, fnptr>);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            static delegate2 bind(const T& obj)
            {
                return delegate2(const_cast<T *const>(&obj), &_member_param_fn<T, fnptr>);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            static delegate2 bind(const T *const obj)
            {
                return delegate2(const_cast<T *const>(obj), &_member_param_fn<T, fnptr>);
            }

            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            static delegate2 bind_const(const T& obj)
            {
                return delegate2(const_cast<T *const>(&obj), &_member_param_fn_const<T, fnptr>);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            static delegate2 bind_const(const T *const obj)
            {
                return delegate2(const_cast<T *const>(obj), &_member_param_fn_const<T, fnptr>);
            }
            
            bool is_bound() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL);
            }
            
            bool is_member_bound() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL && this->m_target != OMNI_NULL);
            }
            
            ret_t invoke(p1_t val1, p2_t val2) const
            {
                #if defined(OMNI_SAFE_DELEGATES)
                    omni::sync::mutex_lock(this->m_mtx);
                    if (this->m_method != OMNI_NULL) {
                        if (this->m_target == OMNI_NULL) {
                            function_ptr fp = reinterpret_cast<function_ptr>(this->m_method);
                            OMNI_D5_FW("invoking function");
                            omni::sync::mutex_unlock(this->m_mtx);
                            return (*fp)(val1, val2);
                        } else {
                            functor m = this->m_method;
                            void* t = this->m_target;
                            OMNI_D5_FW("invoking function");
                            omni::sync::mutex_unlock(this->m_mtx);
                            return (*m)(t, val1, val2);
                        }
                    }
                    omni::sync::mutex_unlock(this->m_mtx);
                #else
                    OMNI_D5_FW("invoking function");
                    return (this->m_target == OMNI_NULL ?
                            (*reinterpret_cast<function_ptr>(this->m_method))(val1, val2) :
                            (*this->m_method)(this->m_target, val1, val2));
                #endif
                OMNI_ERR_RETV_FW(OMNI_INVALID_DELEGATE_INVOKE_STR, omni::exceptions::invalid_delegate_invoke(), ret_t())
            }
            
            ret_t invoke_direct(p1_t val1, p2_t val2) const
            {
                OMNI_D5_FW("invoking function");
                return (this->m_target == OMNI_NULL ?
                        (*reinterpret_cast<function_ptr>(this->m_method))(val1, val2) :
                        (*this->m_method)(this->m_target, val1, val2));
            }
            
            omni::invoke_t invoke_type() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                if (this->m_method == OMNI_NULL) { return omni::invoke_type::NONE; }
                return (this->m_target == OMNI_NULL ?
                        omni::invoke_type::ANONYMOUS :
                        omni::invoke_type::MEMBER_FUNC);
            }
            
            const functor method() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return this->m_method;
            }
            
            const function_ptr function() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return ((this->m_target == OMNI_NULL) ?
                        reinterpret_cast<function_ptr>(this->m_method) : OMNI_NULL);
            }
            
            void swap(delegate2< Ret, PT1, PT2 >& d)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                #if defined(OMNI_SAFE_DELEGATES)
                    omni::sync::mutex_lock(d.m_mtx);
                #endif
                std::swap(this->m_target, d.m_target);
                std::swap(this->m_method, d.m_method);
                #if defined(OMNI_SAFE_DELEGATES)
                    omni::sync::mutex_unlock(d.m_mtx);
                #endif
            }
            
            void* target() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return this->m_target;
            }
            
            inline void unbind()
            {
                this->_bind(OMNI_NULL, OMNI_NULL);
                OMNI_D4_FW("instance unbound");
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            inline void unsafe_set_method()
            {
                this->_set_method(&_member_param_fn<T, fnptr>);
            }

            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            inline void unsafe_set_method_const()
            {
                this->_set_method(&_member_param_fn_const<T, fnptr>);
            }
            
            template < class T >
            inline void unsafe_set_target(T& obj)
            {
                this->_set_target(&obj);
            }

            template < class T >
            inline void unsafe_set_target(const T& obj)
            {
                this->_set_target(const_cast<T *const>(&obj));
            }
            
            template < class T >
            inline void unsafe_set_target(const T *const obj)
            {
                this->_set_target(const_cast<T *const>(obj));
            }
            
            bool valid() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL);
            }
            
            inline ret_t operator()(p1_t val1, p2_t val2) const
            {
                return this->invoke(val1, val2);
            }
            
            inline operator bool() const
            {
                return this->valid();
            }
            
            inline bool operator!() const
            {
                return !(this->operator bool());
            }
            
            delegate2< Ret, PT1, PT2 >& operator=(const delegate2< Ret, PT1, PT2 >& d)
            {
                if (this != &d) {
                    #if defined(OMNI_SAFE_DELEGATES)
                        omni::sync::mutex_lock(d.m_mtx);
                    #endif
                    this->_bind(d.m_target, d.m_method);
                    #if defined(OMNI_SAFE_DELEGATES)
                        omni::sync::mutex_unlock(d.m_mtx);
                    #endif
                }
                return *this;
            }
            
            delegate2< Ret, PT1, PT2 >& operator=(function_ptr fnptr)
            {
                this->_bind(OMNI_NULL, reinterpret_cast<functor>(fnptr));
                return *this;
            }
            
            bool operator==(const delegate2< Ret, PT1, PT2 >& d) const
            {
                if (this == &d) { return true; }
                OMNI_SAFE_DGATE_ALOCK_FW
                return
                (
                    this->m_target == d.m_target &&
                    this->m_method == d.m_method
                );
            }
            
            bool operator!=(const delegate2< Ret, PT1, PT2 >& d) const
            {
                return !(*this == d);
            }
            
        private:
            OMNI_SAFE_DGATE_MTX_FW
            functor m_method;
            void* m_target;
            
            void _bind(void* obj, functor mthd)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                OMNI_D5_FW("binding target and method");
                this->m_target = obj;
                this->m_method = mthd;
            }
            
            void _set_target(void* obj)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                OMNI_D5_FW("binding target");
                this->m_target = obj;
            }
            
            void _set_method(functor mthd)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                OMNI_D5_FW("binding function");
                this->m_method = mthd;
            }
            
            template < ret_t (*fnptr)(p1_t, p2_t) >
            static ret_t _anon_param_fn(void*, p1_t val1, p2_t val2)
            {
                return (fnptr)(val1, val2);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            static ret_t _member_param_fn(void* obj, p1_t val1, p2_t val2)
            {
                return ((static_cast<T*>(obj))->*(fnptr))(val1, val2);
            }
            
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            static ret_t _member_param_fn_const(void* obj, p1_t val1, p2_t val2)
            {
                return ((static_cast<T*>(obj))->*(fnptr))(val1, val2);
            }
    };
    
    typedef omni::delegate2<void, void*, void*> callback2;
    
    template < typename Ret, typename PT1, typename PT2 >
    class event2
    {
        public:
            typedef Ret ret_t;
            typedef omni::delegate2< Ret, PT1, PT2 > delegate_t;
            typedef typename omni_sequence_t< omni::delegate2< Ret, PT1, PT2 > > container_t;
            typedef typename omni_sequence_t< omni::delegate2< Ret, PT1, PT2 > >::iterator iterator_t;
            typedef typename omni_sequence_t< omni::delegate2< Ret, PT1, PT2 > >::const_iterator const_iterator_t;
            typedef typename std::reverse_iterator< iterator_t > reverse_iterator_t;
            typedef typename std::reverse_iterator< const_iterator_t > const_reverse_iterator_t;
            typedef PT1 p1_t;
            typedef PT2 p2_t;


            event2() : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list()
            {
                OMNI_SAFE_EVENT_INIT_FW
                OMNI_D5_FW("created event");
            }
            
            event2(const event2< Ret, PT1, PT2 >& cp) : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list(cp.m_list)
            {
                OMNI_SAFE_EVENT_INIT_FW
                OMNI_D5_FW("created event");
            }
            
            event2(const omni::delegate2< Ret, PT1, PT2 >& d) : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list()
            {
                OMNI_SAFE_EVENT_INIT_FW
                this->attach(d);
                OMNI_D5_FW("created event");
            }

            ~event2()
            {
                OMNI_TRY_FW
                this->clear();
                OMNI_SAFE_EVENT_DTOR_FW
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }
            
            void attach(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                /* DEV_NOTE: do not check if d does not have a valid function reference
                since on invoke d would fail if it did not have a valid fnptr */
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("attaching delegate");
                this->m_list.push_back(d);
            }
            
            template < class InputIterator >
            void attach(InputIterator begin, InputIterator end)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("attaching iterators");
                while (begin != end) {
                    this->m_list.push_back(*begin);
                    ++begin;
                }
            }
            
            void attach(const event2< Ret, PT1, PT2 >& e)
            {
                if (this != &e) {
                    #if defined(OMNI_SAFE_EVENTS)
                        omni::sync::scoped_lock<omni::sync::mutex_t> eauto_mtx(&e.m_mtx);
                    #endif
                    OMNI_D5_FW("attaching event list");
                    this->attach(e.m_list.begin(), e.m_list.end());
                }
            }
            
            template < ret_t (*fnptr)(PT1, PT2) >
            void attach()
            {
                this->attach( fnptr );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void attach(T& obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void attach(const T& obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void attach(const T *const obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            void attach_const(const T& obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            void attach_const(const T *const obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            void clear()
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("clearing list");
                // clear the list container, calling the items destructors
                this->m_list.clear();
            }
            
            bool contains(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return (this->_find(d) != this->m_list.end());
            }
            
            template < ret_t (*fnptr)(PT1, PT2) >
            bool contains()
            {
                return this->contains( fnptr );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            bool contains(T& obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            bool contains(const T& obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            bool contains(const T *const obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            bool contains_const(const T& obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            bool contains_const(const T *const obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            void detach(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                this->_rem(d, false);
            }
            
            template < class InputIterator >
            void detach(InputIterator begin, InputIterator end)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("detaching iterators");
                while (begin != end) {
                    this->_rem(*begin, false);
                    ++begin;
                }
            }
            
            void detach(const event2< Ret, PT1, PT2 >& e)
            {
                if (this != &e) {
                    #if defined(OMNI_SAFE_EVENTS)
                        omni::sync::scoped_lock<omni::sync::mutex_t> eauto_mtx(&e.m_mtx);
                    #endif
                    OMNI_D5_FW("detaching event list");
                    this->detach(e.m_list.begin(), e.m_list.end());
                }
            }
            
            void detach_all(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                this->_rem(d, true);
            }
            
            template < class InputIterator >
            void detach_all(InputIterator begin, InputIterator end)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("detaching iterators");
                while (begin != end) {
                    this->_rem(*begin, true);
                    ++begin;
                }
            }

            void detach_all(const event2< Ret, PT1, PT2 >& e)
            {
                if (this != &e) {
                    OMNI_SAFE_EVENT_ALOCK_FW
                    #if defined(OMNI_SAFE_EVENTS)
                        omni::sync::scoped_lock<omni::sync::mutex_t> eauto_mtx(&e.m_mtx);
                    #endif
                    OMNI_D5_FW("detaching event list");
                    for (iterator_t it = e.m_list.begin(); it != e.m_list.end(); ++it) {  
                        this->_rem(*it, true);
                    }
                }
            }
            
            template < ret_t (*fnptr)(PT1, PT2) >
            void detach()
            {
                this->detach( fnptr );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void detach(T& obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void detach(const T& obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void detach(const T *const obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            void detach_const(const T& obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            void detach_const(const T *const obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            bool empty() const
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return this->m_list.empty();
            }
            
            container_t invocation_list() const
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return this->m_list;
            }
            
            ret_t invoke(p1_t val1, p2_t val2) const
            {
                OMNI_SAFE_EVENT_LOCK_FW
                OMNI_D5_FW("invoking attached delegates");
                const_iterator_t cur = this->m_list.begin();
                const_iterator_t tmp;
                while (cur != this->m_list.end()) {
                    tmp = cur;
                    if ((++tmp) == this->m_list.end()) {
                        OMNI_SAFE_EVENT_UNLOCK_FW
                        return cur->invoke(val1, val2);
                    }
                    OMNI_SAFE_EVENT_UNLOCK_FW
                    cur->invoke(val1, val2);
                    OMNI_SAFE_EVENT_LOCK_FW
                    if (++cur == this->m_list.end()) { break; }
                }
                OMNI_SAFE_EVENT_UNLOCK_FW
                OMNI_ERR_RETV_FW(OMNI_INVALID_DELEGATE_INVOKE_STR, omni::exceptions::invalid_delegate_invoke(), ret_t())
            }
            
            ret_t invoke_direct(p1_t val1, p2_t val2) const
            {
                OMNI_SAFE_EVENT_LOCK_FW
                OMNI_D5_FW("invoking attached delegates direct");
                const_iterator_t cur = this->m_list.begin();
                const_iterator_t tmp;
                while (cur != this->m_list.end()) {
                    tmp = cur;
                    if ((++tmp) == this->m_list.end()) {
                        OMNI_SAFE_EVENT_UNLOCK_FW
                        return cur->invoke_direct(val1, val2);
                    }
                    OMNI_SAFE_EVENT_UNLOCK_FW
                    cur->invoke_direct(val1, val2);
                    OMNI_SAFE_EVENT_LOCK_FW
                    if (++cur == this->m_list.end()) { break; }
                }
                OMNI_SAFE_EVENT_UNLOCK_FW
                OMNI_ERR_RETV_FW(OMNI_INVALID_DELEGATE_INVOKE_STR, omni::exceptions::invalid_delegate_invoke(), ret_t())
            }
            
            void swap(event2< Ret, PT1, PT2 >& e)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                #if defined(OMNI_SAFE_EVENTS)
                    omni::sync::scoped_lock<omni::sync::mutex_t> eauto_mtx(&e.m_mtx);
                #endif
                std::swap(this->m_list, e.m_list);
            }
            
            ret_t operator()(p1_t val1, p2_t val2) const
            {
                return this->invoke(val1, val2);
            }
            
            operator bool() const
            {
                return !this->empty();
            }
            
            bool operator!() const
            {
                return (!operator bool());
            }

            event2< Ret, PT1, PT2 >& operator=(const event2< Ret, PT1, PT2 >& e)
            {
                if (this != &e) {
                    OMNI_SAFE_EVENT_ALOCK_FW
                    #if defined(OMNI_SAFE_EVENTS)
                        omni::sync::scoped_lock<omni::sync::mutex_t> eauto_mtx(&e.m_mtx);
                    #endif
                    OMNI_D5_FW("clearing and assigning list");
                    this->m_list.clear();
                    this->m_list = e.m_list;
                }
                return *this;
            }
            
            omni::delegate2< Ret, PT1, PT2 >& operator[](std::size_t idx)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                if (this->m_list.empty() || (idx > (this->m_list.size() - 1))) {
                    OMNI_ERR_RETV_FW("Index out of range", omni::exceptions::index_out_of_range(), NULL)
                }
                return *(this->m_list[idx]);
            }
            
            event2< Ret, PT1, PT2 >& operator+=(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                this->attach(d);
                return *this;
            }
            
            event2< Ret, PT1, PT2 >& operator+=(const event2< Ret, PT1, PT2 >& e)
            {
                this->attach(e);
                return *this;
            }
            
            event2< Ret, PT1, PT2 >& operator-=(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                this->detach(d);
                return *this;
            }
            
            event2< Ret, PT1, PT2 >& operator-=(const event2< Ret, PT1, PT2 >& e)
            {
                this->detach(e);
                return *this;
            }
            
            event2< Ret, PT1, PT2 > operator+(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                event2< Ret, PT1, PT2 > ret(*this);
                ret.attach(d);
                return ret;
            }
            
            event2< Ret, PT1, PT2 > operator+(const event2< Ret, PT1, PT2 >& e)
            {
                event2< Ret, PT1, PT2 > ret(*this);
                ret.attach(e);
                return ret;
            }
            
            event2< Ret, PT1, PT2 > operator-(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                event2< Ret, PT1, PT2 > ret(*this);
                ret.detach(d);
                return ret;
            }
            
            event2< Ret, PT1, PT2 > operator-(const event2< Ret, PT1, PT2 >& e)
            {
                event2< Ret, PT1, PT2 > ret(*this);
                ret.detach(e);
                return ret;
            }
            
            bool operator==(const event2< Ret, PT1, PT2 >& e) const
            {
                if (this == &e) { return true; }
                OMNI_SAFE_EVENT_ALOCK_FW
                #if defined(OMNI_SAFE_EVENTS)
                    omni::sync::scoped_lock<omni::sync::mutex_t> eauto_mtx(&e.m_mtx);
                #endif
                bool ret = (e.m_list.size() == this->m_list.size());
                if (ret) {
                    const_iterator_t a = this->m_list.begin();
                    const_iterator_t b = e.m_list.begin();
                    while ((a != this->m_list.end()) && (b != e.m_list.end())) {
                        if (*a != *b) { ret = false; break; }
                        ++a; ++b;
                    }
                }
                return ret;
            }
            
            bool operator!=(const event2< Ret, PT1, PT2 >& e) const
            {
                return !(*this == e);
            }
            
        private:
            OMNI_SAFE_EVENT_MTX_FW
            container_t m_list;

            iterator_t _find(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                // do not use any locks here as calling code does the lock
                if (this->m_list.empty()) { return this->m_list.end(); }
                iterator_t itr = this->m_list.end();
                while (itr != this->m_list.begin()) {
                    if (*(--itr) == d) { return itr; }
                }
                return this->m_list.end();
            }
            
            void _rem(const omni::delegate2< Ret, PT1, PT2 >& d, bool all)
            {
                if (!this->m_list.empty()) {
                    iterator_t itr = this->m_list.end();
                    while (itr != this->m_list.begin()) {
                        if (*(--itr) == d) { 
                            OMNI_D5_FW("detaching delegate");
                            itr = this->m_list.erase(itr);
                            if (!all) { break; }
                        }
                    }
                }
            }
    };
    
    typedef omni::event2<void, void*, void*> action2;
} // namespace omni

#define OMNI_DEL2_FW(Ret, PT1, PT2) omni::delegate2<Ret, PT1, PT2>
#define OMNI_EVT2_FW(Ret, PT1, PT2) omni::event2<Ret, PT1, PT2>
#define OMNI_BIND2(Ret, PT1, PT2, Class, Function, Obj) omni::delegate2<Ret, PT1, PT2>::bind<Class, &Class::Function>(Obj)
#define OMNI_BIND2_CONST(Ret, PT1, PT2, Class, Function, Obj) omni::delegate2<Ret, PT1, PT2>::bind_const<Class, &Class::Function>(Obj)

namespace std {
    template < typename Ret, typename PT1, typename PT2 >
    inline void swap(omni::delegate2<Ret, void*, void*>& d1, omni::delegate2<Ret, void*, void*>& d2)
    {
        d1.swap(d2);
    }
    
    template < typename Ret, typename PT1, typename PT2 >
    inline void swap(omni::event2<Ret, void*, void*>& e1, omni::event2<Ret, void*, void*>& e2)
    {
        e1.swap(e2);
    }
}

#endif // OMNI_DELEGATE2_HPP
