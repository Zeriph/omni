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
#if !defined(OMNI_BASIC_THREAD_HPP)
#define OMNI_BASIC_THREAD_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/thread_t.hpp>
#include <omni/sync/spin.hpp>
#include <omni/chrono/span.hpp>
#include <omni/sync/basic_lock.hpp>
#include <map>

namespace omni {
    namespace sync {
        /** Represents an unmanaged system thread object. Automatically starts the thread when created
         * unless otherwise specified.
         */
        class basic_thread
        {
            public:
                // Where a constructor specifies a delegate method, unless user specified, the default start type is NOW
                basic_thread();
                basic_thread(const omni::sync::basic_thread& cp);
                explicit basic_thread(const omni::sync::thread_flags& ops);
                explicit basic_thread(std::size_t max_stack_sz);
                explicit basic_thread(const omni::sync::thread_start& mthd);
                explicit basic_thread(const omni::sync::parameterized_thread_start& mthd);
                basic_thread(const omni::sync::thread_t& tid,
                             const omni::sync::thread_handle_t& h);
                basic_thread(const omni::sync::thread_start& mthd,
                             omni::sync::thread_start_type::enum_t st);
                basic_thread(const omni::sync::thread_start& mthd,
                             std::size_t max_stack_sz);
                basic_thread(const omni::sync::thread_start& mthd,
                             std::size_t max_stack_sz,
                             omni::sync::thread_start_type::enum_t st);
                basic_thread(const omni::sync::thread_start& mthd,
                             omni::sync::thread_option::enum_t op,
                             omni::sync::thread_union_t val);
                basic_thread(const omni::sync::parameterized_thread_start& mthd,
                             omni::sync::thread_arg_t args);
                basic_thread(const omni::sync::parameterized_thread_start& mthd,
                             omni::sync::thread_start_type::enum_t st);
                basic_thread(const omni::sync::parameterized_thread_start& mthd,
                             std::size_t max_stack_sz);
                basic_thread(const omni::sync::parameterized_thread_start& mthd,
                             std::size_t max_stack_sz,
                             omni::sync::thread_arg_t args);
                basic_thread(const omni::sync::parameterized_thread_start& mthd,
                             std::size_t max_stack_sz,
                             omni::sync::thread_start_type::enum_t st);
                basic_thread(const omni::sync::parameterized_thread_start& mthd,
                             omni::sync::thread_option::enum_t op,
                             omni::sync::thread_union_t val);
                basic_thread(const omni::sync::parameterized_thread_start& mthd,
                             omni::sync::thread_arg_t args,
                             omni::sync::thread_option::enum_t op,
                             omni::sync::thread_union_t val);
                ~basic_thread();
                
                void bind(const omni::sync::parameterized_thread_start& mthd);
                void bind(const omni::sync::thread_start& mthd);
                void detach();
                void detach(bool allow_rejoin);
                const omni::sync::thread_union_t get_option(omni::sync::thread_option::enum_t op) const;
                omni::sync::thread_flags options() const;
                omni::sync::thread_handle_t handle() const;
                omni::sync::thread_t id() const;
                bool is_alive() const;
                bool is_bound() const;
                bool is_parameter_bound() const;
                bool is_detached() const;
                bool is_threadpool_thread() const;
                bool join(); // default of infinite timeout
                bool join(uint32_t timeout);
                bool join(const omni::chrono::unsigned_span_t& span);
                bool kill(); // Terminate immediately
                omni::sync::thread_state status() const;
                omni::sync::thread_t start();
                omni::sync::thread_t start(omni::sync::thread_arg_t args);
                void set_option(omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val);
                void set_options(unsigned char op, bool val);
                void set_options(const omni::sync::thread_flags& ops);
                void swap(omni::sync::basic_thread& other);
                void unbind();
                omni::sync::basic_thread& operator=(const omni::sync::basic_thread& other);
                bool operator==(const omni::sync::basic_thread& other) const;
                bool operator!=(const omni::sync::basic_thread& other) const;
                
                #if defined(OMNI_NON_PORTABLE)
                    omni::sync::thread_priority priority() const;
                    void set_priority(omni::sync::thread_priority::enum_t p);
                #endif
                
                OMNI_MEMBERS_FW(omni::sync::basic_thread) // disposing,name,type(),hash()
                
                static inline const omni::sync::basic_thread current()
                {
                    return omni::sync::basic_thread(omni::sync::thread_id(), omni::sync::thread_handle());
                }
                
                static inline omni::sync::basic_thread create_threadpool_thread(const omni::sync::thread_start& tpoolfn)
                {
                    return omni::sync::basic_thread(tpoolfn, true);
                }
                
            private:
                // Methods
                basic_thread(const omni::sync::thread_start& mthd, bool tpool);
                void _chkmthd();
                void _close_handle(bool allow_rejoin);
                void _hreset(bool force, bool allow_rejoin);
                bool _hvalid() const;
                bool _state_running() const;
                void _state_machine(const omni::sync::thread_t tid);
                void _set_context(const omni::sync::basic_thread& t2);
                #if defined(OMNI_NON_PORTABLE)
                    void _set_prio();
                #endif
                
                // Members
                #if defined(OMNI_SAFE_BASIC_THREAD)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
                /** The arguments passed to the thread */
                omni::sync::thread_arg_t m_args;
                /** The delegate invoked on the thread when started */
                void* m_mthd;
                /** The underlying thread ID type */
                omni::sync::thread_t m_tid;
                /** The underlying thread handle type */
                omni::sync::thread_handle_t m_thread;
                /** The underlying thread options */
                omni::sync::thread_flags m_ops;
                /** The current state of the thread */
                omni::sync::thread_state m_state;
                #if defined(OMNI_NON_PORTABLE)
                    /** The threads priority */
                    omni::sync::thread_priority m_priority;
                #endif
                /** If join has been called, do not detach */
                volatile bool m_isjoined;
                /** If parameterized start function */
                volatile bool m_ispmthd;
                /** True if it is a thread pool thread */
                volatile bool m_istpool;
                
                static OMNI_THREAD_FNPTR_T OMNI_THREAD_CALL_T _start(void* param);
                
                /**
                 * This class is an internal thread manager not intended to be used anywhere but here.
                 * it is used to avoid the static init order fiasco (via the static instance function).
                 * it is private to avoid external use as well to allow it access to the private functions.
                 */
                class manager
                {
                    public:
                        manager() : m_lock(), m_threads() {}
                        ~manager() {}
                        void push_back(omni::sync::thread_t tid, omni::sync::basic_thread& bthread);                        
                        void pop_back(omni::sync::thread_t tid);
                        void remove(omni::sync::thread_t tid);
                        
                        static manager& instance()
                        {
                            static omni::sync::basic_thread::manager* ret = new omni::sync::basic_thread::manager();
                            return *ret;
                        }
                        
                    private:
                        typedef std::map<omni::sync::thread_t, omni::sync::basic_thread*> thread_map;
                    
                        omni::sync::basic_lock m_lock;
                        thread_map m_threads;
                        
                        manager(const manager& cp); // = delete;
                        manager& operator=(const manager& cp); // = delete;
                };
        };
    }
} // namespace omni

namespace std {
    inline void swap(omni::sync::basic_thread& ot1, omni::sync::basic_thread& ot2)
    {
        ot1.swap(ot2);
    }
}

#include <omni/sync/basic_thread_allocate.hpp>

#endif // OMNI_BASIC_THREAD_HPP
