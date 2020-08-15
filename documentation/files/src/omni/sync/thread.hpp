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
#if !defined(OMNI_THREAD_HPP)
#define OMNI_THREAD_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/thread_t.hpp>
#include <omni/sync/this_thread.hpp>
#include <omni/sync/basic_lock.hpp>
#include <omni/sync/spin.hpp>
#include <omni/chrono/span.hpp>
#include <map>

namespace omni {
    namespace sync {
        class thread
        {
            public:
                // types
                typedef omni::event1<void, const omni::sync::thread&> event;
                typedef omni::sync::thread::event::delegate_t delegate;
                
                // thread constructors
                thread();
                thread(const omni::sync::thread& cp);
                explicit thread(const omni::sync::thread_flags& ops);
                explicit thread(std::size_t max_stack_sz);
                explicit thread(const omni::sync::thread_start& mthd);
                explicit thread(const omni::sync::parameterized_thread_start& mthd);
                thread(const omni::sync::thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req);
                thread(const omni::sync::thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       const omni::sync::thread::delegate& comp);
                thread(const omni::sync::thread_start& mthd,
                       omni::sync::thread_start_type::enum_t st);
                thread(const omni::sync::thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       omni::sync::thread_start_type::enum_t st);
                thread(const omni::sync::thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       const omni::sync::thread::delegate& comp,
                       omni::sync::thread_start_type::enum_t st);
                thread(const omni::sync::thread_start& mthd,
                       std::size_t max_stack_sz);
                thread(const omni::sync::thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       std::size_t max_stack_sz);
                thread(const omni::sync::thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       const omni::sync::thread::delegate& comp,
                       std::size_t max_stack_sz);
                thread(const omni::sync::thread_start& mthd,
                       std::size_t max_stack_sz,
                       omni::sync::thread_start_type::enum_t st);
                thread(const omni::sync::thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       std::size_t max_stack_sz,
                       omni::sync::thread_start_type::enum_t st);
                thread(const omni::sync::thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       const omni::sync::thread::delegate& comp,
                       std::size_t max_stack_sz,
                       omni::sync::thread_start_type::enum_t st);
                thread(const omni::sync::thread_start& mthd,
                       omni::sync::thread_option::enum_t op,
                       omni::sync::thread_union_t val);
                thread(const omni::sync::parameterized_thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req);
                thread(const omni::sync::parameterized_thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       const omni::sync::thread::delegate& comp);
                thread(const omni::sync::parameterized_thread_start& mthd,
                       std::size_t max_stack_sz);
                thread(const omni::sync::parameterized_thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       std::size_t max_stack_sz);
                thread(const omni::sync::parameterized_thread_start& mthd,
                       const omni::sync::thread::delegate& abort_req,
                       const omni::sync::thread::delegate& comp,
                       std::size_t max_stack_sz);
                thread(const omni::sync::parameterized_thread_start& mthd,
                       omni::sync::thread_option::enum_t op,
                       omni::sync::thread_union_t val);
                ~thread();
                
                static bool abort_requested();
                static void request_abort(omni::sync::thread_t tid);
                static void request_abort(const omni::sync::thread& tid)
                { omni::sync::thread::request_abort(tid.id()); }
                
                void abort(); // request end nicely
                bool abort_join();
                bool abort_join(uint32_t timeout);
                bool bind(const omni::sync::parameterized_thread_start& mthd);
                bool bind(const omni::sync::thread_start& mthd);
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
                bool join(); // default of infinite timeout
                bool join(uint32_t timeout);
                bool join(const omni::chrono::unsigned_span_t& span);
                bool kill(); // Terminate immediately
                bool reset();
                bool restart();
                bool restart(omni::sync::thread_arg_t args);
                bool restart(const omni::sync::thread_start& mthd);
                bool restart(const omni::sync::parameterized_thread_start& mthd);
                bool restart(const omni::sync::parameterized_thread_start& mthd, omni::sync::thread_arg_t args);
                omni::sync::thread_state status() const;
                omni::sync::thread_t start();
                omni::sync::thread_t start(omni::sync::thread_arg_t args);
                void set_option(omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val);
                void set_options(unsigned char op, bool val);
                void set_options(const omni::sync::thread_flags& ops);
                void swap(omni::sync::thread& other);
                bool unbind();
                omni::sync::thread& operator=(const omni::sync::thread& other);
                bool operator==(const omni::sync::thread& other) const;
                bool operator!=(const omni::sync::thread& other) const;
                
                #if defined(OMNI_NON_PORTABLE)
                    omni::sync::thread_priority priority() const;
                    void set_priority(omni::sync::thread_priority::enum_t p);
                #endif
                
                omni::sync::thread::event aborted;
                omni::sync::thread::event completed;
                
                OMNI_MEMBERS_FW(omni::sync::thread) // disposing,name,type(),hash()
                
            private:
                // Methods
                void _chkmthd();
                void _close_handle(bool allow_rejoin);
                void _hreset(bool force, bool allow_rejoin);
                bool _hvalid() const;
                bool _state_running() const;
                void _state_changed(omni::sync::thread_state::enum_t nstate);
                void _state_machine();
                void _set_context(const omni::sync::thread& t2);
                #if defined(OMNI_NON_PORTABLE)
                    void _set_prio();
                #endif
                
                // Members
                #if defined(OMNI_SAFE_THREAD)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
                omni::sync::thread_arg_t m_args;
                void* m_mthd;
                omni::sync::thread_t m_tid;
                omni::sync::thread_handle_t m_thread;
                omni::sync::thread_flags m_ops;
                omni::sync::thread_state m_state;
                #if defined(OMNI_NON_PORTABLE)
                    omni::sync::thread_priority m_priority;
                #endif
                volatile bool m_isjoined;
                volatile bool m_ispmthd;
                
                static OMNI_THREAD_FNPTR_T OMNI_THREAD_CALL_T _start(void* param);
                
                class manager
                {
                    public:
                        manager() : m_lock(), m_aborts(), m_threads() {}
                        ~manager() {}
                        void abort(omni::sync::thread_t tid);
                        bool abort_requested();
                        void push_back(omni::sync::thread_t tid, omni::sync::thread& bthread);
                        void pop_back(omni::sync::thread_t tid);
                        void remove(omni::sync::thread_t tid);
                        void request_abort(omni::sync::thread_t tid);
                        
                        static manager& instance()
                        {
                            /* typically a new without a delete is a memory leak, but this
                            has a similar effect to a static global variable. This instance
                            method is following the static init on first use idiom to avoid
                            the static init order fiasco that can cause innocuous crashes.
                            Specifically, the lock and thread_map variables are those we would
                            have declared as static. */
                            static omni::sync::thread::manager* ret = new omni::sync::thread::manager();
                            return *ret;
                        }
                        
                    private:
                        typedef std::map<omni::sync::thread_t, bool> abort_map;
                        typedef std::map<omni::sync::thread_t, omni::sync::thread*> thread_map;
                        
                        omni::sync::basic_lock m_lock;
                        abort_map m_aborts;
                        thread_map m_threads;
                        
                        manager(const manager& cp); // = delete;
                        manager& operator=(const manager& cp); // = delete;
                };
        };
    } // namespace sync
} // namespace omni

namespace std {
    inline void swap(omni::sync::thread& ot1, omni::sync::thread& ot2)
    {
       ot1.swap(ot2);
    }
}

#include <omni/sync/thread_allocate.hpp>

#endif // OMNI_THREAD_HPP
