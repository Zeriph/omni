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
#if !defined(OMNI_THREAD_ALLOCATE_HPP)
#define OMNI_THREAD_ALLOCATE_HPP 1
#include <omni/sync/thread.hpp>

namespace omni {
    namespace sync {
        // create_thread
        
        // void (T::*fnptr)()
        
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(T& obj)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T& obj)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T *const obj)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T *const obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T *const obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread create_thread(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T& obj)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T *const obj)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T *const obj, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T *const obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread create_thread_const(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        // void (T::*fnptr)(omni::sync::thread_arg_t)

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(T& obj)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(const T& obj)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(const T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(const T *const obj)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(const T *const obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread create_thread_parameterized(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread create_thread_parameterized_const(const T& obj)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread create_thread_parameterized_const(const T& obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread create_thread_parameterized_const(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread create_thread_parameterized_const(const T *const obj)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread create_thread_parameterized_const(const T *const obj, std::size_t max_stack_sz)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread create_thread_parameterized_const(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }

        // allocate_thread

        // void (T::*fnptr)()

        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(T& obj)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T& obj)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T *const obj)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T *const obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T *const obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() >
        static omni::sync::thread* allocate_thread(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T& obj)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T& obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T& obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T *const obj)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T *const obj, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T *const obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T *const obj, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), max_stack_sz, st);
        }
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread* allocate_thread_const(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::thread_start::bind<T, fnptr>(obj), op, val);
        }

        // void (T::*fnptr)(omni::sync::thread_arg_t)
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(T& obj)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(const T& obj)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(const T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(const T *const obj)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(const T *const obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::thread* allocate_thread_parameterized(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread* allocate_thread_parameterized_const(const T& obj)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread* allocate_thread_parameterized_const(const T& obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread* allocate_thread_parameterized_const(const T& obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread* allocate_thread_parameterized_const(const T *const obj)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj));
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread* allocate_thread_parameterized_const(const T *const obj, std::size_t max_stack_sz)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), max_stack_sz);
        }
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::thread* allocate_thread_parameterized_const(const T *const obj, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
        {
            return new omni::sync::thread(omni::sync::parameterized_thread_start::bind<T, fnptr>(obj), op, val);
        }
    } // namespace sync
} // namespace omni

#endif // OMNI_THREAD_ALLOCATE_HPP
