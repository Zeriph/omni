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
#if !defined(OMNI_RUNNABLE_HPP)
#define OMNI_RUNNABLE_HPP 1
#include <omni/sync/runnable.hpp>
#include <omni/types/thread_t.hpp>
#include <omni/sync/spin.hpp>

#if defined(OMNI_SAFE_RUNNABLE_THREAD)
    #include <omni/sync/basic_lock.hpp>
#endif

namespace omni {
    namespace sync {
        /** Represents a managed over-ridable runnable thread object. */
        class runnable_thread : virtual public omni::sync::runnable
        {
            public:
                /** Defines the thread changed event delegate signature */
                typedef omni::delegate2<void, const omni::sync::runnable_thread&, omni::sync::thread_state::enum_t> state_delegate;
                /** Defines the thread changed event delegate signature */
                typedef omni::event2<void, const omni::sync::runnable_thread&, omni::sync::thread_state::enum_t> state_event;
                
                // Methods
                runnable_thread();
                runnable_thread(const omni::sync::runnable_thread& cp);
                explicit runnable_thread(const omni::sync::runnable& obj);
                explicit runnable_thread(const omni::sync::thread_flags& ops);
                explicit runnable_thread(std::size_t max_stack_sz);
                runnable_thread(const omni::sync::runnable& obj, std::size_t max_stack_sz);
                runnable_thread(omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val);
                virtual ~runnable_thread();
                void abort(); // request end nicely
                bool abort_join();
                bool abort_join(uint32_t timeout);
                const omni::sync::thread_union_t get_option(omni::sync::thread_option::enum_t op) const;
                omni::sync::thread_flags get_options() const;
                omni::sync::thread_handle_t handle() const;
                omni::sync::thread_t id() const;
                bool is_alive() const;
                bool join(); // default of infinite timeout
                bool join(uint32_t timeout);
                bool join(const omni::chrono::unsigned_timespan& span);
                bool kill(); // Terminate 'immediately'
                virtual void run(omni::sync::thread_arg_t parm) { OMNI_UNUSED(parm); } // default empty run
                bool reset();
                bool restart();
                bool restart(omni::sync::thread_arg_t args);
                omni::sync::thread_state status() const;
                omni::sync::thread_t start();
                omni::sync::thread_t start(omni::sync::thread_arg_t args);
                void set_option(omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val);
                void set_options(unsigned char op, bool val);
                void set_options(const omni::sync::thread_flags& ops);
                void swap(omni::sync::runnable_thread& other);
                omni::sync::runnable_thread& operator=(const omni::sync::runnable_thread& other);
                
                using omni::sync::runnable::operator==;
                using omni::sync::runnable::operator!=;                
                bool operator==(const omni::sync::runnable_thread& other) const;
                bool operator!=(const omni::sync::runnable_thread& other) const;
                
                #if defined(OMNI_NON_PORTABLE)
                    omni::sync::thread_priority priority() const;
                    void set_priority(omni::sync::thread_priority::enum_t p);
                #endif
                
                /** Raised when the thread has changed state (running, stopped, etc) */
                omni::sync::runnable_thread::state_event state_changed;
                
                // disposing,name,type(),hash()
                OMNI_MEMBERS_FW(omni::sync::runnable_thread)
                
            protected:
                virtual void state_update(omni::sync::thread_state::enum_t old_state) { OMNI_UNUSED(old_state); }
                
            private:
                // Methods
                void _close_handle();
                void _hreset(bool force = false);
                bool _hvalid() const;
                bool _state_running() const;
                void _state_changed(omni::sync::thread_state::enum_t nstate);
                void _set_context(const omni::sync::runnable_thread& t2);
                #if defined(OMNI_NON_PORTABLE)
                    void _set_prio();
                #endif
                static OMNI_THREAD_FNPTR_T OMNI_THREAD_CALL_T _start(void* param);

                // Members
                #if defined(OMNI_SAFE_RUNNABLE_THREAD)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
                /** The arguments passed to the thread */
                omni::sync::thread_arg_t m_args;
                /** The underlying interface that's called on thread run (if none assigned, then this->run()) */
                omni::sync::runnable* m_iface;
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
                /** If join has been called, don't detach */
                volatile bool m_isjoined;
        };
    } // namespace sync
} // namespace omni

namespace std {
    inline void swap(omni::sync::runnable_thread& ot1, omni::sync::runnable_thread& ot2)
    {
        ot1.swap(ot2);
    }
}

#endif // OMNI_RUNNABLE_HPP
