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
#if !defined(OMNI_DELEGATE12_HPP)
#define OMNI_DELEGATE12_HPP 1
#include <omni/defs/delegate_def.hpp>
#include <omni/types/invoke_t.hpp>

namespace omni {
    /**
     * @brief The delegate is a powerful function pointer object
     * that encapsulates both an object instance and a method.
     * 
     * @details The delegate is agnostic to the type or method it encapsulates;
     * all that matters is that the method be signature compatible with the delegate.
     * This allows for anonymous invocation by users of the delegate.
     * 
     * @tparam Ret     Specifies the return type of the function the delegate is to attach to
     * @tparam PT1     Specifies the 1st parameter type passed to the function delegate
     * @tparam PT2     Specifies the 2nd parameter type passed to the function delegate
     * @tparam PT3     Specifies the 3rd parameter type passed to the function delegate
     * @tparam PT4     Specifies the 4th parameter type passed to the function delegate
     * @tparam PT5     Specifies the 5th parameter type passed to the function delegate
     * @tparam PT6     Specifies the 6th parameter type passed to the function delegate
     * @tparam PT7     Specifies the 7th parameter type passed to the function delegate
     * @tparam PT8     Specifies the 8th parameter type passed to the function delegate
     * @tparam PT9     Specifies the 9th parameter type passed to the function delegate
     * @tparam PT10     Specifies the 10th parameter type passed to the function delegate
     * @tparam PT11     Specifies the 11th parameter type passed to the function delegate
     * @tparam PT12     Specifies the 12th parameter type passed to the function delegate
     */
    template < typename Ret, typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6, typename PT7, typename PT8, typename PT9, typename PT10, typename PT11, typename PT12 >
    class delegate12
    {
        public:
            /** Defines the return type this delegate will represent */
            typedef Ret ret_t;
            /** Defines the 1st function parameter type of this delegate */
            typedef PT1 p1_t;
            /** Defines the 2nd function parameter type of this delegate */
            typedef PT2 p2_t;
            /** Defines the 3rd function parameter type of this delegate */
            typedef PT3 p3_t;
            /** Defines the 4th function parameter type of this delegate */
            typedef PT4 p4_t;
            /** Defines the 5th function parameter type of this delegate */
            typedef PT5 p5_t;
            /** Defines the 6th function parameter type of this delegate */
            typedef PT6 p6_t;
            /** Defines the 7th function parameter type of this delegate */
            typedef PT7 p7_t;
            /** Defines the 8th function parameter type of this delegate */
            typedef PT8 p8_t;
            /** Defines the 9th function parameter type of this delegate */
            typedef PT9 p9_t;
            /** Defines the 10th function parameter type of this delegate */
            typedef PT10 p10_t;
            /** Defines the 11th function parameter type of this delegate */
            typedef PT11 p11_t;
            /** Defines the 12th function parameter type of this delegate */
            typedef PT12 p12_t;

            /** Defines the functor signature this delegate will represent */
            typedef ret_t (*functor)(void* extObj, p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12);
            /** Defines the function pointer signature this delegate will represent */
            typedef ret_t (*function_ptr)(p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12);
            
            /**
             * @brief The default constructor; constructs a default delegate
             * object with no function or member attached.
             */
            delegate12() :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(OMNI_NULL_PTR),
                m_target(OMNI_NULL_PTR)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate");
            }
            
            /**
             * @brief The copy constructor; copies another delegates target and method.
             * The delegate being copied must be of the same signature.
             *
             * @param cp    The other delegate to copy
             */
            delegate12(const delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& cp) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(cp.m_method),
                m_target(cp.m_target)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("copied delegate");
            }
            
            /**
             * @brief Creates a new instance from a non-member or static member function pointer.
             * 
             * @param fnptr   The function pointer to attach
             */
            delegate12(function_ptr fnptr) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(reinterpret_cast<functor>(fnptr)),
                m_target(OMNI_NULL_PTR)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate with function pointer");
            }
            
            /**
             * @brief Creates a new instance from a functor and object.
             * 
             * @param obj   The instance of the object to use with this delegate
             * @param mthd  The omni::delegate12::functor of the object to attach
             *              to this delegate for invocation
             */
            delegate12(void* obj, functor mthd) :
                OMNI_SAFE_DGATE_MILST_FW
                m_method(mthd),
                m_target(obj)
            {
                OMNI_SAFE_DGATE_INIT_FW
                OMNI_D5_FW("created delegate with target and method");
            }
            
            /**
             * @brief The destructor detaches this instance from its target and method
             * 
             * @warning If the function is still running when this delegate instance is
             * being destroyed, the function will continue to live in an undefined state.
             * The function will not stop upon destruction and will likely have a corrupted
             * stack pointer.
             */
            ~delegate12() OMNI_DTOR_THROWS
            {
                OMNI_TRY_FW
                this->unbind();
                OMNI_SAFE_DGATE_DTOR_FW
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            /**
             * @brief Attach a static member or non-member function to this delegate.
             * 
             * @param fnptr The function taking 12 parameters to attach to the delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            inline void bond(function_ptr fnptr)
            {
                this->_bind(OMNI_NULL_PTR, reinterpret_cast<functor>(fnptr));
            }
            
            /**
             * @brief Attach a static member or non-member function to this delegate.
             * 
             * @tparam fnptr The function taking 12 parameters to attach to the delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < ret_t (*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            inline void bond()
            {
                this->_bind(OMNI_NULL_PTR, &_anon_param_fn<fnptr>);
            }
            
            /**
             * @brief Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            inline void bond(T& obj)
            {
                this->_bind(static_cast<void*>(&obj), &_member_param_fn<T, fnptr>);
            }

            /**
             * @brief Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            inline void bond(const T& obj)
            {
                this->_bind(static_cast<void*>(const_cast<T*>(&obj)), &_member_param_fn<T, fnptr>);
            }
            
            /**
             * @brief Attach a member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            inline void bond(const T *const obj)
            {
                this->_bind(static_cast<void*>(const_cast<T *const>(obj)), &_member_param_fn<T, fnptr>);
            }

            /**
             * @brief Attach a const member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The const function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) const >
            inline void bond_const(const T& obj)
            {
                this->_bind(static_cast<void*>(const_cast<T*>(&obj)), &_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * @brief Attach a const member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) const >
            inline void bond_const(const T *const obj)
            {
                this->_bind(static_cast<void*>(const_cast<T *const>(obj)), &_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * @brief Attach a static member or non-member function to this delegate.
             * 
             * @tparam fnptr The function taking 12 parameters to attach to the delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < ret_t (*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            static delegate12 bind()
            {
                return delegate12(OMNI_NULL_PTR, &_anon_param_fn<fnptr>);
            }
            
            /**
             * @brief Attach a parameterized member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The parameterized function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            static delegate12 bind(T& obj)
            {
                return delegate12(&obj, &_member_param_fn<T, fnptr>);
            }
            
            /**
             * @brief Attach a parameterized member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The parameterized function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            static delegate12 bind(const T& obj)
            {
                return delegate12(const_cast<T *const>(&obj), &_member_param_fn<T, fnptr>);
            }
            
            /**
             * @brief Attach a parameterized member function to this delegate.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The parameterized function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            static delegate12 bind(const T *const obj)
            {
                return delegate12(const_cast<T *const>(obj), &_member_param_fn<T, fnptr>);
            }

            /**
             * @brief Attach a const parameterized member function to this delegate.
             * 
             * @tparam T           The type of class to associate with this delegate
             * @tparam fnptr       The parameterized function to attach to the delegate
             * @param obj          The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) const >
            static delegate12 bind_const(const T& obj)
            {
                return delegate12(const_cast<T *const>(&obj), &_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * @brief Attach a parameterized member function to this delegate.
             * 
             * @tparam T           The type of class to associate with this delegate
             * @tparam fnptr       The parameterized function to attach to the delegate
             * @param obj          The instance of the class to reference in this delegate
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) const >
            static delegate12 bind_const(const T *const obj)
            {
                return delegate12(const_cast<T *const>(obj), &_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * @brief Gets if this instance is bound to a method
             *
             * @return True if this instance is currently bound
             */
            bool is_bound() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL_PTR);
            }
            
            /**
             * @brief Gets if this instance is bound to a member method
             *
             * @return True if this instance is currently bound to a target and method
             */
            bool is_member_bound() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL_PTR && this->m_target != OMNI_NULL_PTR);
            }
            
            /**
             * @brief Invoke the function bound to this delegate instance
             * 
             * @return  This function returns whatever is returned
             *          (if anything) from the invoked function
             */
            ret_t invoke(p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12) const
            {
                #if defined(OMNI_SAFE_DELEGATES)
                    omni::sync::mutex_lock(this->m_mtx);
                    if (this->m_method != OMNI_NULL_PTR) {
                        if (this->m_target == OMNI_NULL_PTR) {
                            function_ptr fp = reinterpret_cast<function_ptr>(this->m_method);
                            OMNI_D5_FW("invoking function");
                            omni::sync::mutex_unlock(this->m_mtx);
                            return (*fp)(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
                        } else {
                            functor m = this->m_method;
                            void* t = this->m_target;
                            OMNI_D5_FW("invoking function");
                            omni::sync::mutex_unlock(this->m_mtx);
                            return (*m)(t, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
                        }
                    }
                    omni::sync::mutex_unlock(this->m_mtx);
                #else
                    OMNI_D5_FW("invoking function");
                    return (this->m_target == OMNI_NULL_PTR ?
                            (*reinterpret_cast<function_ptr>(this->m_method))(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12) :
                            (*this->m_method)(this->m_target, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12));
                #endif
                OMNI_ERR_RETV_FW(OMNI_INVALID_DELEGATE_INVOKE_STR, omni::exceptions::invalid_delegate_invoke(), ret_t())
            }
            
            /**
             * @brief Directly invoke the function bound to this delegate instance.
             * 
             * @details This method does not preform any safety checks on the method
             * object instance and directly calls the method for invocation (if bound).
             * 
             * @return  This function returns whatever is returned
             *          (if anything) from the invoked function
             */
            ret_t invoke_direct(p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12) const
            {
                OMNI_D5_FW("invoking function");
                return (this->m_target == OMNI_NULL_PTR ?
                        (*reinterpret_cast<function_ptr>(this->m_method))(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12) :
                        (*this->m_method)(this->m_target, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12));
            }
            
            /**
             * @brief Gets the invocation type this delegate represents
             * 
             * @return The delegates omni::invoke_type::enum_t 
             */
            omni::invoke_t invoke_type() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                if (this->m_method == OMNI_NULL_PTR) { return omni::invoke_type::NONE; }
                return (this->m_target == OMNI_NULL_PTR ?
                        omni::invoke_type::ANONYMOUS :
                        omni::invoke_type::MEMBER_FUNC);
            }
            
            /**
             * @brief Gets the underlying functor called when this method is invoked.
             * 
             * @return The underlying functor method
             */
            functor method() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return this->m_method;
            }
            
            /**
             * @brief Gets the underlying function pointer called when this method is invoked.
             * 
             * @return The underlying function pointer, or an OMNI_NULL_PTR value if the
             * object instance is null (in the case of a static or non-member function).
             */
            function_ptr function() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return ((this->m_target == OMNI_NULL_PTR) ?
                        reinterpret_cast<function_ptr>(this->m_method) : OMNI_NULL_PTR);
            }
            
            /**
             * @brief Swaps the invocation method and target of 2 delegates
             */
            void swap(delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
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
             * @brief Gets the underlying target (if any) used when invoking this method.
             * 
             * @return A pointer to the underlying target object (if any)
             */
            void* target() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return this->m_target;
            }
            
            /**
             * @brief Detaches the target and method from this instance
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to unbind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            inline void unbind()
            {
                this->_bind(OMNI_NULL_PTR, OMNI_NULL_PTR);
                OMNI_D4_FW("instance unbound");
            }
            
            /**
             * @brief Sets the underlying method.
             * 
             * @details This method is marked unsafe since it manipulates
             * the underlying pointers. This method assumes the user understands
             * all implications with this.
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            inline void unsafe_set_method()
            {
                this->_set_method(&_member_param_fn<T, fnptr>);
            }

            /**
             * @brief Sets the underlying method.
             * 
             * @details This method is marked unsafe since it manipulates
             * the underlying pointers. This method assumes the user understands
             * all implications with this.
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) const >
            inline void unsafe_set_method_const()
            {
                this->_set_method(&_member_param_fn_const<T, fnptr>);
            }
            
            /**
             * @brief Sets the underlying target.
             * 
             * @details This method is marked unsafe since it manipulates
             * the underlying pointers. This method assumes the user understands
             * all implications with this.
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T >
            inline void unsafe_set_target(T& obj)
            {
                this->_set_target(&obj);
            }

            /**
             * @brief Sets the underlying target.
             * 
             * @details This method is marked unsafe since it manipulates
             * the underlying pointers. This method assumes the user understands
             * all implications with this.
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T >
            inline void unsafe_set_target(const T& obj)
            {
                this->_set_target(const_cast<T *const>(&obj));
            }
            
            /**
             * @brief Sets the underlying target.
             * 
             * @details This method is marked unsafe since it manipulates
             * the underlying pointers. This method assumes the user understands
             * all implications with this.
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            template < class T >
            inline void unsafe_set_target(const T *const obj)
            {
                this->_set_target(const_cast<T *const>(obj));
            }
            
            /**
             * @brief Checks if the current delegate instance is valid.
             * 
             * @details This only checks to see if there is a method attached
             * to this instance that can be invoked, and does not check if
             * the object attached is valid. 
             * 
             * @return True if the instance has a method attached, false if not
             */
            bool valid() const
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                return (this->m_method != OMNI_NULL_PTR);
            }
            
            /**
             * @brief Has the same effect as calling the invoke method.
             * 
             * @details Overloading this operator makes it such that you can
             * use the delegate as if it were a function, for example:
             * 
             * delegate<int> d = &some_func;
             * printf("value = %d", d());
             * 
             * @return The return type specified at compile time
             */
            inline ret_t operator()(p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12) const
            {
                return this->invoke(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
            }
            
            /**
             * @brief Calls this instances valid() function
             * 
             * @details The boolean operator allows you to check for validity as if
             * the delegate were a function pointer, example:
             * 
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
             * @brief The negated boolean () operator is used to check negation of the boolean () operator
             */
            inline bool operator!() const
            {
                return !(this->operator bool());
            }
            
            /**
             * @brief The assignment operator is used to set the target and method
             * of another delegate to this one.
             * 
             * @param d        The right most operand which to assign to
             *
             * @return A reference to the current instance
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& operator=(const delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
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
             * @brief Allows for assignment to anonymous (non-member) functions
             * by saying = &func_name
             * 
             * @param fp   The function pointer to assign
             *
             * @return A reference to the current instance
             * 
             * @warning If there is a function currently attached and still running when
             * this call is made to rebind, the attached function will continue to live
             * in an undefined state. It will not stop upon unbinding and will likely have
             * a corrupted stack pointer.
             */
            delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& operator=(function_ptr fnptr)
            {
                this->_bind(OMNI_NULL_PTR, reinterpret_cast<functor>(fnptr));
                return *this;
            }
            
            /**
             * @brief The equality operator test the target and method against the other
             * 
             * @param d        The right most operand which to compare to
             *
             * @return      True if the two instance are equal
             */
            bool operator==(const delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d) const
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
             * @brief The != operator is used for comparison results (negates the == operator)
             * 
             * @param d        The right most operand which to compare to
             *
             * @return True if the instances are not equal
             */
            bool operator!=(const delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d) const
            {
                return !(*this == d);
            }
            
        private:
            OMNI_SAFE_DGATE_MTX_FW
            /** The 12 parameter member function to be called */
            functor m_method;
            /** The instance of the object set when attaching to the delegate */
            void* m_target;
            
            /**
             * @brief The internal binding function that sets the underlying method and target
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
             * @brief Sets the underlying target object
             */
            void _set_target(void* obj)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                OMNI_D5_FW("binding target");
                this->m_target = obj;
            }
            
            /**
             * @brief Sets the underlying target function
             */
            void _set_method(functor mthd)
            {
                OMNI_SAFE_DGATE_ALOCK_FW
                OMNI_D5_FW("binding function");
                this->m_method = mthd;
            }
            
            /**
             * @brief Gets the parameterized non member (static/anonymous) function to use
             * 
             * @tparam fnptr         The method to assign
             */
            template < ret_t (*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            static ret_t _anon_param_fn(void*, p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12)
            {
                return (fnptr)(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
            }
            
            /**
             * @brief Get the parameterized member function to use
             * 
             * @tparam T           The class type
             * @tparam fnptr       The parameterized member method to use
             * @param obj          The instance object associated with the member method
             * 
             * @return             The functor
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) >
            static ret_t _member_param_fn(void* obj, p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12)
            {
                return ((static_cast<T*>(obj))->*(fnptr))(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
            }
            
            /**
             * @brief Get the const parameterized member function to use
             * 
             * @tparam T           The class type
             * @tparam fnptr       The parameterized member method to use
             * @param obj          The instance object associated with the member method
             * 
             * @return             The functor
             */
            template < class T, ret_t (T::*fnptr)(p1_t, p2_t, p3_t, p4_t, p5_t, p6_t, p7_t, p8_t, p9_t, p10_t, p11_t, p12_t) const >
            static ret_t _member_param_fn_const(void* obj, p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12)
            {
                return ((static_cast<T*>(obj))->*(fnptr))(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
            }
    };
    
    /**
     * @brief A generic delegate that has 12 parameters and does not return a value.
     */
    typedef omni::delegate12<void, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*> callback12;
    
    /**
     * @brief The event class is a type of multicast delegate.
     *
     * @details Events are a type of multi-cast delegate that allows client code to attach
     * multiple handlers of various classes, structs and anonymous functions, to a single
     * event handler. As long as each target method is signature compatable with the underlying
     * delegate type, classes and structs of various types can be attached to the same event object.
     * 
     * Invoking an event will invoke each attached handler (delegate) in the order they have been
     * attached.
     * 
     * @tparam Ret      Specifies the return type of the delegates to be attached
     * @tparam 12     Specifies the parameter types passed to the delegate
     */
    template < typename Ret, typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6, typename PT7, typename PT8, typename PT9, typename PT10, typename PT11, typename PT12 >
    class event12
    {
        public:
            /** Defines the return type this event will represent */
            typedef Ret ret_t;
            /** Defines the delegate signature this event represents */
            typedef omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > delegate_t;
            /** Defines the container type used by this event class */
            typedef typename omni_sequence_t< omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > > container_t;
            /** Defines an iterator type to the underlying types */
            typedef typename omni_sequence_t< omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > >::iterator iterator_t;
            /** Defines a const iterator type to the underlying types */
            typedef typename omni_sequence_t< omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > >::const_iterator const_iterator_t;
            /** Defines a reverse iterator type to the underlying types */
            typedef typename std::reverse_iterator< iterator_t > reverse_iterator_t;
            /** Defines a const reverse iterator type to the underlying types */
            typedef typename std::reverse_iterator< const_iterator_t > const_reverse_iterator_t;
            /** Defines the 1st function parameter type of this delegate */
            typedef PT1 p1_t;
            /** Defines the 2nd function parameter type of this delegate */
            typedef PT2 p2_t;
            /** Defines the 3rd function parameter type of this delegate */
            typedef PT3 p3_t;
            /** Defines the 4th function parameter type of this delegate */
            typedef PT4 p4_t;
            /** Defines the 5th function parameter type of this delegate */
            typedef PT5 p5_t;
            /** Defines the 6th function parameter type of this delegate */
            typedef PT6 p6_t;
            /** Defines the 7th function parameter type of this delegate */
            typedef PT7 p7_t;
            /** Defines the 8th function parameter type of this delegate */
            typedef PT8 p8_t;
            /** Defines the 9th function parameter type of this delegate */
            typedef PT9 p9_t;
            /** Defines the 10th function parameter type of this delegate */
            typedef PT10 p10_t;
            /** Defines the 11th function parameter type of this delegate */
            typedef PT11 p11_t;
            /** Defines the 12th function parameter type of this delegate */
            typedef PT12 p12_t;


            /**
             * @brief The default constructor
             * 
             * @details Constructs a default empty event handler
             */
            event12() : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list()
            {
                OMNI_SAFE_EVENT_INIT_FW
                OMNI_D5_FW("created event");
            }
            
            /**
             * @brief The copy constructor copies the elements from the other event passed in.
             *
             * @details Constructs a copy of the event passed in, copying each of the underyling
             * delegates to this instances list.
             *
             * @param cp    The event to copy
             */
            event12(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& cp) : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list(cp.m_list)
            {
                OMNI_SAFE_EVENT_INIT_FW
                OMNI_D5_FW("created event");
            }
            
            /**
             * @brief Creates an event with a signature compatible delegate attached
             *
             * @details Constructs an event with a single signature compatible delegate
             * added to its invocation list.
             *
             * @param d     The signature compatible delegate to add to the invocation list
             */
            event12(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d) : 
                OMNI_SAFE_EVENT_MILST_FW
                m_list()
            {
                OMNI_SAFE_EVENT_INIT_FW
                this->attach(d);
                OMNI_D5_FW("created event");
            }

            /**
             * @brief Destructs the event clearing the underlying list.
             * 
             * @details Destroys the event object and clears out the underlying list,
             * calling each of the attached delegates destructors.
             *
             * @warning If the function is still running when this delegate instance is
             * being destroyed, the function will continue to live in an undefined state.
             * The function will not stop upon destruction and will likely have a corrupted
             * stack pointer.
             */
            ~event12()
            {
                OMNI_TRY_FW
                this->clear();
                OMNI_SAFE_EVENT_DTOR_FW
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }
            
            /**
             * @brief Add (attach) a member delegate to this event instance
             * 
             * @details Adds a delegate to the end of this instances invocation list.
             * See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(1)
             * 
             * @param d     The member delegate to attach
             */
            void attach(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                /* DEV_NOTE: do not check if d does not have a valid function reference
                since on invoke d would fail if it did not have a valid fnptr */
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("attaching delegate");
                this->m_list.push_back(d);
            }
            
            /**
             * @brief Add (attach) a range of delegates to this event instance
             * 
             * @details Adds a range of delegates from an InputIterator template type.
             * Each of the elements is added to the end of this instances invocation list.
             * See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(n) where n is the number of elements to attach.
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
             * @brief Add (attach) another events invocation list to this instance
             * 
             * @details Adds a range of delegates from another event element with the
             * same signature. Each of the elements is added to the end of this instances
             * invocation list. See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(n) where n is the number of elements in the other events
             * list being attached.
             * 
             * @param e        The other event to add invocation list
             */
            void attach(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
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
             * @brief Add (attach) an anonymous/non-member or static member function to this delegate.
             * 
             * @details Adds a delegate to the end of this instances invocation list.
             * See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(1)
             * 
             * @tparam fnptr         The function to attach to the delegate
             */
            template < ret_t (*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            void attach()
            {
                this->attach( fnptr );
            }
            
            /**
             * @brief Add (attach) a member function to this delegate.
             * 
             * @details Adds a delegate to the end of this instances invocation list.
             * See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(1)
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            void attach(T& obj)
            {
                this->attach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Add (attach) a member function to this delegate.
             * 
             * @details Adds a delegate to the end of this instances invocation list.
             * See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(1)
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            void attach(const T& obj)
            {
                this->attach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Add (attach) a member function to this delegate.
             * 
             * @details Adds a delegate to the end of this instances invocation list.
             * See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(1)
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            void attach(const T *const obj)
            {
                this->attach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Add (attach) a const member function to this delegate.
             * 
             * @details Adds a delegate to the end of this instances invocation list.
             * See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(1)
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) const >
            void attach_const(const T& obj)
            {
                this->attach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * @brief Add (attach) a const member function to this delegate.
             * 
             * @details Adds a delegate to the end of this instances invocation list.
             * See the notes below about race conditions.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @invariant   O(1)
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) const >
            void attach_const(const T *const obj)
            {
                this->attach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * @brief Clears the underlying invocation list
             * 
             * @details Clears the underlying list of the attached delegates,
             * subsequently calling each delegates destructor.
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you attach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            void clear()
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                OMNI_D5_FW("clearing list");
                // clear the list container, calling the items destructors
                this->m_list.clear();
            }
            
            /**
             * @brief Tests if a specified member delegate is in this event instance.
             * 
             * @param d        The member delegate to search for
             * 
             * @return True if the delegate is found, false otherwise
             */
            bool contains(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return (this->_find(d) != this->m_list.end());
            }
            
            /**
             * @brief Tests if a specified member delegate is in this event instance.
             * 
             * @tparam fnptr         The function to attach to the delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < ret_t (*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            bool contains()
            {
                return this->contains( fnptr );
            }
            
            /**
             * @brief Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            bool contains(T& obj)
            {
                return this->contains( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            bool contains(const T& obj)
            {
                return this->contains( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            bool contains(const T *const obj)
            {
                return this->contains( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) const >
            bool contains_const(const T& obj)
            {
                return this->contains( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * @brief Tests if a specified member delegate is in this event instance.
             * 
             * @tparam T             The type of class to associate with this delegate
             * @tparam fnptr         The function to attach to the delegate
             * @param obj            The instance of the class to reference in this delegate
             * 
             * @return True if the delegate is found, false otherwise
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) const >
            bool contains_const(const T *const obj)
            {
                return this->contains( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * @brief Detach the last attached delegate that matches.
             * 
             * @details Removes the last attached delegate that matches the
             * signature, method and object of the delegate being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @param d        The member delegate to search for and detach
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            void detach(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                this->_rem(d, false);
            }
            
            /**
             * @brief Detach the last matched delegates from a range
             * 
             * @details Removes the last attached delegate that matches the
             * signature, method and object of the range being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @param begin     The input iterator pointing to the initial position in the sequence to remove
             * @param end       The input iterator pointing to the last position in the sequence to remove
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
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
            
            /**
             * @brief Detach the last matched delegates from another event
             * 
             * @details Removes the last attached delegate that matches the
             * signature, method and object of the range being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @param begin     The input iterator pointing to the initial position in the sequence to remove
             * @param end       The input iterator pointing to the last position in the sequence to remove
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            void detach(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
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
             * @brief Detach all attached delegate that match.
             * 
             * @details Removes all attached delegate that matches the
             * signature, method and object of the delegate being passed in,
             * subsequently calling those delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @param d        The member delegate to search for and detach
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            void detach_all(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                this->_rem(d, true);
            }
            
            /**
             * @brief Detach all matched delegates from a range
             * 
             * @details Removes all attached delegates that matches the
             * signature, method and object of the range being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @param begin     The input iterator pointing to the initial position in the sequence to remove
             * @param end       The input iterator pointing to the last position in the sequence to remove
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
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

            /**
             * @brief Detach all matched delegates from another event
             * 
             * @details Removes all attached delegate that matches the
             * signature, method and object of the range being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @param begin     The input iterator pointing to the initial position in the sequence to remove
             * @param end       The input iterator pointing to the last position in the sequence to remove
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            void detach_all(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
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
             * @brief Detach an anonymous/non-member or static member function from this event.
             * 
             * @details Removes the last attached function that matches the
             * signature of the delegate being passed in, subsequently calling
             * that delegates destructor. If there is no match, nothing happens
             * and no errors are thrown.
             * 
             * @tparam fnptr         The function to detach
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            template < ret_t (*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            void detach()
            {
                this->detach( fnptr );
            }
            
            /**
             * @brief Detach the last attached member function that matches.
             * 
             * @details Removes the last attached delegate that matches the
             * signature, method and object of the delegate being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            void detach(T& obj)
            {
                this->detach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Detach the last attached member function that matches.
             * 
             * @details Removes the last attached delegate that matches the
             * signature, method and object of the delegate being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            void detach(const T& obj)
            {
                this->detach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Detach the last attached member function that matches.
             * 
             * @details Removes the last attached delegate that matches the
             * signature, method and object of the delegate being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            template < class T, Ret (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) >
            void detach(const T *const obj)
            {
                this->detach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind< T, fnptr >(obj) );
            }
            
            /**
             * @brief Detach the last attached member function that matches.
             * 
             * @details Removes the last attached delegate that matches the
             * signature, method and object of the delegate being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) const >
            void detach_const(const T& obj)
            {
                this->detach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * @brief Detach the last attached const member function that matches.
             * 
             * @details Removes the last attached delegate that matches the
             * signature, method and object of the delegate being passed in,
             * subsequently calling that delegates destructor. If there is no
             * match, nothing happens and no errors are thrown.
             * 
             * @tparam T             The type of class to associate with the delegate
             * @tparam fnptr         The function to detach
             * @param obj            The instance of the class to reference
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @note See the notes on omni::delegate::~delegate about the implications
             * regarding destruction of the delegate class while a bound function is
             * still running.
             */
            template < class T, ret_t (T::*fnptr)(PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) const >
            void detach_const(const T *const obj)
            {
                this->detach( omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >::template bind_const< T, fnptr >(obj) );
            }
            
            /**
             * @brief Checks if the current event instance has any attached methods
             * 
             * @return True if the instance has a method or methods attached, false if not
             */
            bool empty() const
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return this->m_list.empty();
            }
            
            /**
             * @brief Gets the invocation list used to call the delegate objects on event invocation
             * 
             * @return The underlying container variable
             */
            container_t invocation_list() const
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                return this->m_list;
            }
            
            /**
             * @brief Invoke the functions bound to this event instance
             * 
             * @return The return type specified at compile time
             */
            ret_t invoke(p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12) const
            {
                OMNI_SAFE_EVENT_LOCK_FW
                OMNI_D5_FW("invoking attached delegates");
                const_iterator_t cur = this->m_list.begin();
                const_iterator_t tmp;
                while (cur != this->m_list.end()) {
                    tmp = cur;
                    if ((++tmp) == this->m_list.end()) {
                        OMNI_SAFE_EVENT_UNLOCK_FW
                        return cur->invoke(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
                    }
                    OMNI_SAFE_EVENT_UNLOCK_FW
                    cur->invoke(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
                    OMNI_SAFE_EVENT_LOCK_FW
                    if (++cur == this->m_list.end()) { break; }
                }
                OMNI_SAFE_EVENT_UNLOCK_FW
                OMNI_ERR_RETV_FW(OMNI_INVALID_DELEGATE_INVOKE_STR, omni::exceptions::invalid_delegate_invoke(), ret_t())
            }
            
            /**
             * @brief Calls the functions bound to this event instance in a non-safe manner.
             * delegate::invoke_direct does not perform certain checks.
             * 
             * @return The return type specified at compile time
             */
            ret_t invoke_direct(p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12) const
            {
                OMNI_SAFE_EVENT_LOCK_FW
                OMNI_D5_FW("invoking attached delegates direct");
                const_iterator_t cur = this->m_list.begin();
                const_iterator_t tmp;
                while (cur != this->m_list.end()) {
                    tmp = cur;
                    if ((++tmp) == this->m_list.end()) {
                        OMNI_SAFE_EVENT_UNLOCK_FW
                        return cur->invoke_direct(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
                    }
                    OMNI_SAFE_EVENT_UNLOCK_FW
                    cur->invoke_direct(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
                    OMNI_SAFE_EVENT_LOCK_FW
                    if (++cur == this->m_list.end()) { break; }
                }
                OMNI_SAFE_EVENT_UNLOCK_FW
                OMNI_ERR_RETV_FW(OMNI_INVALID_DELEGATE_INVOKE_STR, omni::exceptions::invalid_delegate_invoke(), ret_t())
            }
            
            /**
             * @brief Swaps the underlying lists between the two events
             */
            void swap(event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                #if defined(OMNI_SAFE_EVENTS)
                    omni::sync::scoped_lock<omni::sync::mutex_t> eauto_mtx(&e.m_mtx);
                #endif
                std::swap(this->m_list, e.m_list);
            }
            
            /**
             * @brief The () operator can be used to call the functions bound to this event instance
             * 
             * @return The return type specified at compile time
             */
            ret_t operator()(p1_t val1, p2_t val2, p3_t val3, p4_t val4, p5_t val5, p6_t val6, p7_t val7, p8_t val8, p9_t val9, p10_t val10, p11_t val11, p12_t val12) const
            {
                return this->invoke(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12);
            }
            
            /**
             * @brief Checks if this event has any attached delegates.
             * 
             * @returns True if the list is not empty, false otherwise
             */
            operator bool() const
            {
                return !this->empty();
            }
            
            /**
             * @brief Checks if this event has any attached delegates.
             * 
             * @returns True if the list is empty, false otherwise
             */
            bool operator!() const
            {
                return (!operator bool());
            }

            /**
             * @brief The assignment operator copies the list from another event
             * 
             * @param e        The right most operand event to assign
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns     A refernce to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& operator=(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
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
             * @brief Access a delegate directly by index.
             * 
             * @details The [int] operator can be used to access a specific delegate in the
             * invocation list directly.
             * 
             * @exception An omni::exceptions::index_out_of_range will be thrown if the index
             * requested is outside the range of this instance
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @return A reference to the delegate instance at the specified index
             */
            omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& operator[](std::size_t idx)
            {
                OMNI_SAFE_EVENT_ALOCK_FW
                if (this->m_list.empty() || (idx > (this->m_list.size() - 1))) {
                    OMNI_ERR_RETV_FW("Index out of range", omni::exceptions::index_out_of_range(), OMNI_NULL_PTR)
                }
                return *(this->m_list[idx]);
            }
            
            /**
             * @brief The += operator is used to add delegates to this event instance
             * 
             * @details This is similar to calling the attach method on this instance.
             * Each delegate is added to the end of the list and called in that order.
             * 
             * @param d        The right most operand delegate to add
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns A reference to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& operator+=(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                this->attach(d);
                return *this;
            }
            
            /**
             * @brief The += operator is used to add a list of delegates to this event instance
             * 
             * @details This is similar to calling the attach method on this instance.
             * Each delegate from the other event is added to the end of the list and
             * called in that order.
             * 
             * @param e        The right most operand event to add
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns A reference to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& operator+=(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
            {
                this->attach(e);
                return *this;
            }
            
            /**
             * @brief The -= operator is used to remove delegates from this event instance
             * 
             * @details This is similar to calling the detach method on this instance.
             * 
             * @param d        The right most operand delegate to add
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns A reference to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& operator-=(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                this->detach(d);
                return *this;
            }
            
            /**
             * @brief The -= operator is used to remove a list of delegates to this event instance
             * 
             * @details This is similar to calling the detach method on this instance.
             * 
             * @param e        The right most operand event to add
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns A reference to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& operator-=(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
            {
                this->detach(e);
                return *this;
            }
            
            /**
             * @brief The + operator adds delegate to the event instance and returns the combined list.
             * 
             * @param d        The right most operand delegate to add
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns A reference to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > operator+(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > ret(*this);
                ret.attach(d);
                return ret;
            }
            
            /**
             * @brief The + operator adds the event instance to another and returns the combined list.
             * 
             * @param e        The right most operand event to add
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns A reference to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > operator+(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
            {
                event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > ret(*this);
                ret.attach(e);
                return ret;
            }
            
            /**
             * @brief The - operator removes a delegate from the event instance and returns the new list.
             * 
             * @param d        The right most operand delegate to remove
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns A reference to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > operator-(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > ret(*this);
                ret.detach(d);
                return ret;
            }
            
            /**
             * @brief The - operator removes an event instance from another and returns the new list.
             * 
             * @param e        The right most operand event to remove
             * 
             * @warning If the OMNI_SAFE_EVENT defines are not enabled, it is undefined
             * if this event is invoked and edited at the same time; i.e. a race condition
             * can occur if you detach to an event from one thread while invoking from
             * another.
             * 
             * @returns A reference to this
             */
            event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > operator-(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e)
            {
                event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 > ret(*this);
                ret.detach(e);
                return ret;
            }
            
            /**
             * @brief Compares to events and tests the equality of their lists
             * 
             * @param e        The right most event which to compare to
             * 
             * @returns True if the events are equal, false otherwise
             */
            bool operator==(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e) const
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
             * @brief Negates the comparison operator
             * 
             * @param e        The right most event which to compare to
             * 
             * @returns True if the events are not equal, false otherwise
             */
            bool operator!=(const event12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& e) const
            {
                return !(*this == e);
            }
            
        private:
            OMNI_SAFE_EVENT_MTX_FW
            /** The collection of member methods */
            container_t m_list;

            /**
             * @brief Find a specified member delegate in this event instance.
             * 
             * @param d        The member delegate to search for
             * 
             * @return An iterator to the found delegate, list.end() if not found
             */
            iterator_t _find(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d)
            {
                // do not use any locks here as calling code does the lock
                if (this->m_list.empty()) { return this->m_list.end(); }
                iterator_t itr = this->m_list.end();
                while (itr != this->m_list.begin()) {
                    if (*(--itr) == d) { return itr; }
                }
                return this->m_list.end();
            }
            
            void _rem(const omni::delegate12< Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12 >& d, bool all)
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
    
    /** A generic event that has 12 parameters and does not return a value. */
    typedef omni::event12<void, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*> action12;
} // namespace omni

#define OMNI_DEL12_FW(Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) omni::delegate12<Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12>
#define OMNI_EVT12_FW(Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12) omni::event12<Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12>
#define OMNI_BIND12(Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12, Class, Function, Obj) omni::delegate12<Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12>::bind<Class, &Class::Function>(Obj)
#define OMNI_BIND12_CONST(Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12, Class, Function, Obj) omni::delegate12<Ret, PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12>::bind_const<Class, &Class::Function>(Obj)

namespace std {
    template < typename Ret, typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6, typename PT7, typename PT8, typename PT9, typename PT10, typename PT11, typename PT12 >
    inline void swap(omni::delegate12<Ret, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*>& d1, omni::delegate12<Ret, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*>& d2)
    {
        d1.swap(d2);
    }
    
    template < typename Ret, typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6, typename PT7, typename PT8, typename PT9, typename PT10, typename PT11, typename PT12 >
    inline void swap(omni::event12<Ret, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*>& e1, omni::event12<Ret, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*>& e2)
    {
        e1.swap(e2);
    }
}

#endif // OMNI_DELEGATE12_HPP
