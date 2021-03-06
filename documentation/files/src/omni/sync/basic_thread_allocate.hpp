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
#if !defined(OMNI_BASIC_THREAD_ALLOCATE_HPP)
#define OMNI_BASIC_THREAD_ALLOCATE_HPP 1
#include <omni/sync/basic_thread.hpp>

namespace omni {
    namespace sync {
        // create_thread
        // void (T::*fnptr)()

        template < void (*fnptr)() >
        static omni::sync::basic_thread create_basic_thread()
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<fnptr>());
        }
        template < void (*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<fnptr>(), st);
        }
        template < void (*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<fnptr>(), max_stack_sz);
        }
        template < void (*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<fnptr>(), max_stack_sz, st);
        }
        template < void (*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<fnptr>(), op, val);
        }
        
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(T& obj)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T& obj)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T *const obj)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T *const obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T *const obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread create_basic_thread(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T& obj)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T *const obj)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T *const obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T *const obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread create_basic_thread_const(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        // void (T::*fnptr)(omni::sync::thread_arg_t)

        template < void (*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized()
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<fnptr>());
        }
        template < void (*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<fnptr>(), max_stack_sz);
        }
        template < void (*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<fnptr>(), op, val);
        }
        template < void (*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<fnptr>(), args);
        }
        template < void (*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<fnptr>(), max_stack_sz, args);
        }
        template < void (*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<fnptr>(), args, op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(T& obj)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(T& obj, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(T& obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(T& obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T& obj)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T& obj, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T& obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T& obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T *const obj)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T *const obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T *const obj, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized(const T *const obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T& obj)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T& obj, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T& obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T& obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T *const obj)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T *const obj, std::size_t max_stack_sz)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T *const obj, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread create_basic_thread_parameterized_const(const T *const obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }

        // allocate_thread

        // void (T::*fnptr)()

        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(T& obj)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }
        
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T& obj)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T *const obj)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T *const obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T *const obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::basic_thread* allocate_basic_thread(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T& obj)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T *const obj)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T *const obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T *const obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::basic_thread* allocate_basic_thread_const(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        // void (T::*fnptr)(omni::sync::thread_arg_t)
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(T& obj)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(T& obj, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(T& obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(T& obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T& obj)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T& obj, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T& obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T& obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T *const obj)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T *const obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T *const obj, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized(const T *const obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T& obj)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T& obj, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T& obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T& obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T *const obj)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T *const obj, std::size_t max_stack_sz)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T *const obj, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_arg_t args)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz, args);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::basic_thread* allocate_basic_thread_parameterized_const(const T *const obj, omni::sync::thread_arg_t args, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::basic_thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), args, op, val);
        }
    } // namespace sync
} // namespace omni

#endif // OMNI_BASIC_THREAD_ALLOCATE_HPP
