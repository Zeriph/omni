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
    /**
     * The delegate is a powerful function pointer object that
     * encapsulates both an object instance and a method. The delegate is
     * agnostic to the type or method it encapsulates; all that matters is that
     * the method be signature compatible with the delegate. This allows for 
     * 'anonymous' invocation by users of the delegate.
     * 
     * @tparam Ret     Specifies the return type of the function the delegate is to attach to
     * @tparam PT1     Specifies the 1st parameter type passed to the function delegate
     * @tparam PT2     Specifies the 2nd parameter type passed to the function delegate
     */
    template < typename Ret, typename PT1, typename PT2 >
    class delegate2
    {
        public:
            /** Defines the return type this delegate will represent */
            typedef Ret ret_t;
            /** Defines the 1st function parameter type of this delegate */
            typedef PT1 p1_t;
            /** Defines the 2nd function parameter type of this delegate */
            typedef PT2 p2_t;

            /** Defines the functor signature this delegate will represent */
            typedef ret_t (*functor)(void* extObj, p1_t val1, p2_t val2);
            /** Defines the function pointer signature this delegate will represent */
            typedef ret_t (*function_ptr)(p1_t val1, p2_t val2);
            
            /**
             * The default constructor; constructs a default delegate
             * object with no function or member attached.
             */
            delegate2() :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(OMNI_NULL),
                m_target(OMNI_NULL)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate");
            }
            
            /**
             * The copy constructor; copies another delegates target and method.
             * The delegate being copied must be of the same signature.
             *
             * @param cp    The other delegate to copy
             */
            delegate2(const delegate2< Ret, PT1, PT2 >& cp) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(cp.m_method),
                m_target(cp.m_target)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("copied delegate");
            }
            
            /**
             * Creates a new instance from a non-member or static member function pointer.
             * 
             * @param fnptr   The function pointer to attach
             */
            delegate2(function_ptr fnptr) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(reinterpret_cast<functor>(fnptr)),
                m_target(OMNI_NULL)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate with function pointer");
            }
            
            /**
             * Creates a new instance from a functor and object.
             * 
             * @param obj   The instance of the object to use with this delegate
             * @param mthd  The functor of the object to attach to this delegate for invocation
             */
            delegate2(void* obj, functor mthd) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(mthd),
                m_target(obj)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate with target and method");
            }
            
            /** The default destructor, detaches this instance from its target and method */
            ~delegate2()
            {
                OMNI_TRY_FW
                this->unbind();
                OMNI_SAFE_DGATE_DTOR_FW
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            /**
             * Attach a static member or non-member function to this delegate.
             * 
             * @param fnptr The function taking 2 parameters to attach to the delegate
             */
            inline void bond(function_ptr fnptr)
            {
                this->_bind(OMNI_NULL, reinterpret_cast<functor>(fnptr));
            }
            
            /**
             * Attach a static member or non-member function to this delegate.
             * 
             * @tparam fnptr The function taking 2 parameters to attach to the delegate
             */
            template < ret_t (*fnptr)(p1_t, p2_t) >
            inline void bond()
            {
                this->_bind(OMNI_NULL, &_anon_param_fn<fnptr>);
            }
            
            /**
             * Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            inline void bond(T& obj)
            {
                this->_bind(static_cast<void*>(&obj), &_member_param_fn<T, fnptr>);
            }

            /**
             * Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            inline void bond(const T& obj)
            {
                this->_bind(static_cast<void*>(const_cast<T*>(&obj)), &_member_param_fn<T, fnptr>);
            }
            
            /**
             * Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            inline void bond(const T *const obj)
            {
                this->_bind(static_cast<void*>(const_cast<T *const>(obj)), &_member_param_fn<T, fnptr>);
            }

            /**
             * Attach a const member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The const function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            inline void bond_const(const T& obj)
            {
                this->_bind(static_cast<void*>(const_cast<T*>(&obj)), &_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * Attach a const member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            inline void bond_const(const T *const obj)
            {
                this->_bind(static_cast<void*>(const_cast<T *const>(obj)), &_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * Attach a static member or non-member function to this delegate.
             * 
             * @tparam fnptr The function taking 2 parameters to attach to the delegate
             */
            template < ret_t (*fnptr)(p1_t, p2_t) >
            static delegate2 bind()
            {
                return delegate2(OMNI_NULL, &_anon_param_fn<fnptr>);
            }
            
            /**
             * Attach a parametrized member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The parametrized function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            static delegate2 bind(T& obj)
            {
                return delegate2(&obj, &_member_param_fn<T, fnptr>);
            }
            
            /**
             * Attach a parametrized member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The parametrized function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            static delegate2 bind(const T& obj)
            {
                return delegate2(const_cast<T *const>(&obj), &_member_param_fn<T, fnptr>);
            }
            
            /**
             * Attach a parametrized member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The parametrized function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            static delegate2 bind(const T *const obj)
            {
                return delegate2(const_cast<T *const>(obj), &_member_param_fn<T, fnptr>);
            }

            /**
             * Attach a const parametrized member function to this delegate.
             * 
             * @tparam T           The type of class to associate with this delegate
             * @tparam fnptr       The parametrized function to attach to the delegate
             * @param obj          The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            static delegate2 bind_const(const T& obj)
            {
                return delegate2(const_cast<T *const>(&obj), &_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * Attach a parametrized member function to this delegate.
             * 
             * @tparam T           The type of class to associate with this delegate
             * @tparam fnptr       The parametrized function to attach to the delegate
             * @param obj          The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            static delegate2 bind_const(const T *const obj)
            {
                return delegate2(const_cast<T *const>(obj), &_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * Gets if this instance is bound to a method
             *
             * @return True if this instance is currently bound
             */
            bool is_bound() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL);
            }
            
            /**
             * Gets if this instance is bound to a member method
             *
             * @return True if this instance is currently bound to a target and method
             */
            bool is_member_bound() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL && this->m_target != OMNI_NULL);
            }
            
            /**
             * Invoke the function bound to this delegate instance
             * 
             * @return  This function returns whatever is returned
             *          (if anything) from the invoked function
             */
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
            
            /**
             * Invoke the function bound to this delegate instance.
             * This method does not preform any safety checks on the
             * method or object instance and directly calls the method
             * for invocation (if bound).
             * 
             * @return  This function returns whatever is returned
             *          (if anything) from the invoked function
             */
            ret_t invoke_direct(p1_t val1, p2_t val2) const
            {
                OMNI_D5_FW("invoking function");
                return (this->m_target == OMNI_NULL ?
                        (*reinterpret_cast<function_ptr>(this->m_method))(val1, val2) :
                        (*this->m_method)(this->m_target, val1, val2));
            }
            
            /**
             * Gets the invocation type this delegate represents
             * 
             * @return The delegates omni::invoke_type::enum_t 
             */
            omni::invoke_t invoke_type() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                if (this->m_method == OMNI_NULL) { return omni::invoke_type::NONE; }
                return (this->m_target == OMNI_NULL ?
                        omni::invoke_type::ANONYMOUS :
                        omni::invoke_type::MEMBER_FUNC);
            }
            
            /**
             * Gets the underlying functor called when this method is invoked.
             * 
             * @return The underlying functor method
             */
            const functor method() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return this->m_method;
            }
            
            /**
             * Gets the underlying function pointer called when this method is invoked.
             * 
             * @return The underlying function pointer, or an OMNI_NULL value if the
             * object instance is null;
             */
            const function_ptr function() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return ((this->m_target == OMNI_NULL) ?
                        reinterpret_cast<function_ptr>(this->m_method) : OMNI_NULL);
            }
            
            /**
             * Swaps the invocation method and target of 2 delegates
             */
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
            
            /**
             * Gets the underlying target (if any) used when invoking this method.
             * 
             * @return A pointer to the underlying target object (if any)
             */
            void *const target() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return this->m_target;
            }
            
            /**
             * Detaches the target and method from this instance
             */
            inline void unbind()
            {
                this->_bind(OMNI_NULL, OMNI_NULL);
                OMNI_D4_FW("instance unbound");
            }
            
            /**
             * Sets the underlying method; this method is marked unsafe
             * since it manipulates the underlying pointers. This method
             * assumes the user understands all implications with this.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            inline void unsafe_set_method()
            {
                this->_set_method(&_member_param_fn<T, fnptr>);
            }

            /**
             * Sets the underlying method; this method is marked unsafe
             * since it manipulates the underlying pointers. This method
             * assumes the user understands all implications with this.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            inline void unsafe_set_method_const()
            {
                this->_set_method(&_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * Sets the underlying target; this method is marked unsafe
             * since it manipulates the underlying pointers. This method
             * assumes the user understands all implications with this.
             */
            template < class T >
            inline void unsafe_set_target(T& obj)
            {
                this->_set_target(&obj);
            }

            /**
             * Sets the underlying target; this method is marked unsafe
             * since it manipulates the underlying pointers. This method
             * assumes the user understands all implications with this.
             */
            template < class T >
            inline void unsafe_set_target(const T& obj)
            {
                this->_set_target(const_cast<T *const>(&obj));
            }
            
            /**
             * Sets the underlying target; this method is marked unsafe
             * since it manipulates the underlying pointers. This method
             * assumes the user understands all implications with this.
             */
            template < class T >
            inline void unsafe_set_target(const T *const obj)
            {
                this->_set_target(const_cast<T *const>(obj));
            }
            
            /**
             * Checks if the current delegate instance is valid
             * 
             * @return True if the instance has a method attached, false if not
             */
            bool valid() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL);
            }
            
            /**
             * Has the same effect as calling the invoke method.
             * Overloading this operator makes it such that you can
             * use the delegate as if it were a function.
             *
             * delegate<int> d = &some_func;
             * printf("value = %d", d());
             * 
             * @return The return type specified at compile time
             */
            inline ret_t operator()(p1_t val1, p2_t val2) const
            {
                return this->invoke(val1, val2);
            }
            
            /**
             * The boolean operator allows you to check for validity as if
             * the delegate were a function pointer, example:
             * delegate<int> d;
             * if (d) { d(); } // fails check because d is not attached
             * d = &some_func;
             * if (d) { d(); } // success because d is bound
             * 
             * @return True if the delegate is attached
             */
            inline operator bool() const
            {
                return this->valid();
            }
            
            /**
             * The negated boolean () operator is used to check negation of the boolean () operator
             */
            inline bool operator!() const
            {
                return !(this->operator bool());
            }
            
            /**
             * The assignment operator is used to set the target and method
             * of another delegate to this one.
             * 
             * @param d        The right most operand which to assign to
             *
             * @return A reference to the current instance
             */
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
            
            /**
             * Allows for assignment to anonymous (non-member) functions
             * by saying = &func_name
             * 
             * @param fp   The function pointer to assign
             *
             * @return A reference to the current instance
             */
            delegate2< Ret, PT1, PT2 >& operator=(function_ptr fnptr)
            {
                this->_bind(OMNI_NULL, reinterpret_cast<functor>(fnptr));
                return *this;
            }
            
            /**
             * The equality operator test the target and method against the other
             * 
             * @param d        The right most operand which to compare to
             *
             * @return      True if the two instance are equal
             */
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
            
            /**
             * The != operator is used for comparison results (negates the == operator)
             * 
             * @param d        The right most operand which to compare to
             *
             * @return True if the instances are not equal
             */
            bool operator!=(const delegate2< Ret, PT1, PT2 >& d) const
            {
                return !(*this == d);
            }
            
        private:
            OMNI_SAFE_DGATE_MTX_FW
            /** The 2 parameter member function to be called */
            functor m_method;
            /** The instance of the object set when attaching to the delegate */
            void* m_target;
            
            /**
             * The internal binding function that sets the underlying method and target
             * 
             * @param obj  The target to set
             * @param mthd The method to set
             * @param type The type to set
             */
            void _bind(void* obj, functor mthd)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                OMNI_D5_FW("binding target and method");
                this->m_target = obj;
                this->m_method = mthd;
            }
            
            /**
             * Sets the underlying target object
             */
            void _set_target(void* obj)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                OMNI_D5_FW("binding target");
                this->m_target = obj;
            }
            
            /**
             * Sets the underlying target function
             */
            void _set_method(functor mthd)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                OMNI_D5_FW("binding function");
                this->m_method = mthd;
            }
            
            /**
             * Gets the parametrized non member (static/anonymous) function to use
             * 
             * @tparam fnptr         The method to assign
             */
            template < ret_t (*fnptr)(p1_t, p2_t) >
            static ret_t _anon_param_fn(void*, p1_t val1, p2_t val2)
            {
                return (fnptr)(val1, val2);
            }
            
            /**
             * Get the parametrized member function to use
             * 
             * @tparam T           The class type
             * @tparam fnptr       The parametrized member method to use
             * @param obj          The instance object associated with the member method
             * 
             * @return             The functor
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) >
            static ret_t _member_param_fn(void* obj, p1_t val1, p2_t val2)
            {
                return ((static_cast<T*>(obj))->*(fnptr))(val1, val2);
            }
            
            /**
             * Get the const parametrized member function to use
             * 
             * @tparam T           The class type
             * @tparam fnptr       The parametrized member method to use
             * @param obj          The instance object associated with the member method
             * 
             * @return             The functor
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t) const >
            static ret_t _member_param_fn_const(void* obj, p1_t val1, p2_t val2)
            {
                return ((static_cast<T*>(obj))->*(fnptr))(val1, val2);
            }
    };
    
    /** A generic delegate that has 2 parameters and does not return a value. */
    typedef omni::delegate2<void, void*, void*> callback2;
    
    /**
     * The templated event allows client code to attach multiple delegates
     * and invoke them, providing notification to attached code (i.e. event handlers).
     * 
     * Invoking an event will invoke each attached handler (delegate) in the order
     * they have been attached.
     * 
     * @tparam Ret      Specifies the return type of the delegates to be attached
     * @tparam 2     Specifies the parameter types passed to the delegate
     */
    template < typename Ret, typename PT1, typename PT2 >
    class event2
    {
        public:
            /** Defines the return type this event will represent */
            typedef Ret ret_t;
            /** Defines the delegate signature this event represents */
            typedef omni::delegate2< Ret, PT1, PT2 > delegate_t;
            /** Defines the container type used by this event class */
            typedef typename omni_sequence_t< omni::delegate2< Ret, PT1, PT2 > > container_t;
            /** Defines an iterator type to the underlying types */
            typedef typename omni_sequence_t< omni::delegate2< Ret, PT1, PT2 > >::iterator iterator_t;
            /** Defines a const iterator type to the underlying types */
            typedef typename omni_sequence_t< omni::delegate2< Ret, PT1, PT2 > >::const_iterator const_iterator_t;
            /** Defines a reverse iterator type to the underlying types */
            typedef typename std::reverse_iterator< iterator_t > reverse_iterator_t;
            /** Defines a const reverse iterator type to the underlying types */
            typedef typename std::reverse_iterator< const_iterator_t > const_reverse_iterator_t;
            /** Defines the 1st function parameter type of this delegate */
            typedef PT1 p1_t;
            /** Defines the 2nd function parameter type of this delegate */
            typedef PT2 p2_t;


            /** The default constructor */
            event2() : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list()
            {
                OMNI_SAFE_EVENT_INIT_FW
                OMNI_D5_FW("created event");
            }
            
            /**
             * The copy constructor copies the elements from the
             * event passed in.
             *
             * @param cp    The event to copy
             */
            event2(const event2< Ret, PT1, PT2 >& cp) : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list(cp.m_list)
            {
                OMNI_SAFE_EVENT_INIT_FW
                OMNI_D5_FW("created event");
            }
            
            /**
             * Creates an event with a signature compatible delegate attached
             *
             * @param d     The signature compatible delegate to add to the invocation list
             */
            event2(const omni::delegate2< Ret, PT1, PT2 >& d) : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list()
            {
                OMNI_SAFE_EVENT_INIT_FW
                this->attach(d);
                OMNI_D5_FW("created event");
            }

            /**
             * The default destructor; clears the underlying list,
             * calling the destructor for each attached delegate
             */
            ~event2()
            {
                OMNI_TRY_FW
                this->clear();
                OMNI_SAFE_EVENT_DTOR_FW
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }
            
            /**
             * Add (attach) a member delegate to this event instance
             * 
             * @param d        The member delegate to attach
             */
            void attach(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                /* DEV_NOTE: don't check if 'd' doesn't have a valid function reference
                since on invoke 'd' would fail if it didn't have a valid fnptr */
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("attaching delegate");
                this->m_list.push_back(d);
            }
            
            /**
             * Add (attach) a range of delegates to this event instance
             * 
             * @param begin     The input iterator pointing to the initial position in the sequence to add
             * @param end       The input iterator pointing to the last position in the sequence to add
             */
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
            
            /**
             * Add (attach) another events invocation list to this instance
             *    
             * @param e        The other event to add invocation list
             */
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
            
            /**
             * Attach a an anonymous/non-member or static member function to this delegate.
             * 
             * @tparam fnptr         The function to attach to the delegate
             */
            template < ret_t (*fnptr)(PT1, PT2) >
            void attach()
            {
                this->attach( fnptr );
            }
            
            /**
             * Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void attach(T& obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void attach(const T& obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void attach(const T *const obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Attach a const member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            void attach_const(const T& obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * Attach a const member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            void attach_const(const T *const obj)
            {
                this->attach( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * Clears the underlying invocation list
             */
            void clear()
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("clearing list");
                // clear the list container, calling the items destructors
                this->m_list.clear();
            }
            
            /**
             * Tests if a specified member delegate is in this event instance.
             * 
             * @param d        The member delegate to search for
             * 
             * @return True if the delegate is found, false otherwise
             */
            bool contains(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return (this->_find(d) != this->m_list.end());
            }
            
            /**
             * Tests if a specified member delegate is in this event instance.
             * 
             * @tparam fnptr         The function to attach to the delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < ret_t (*fnptr)(PT1, PT2) >
            bool contains()
            {
                return this->contains( fnptr );
            }
            
            /**
             * Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            bool contains(T& obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            bool contains(const T& obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            bool contains(const T *const obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            bool contains_const(const T& obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            bool contains_const(const T *const obj)
            {
                return this->contains( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * Detach the last attached delegate from this event instance that matches
             * 
             * @param d        The member delegate to detach
             */
            void detach(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                this->_rem(d, false);
            }
            
            /**
             * Detach a range of delegates from this event instance
             * 
             * @param begin     The input iterator pointing to the initial position in the sequence to remove
             * @param end       The input iterator pointing to the last position in the sequence to remove
             */
            template < class InputIterator >
            void detach(InputIterator begin, InputIterator end)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("detaching iterators");
                iterator_t found = this->m_list.end();
                while (begin != end) {
                    this->_rem(*begin, false);
                    ++begin;
                }
            }
            
            /**
             * Detaches another events invocation list from this instance
             * 
             * @param e        The event to detach invocation list of
             */
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
            
            /**
             * Detaches all delegates from this event instance that match
             * 
             * @param d        The member delegate to detach
             */
            void detach_all(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                this->_rem(d, true);
            }
            
            /**
             * Detaches another events invocation list from this instance
             * 
             * @param e        The event to detach invocation list of
             */
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
            
            /**
             * Detach a range of delegates from this event instance
             * 
             * @param begin     The input iterator pointing to the initial position in the sequence to remove
             * @param end       The input iterator pointing to the last position in the sequence to remove
             */
            template < class InputIterator >
            void detach_all(InputIterator begin, InputIterator end)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("detaching iterators");
                iterator_t found = this->m_list.end();
                while (begin != end) {
                    this->_rem(*begin, true);
                    ++begin;
                }
            }
            
            /**
             * Detach an anonymous/non-member or static member function from this event.
             * 
             * @tparam fnptr         The function to detach
             */
            template < ret_t (*fnptr)(PT1, PT2) >
            void detach()
            {
                this->detach( fnptr );
            }
            
            /**
             * Detach a member function from this event.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void detach(T& obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Detach a member function from this event.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void detach(const T& obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Detach a member function from this event.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2) >
            void detach(const T *const obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * Detach a const member function from this event.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            void detach_const(const T& obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * Detach a const member function from this event.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2) const >
            void detach_const(const T *const obj)
            {
                this->detach( omni::delegate2< Ret, PT1, PT2 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * Checks if the current event instance has any attached methods
             * 
             * @return True if the instance has a method or methods attached, false if not
             */
            bool empty() const
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return this->m_list.empty();
            }
            
            /**
             * Gets the invocation list used to call the delegate objects on event invocation
             * 
             * @return The underlying container variable
             */
            container_t invocation_list() const
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return this->m_list;
            }
            
            /**
             * Invoke the functions bound to this event instance
             * 
             * @return The return type specified at compile time
             */
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
            
            /**
             * Calls the functions bound to this event instance in a non-safe manner.
             * delegate::invoke_direct does not perform certain checks.
             * 
             * @return The return type specified at compile time
             */
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
            
            /**
             * The () operator can be used to call the functions bound to this event instance
             * 
             * @return The return type specified at compile time
             */
            ret_t operator()(p1_t val1, p2_t val2) const
            {
                return this->invoke(val1, val2);
            }
            
            /**
             * The boolean () operator can be used to check if this delegate is valid (has a valid function assigned)
             */
            operator bool() const
            {
                return !this->empty();
            }
            
            /**
             * The negated boolean () operator is used to check negation of the boolean () operator
             */
            bool operator!() const
            {
                return (!operator bool());
            }

            /**
             * The = operator is used to assign one event invocation to another
             * 
             * @param e        The right most operand event to assign
             */
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
            
            /**
             * The [int] operator can be used to access a specific delegate in the
             * invocation list directly.
             * 
             * @return A reference to the delegate instance at the specified index
             */
            omni::delegate2< Ret, PT1, PT2 >& operator[](std::size_t idx)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                if (this->m_list.empty() || (idx > (this->m_list.size() - 1))) {
                    OMNI_ERR_RETV_FW("Index out of range", omni::exceptions::index_out_of_range(), NULL)
                }
                return *(this->m_list[idx]);
            }
            
            /**
             * The += operator is used to add delegates to this event instance
             * 
             * @param d        The right most operand delegate to add
             */
            event2< Ret, PT1, PT2 >& operator+=(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                this->attach(d);
                return *this;
            }
            
            /**
             * The += operator is used to add delegates to this event instance
             * 
             * @param e        The right most operand event to add
             */
            event2< Ret, PT1, PT2 >& operator+=(const event2< Ret, PT1, PT2 >& e)
            {
                this->attach(e);
                return *this;
            }
            
            /**
             * The -= operator is used to remove delegates from this event instance
             * 
             * @param d        The right most operand delegate to remove
             */
            event2< Ret, PT1, PT2 >& operator-=(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                this->detach(d);
                return *this;
            }
            
            /**
             * The -= operator is used to remove delegates from this event instance
             * 
             * @param e        The right most operand event to remove
             */
            event2< Ret, PT1, PT2 >& operator-=(const event2< Ret, PT1, PT2 >& e)
            {
                this->detach(e);
                return *this;
            }
            
            /**
             * The + operator adds delegate to the event instance and returns the combined list.
             * 
             * @param d        The right most operand delegate to add
             */
            event2< Ret, PT1, PT2 > operator+(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                event2< Ret, PT1, PT2 > ret(*this);
                ret.attach(d);
                return ret;
            }
            
            /**
             * The + operator adds the event instance to another and returns the combined list.
             * 
             * @param e        The right most operand event to add
             */
            event2< Ret, PT1, PT2 > operator+(const event2< Ret, PT1, PT2 >& e)
            {
                event2< Ret, PT1, PT2 > ret(*this);
                ret.attach(e);
                return ret;
            }
            
            /**
             * The - operator removes a delegate from the event instance and returns the new list.
             * 
             * @param d        The right most operand delegate to remove
             */
            event2< Ret, PT1, PT2 > operator-(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                event2< Ret, PT1, PT2 > ret(*this);
                ret.detach(d);
                return ret;
            }
            
            /**
             * The - operator removes an event instance from another and returns the new list.
             * 
             * @param e        The right most operand event to remove
             */
            event2< Ret, PT1, PT2 > operator-(const event2< Ret, PT1, PT2 >& e)
            {
                event2< Ret, PT1, PT2 > ret(*this);
                ret.detach(e);
                return ret;
            }
            
            /**
             * The == operator is used for comparison results
             * 
             * @param d        The right most operand which to compare to
             */
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
            
            /**
             * The != operator is used for comparison results (negates the == operator)
             * 
             * @param d        The right most operand which to compare to
             */
            bool operator!=(const event2< Ret, PT1, PT2 >& e) const
            {
                return !(*this == e);
            }
            
        private:
            OMNI_SAFE_EVENT_MTX_FW
            /** The collection of member methods */
            container_t m_list;

            /**
             * Find a specified member delegate in this event instance.
             * 
             * @param d        The member delegate to search for
             * 
             * @return An iterator to the found delegate, list.end() if not found
             */
            iterator_t _find(const omni::delegate2< Ret, PT1, PT2 >& d)
            {
                // don't use any locks here as calling code does the lock
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
    
    /** A generic event that has 2 parameters and does not return a value. */
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
