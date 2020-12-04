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
#if !defined(OMNI_SYNC_TIMER_HPP)
#define OMNI_SYNC_TIMER_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/timer_t.hpp>
#if defined(OMNI_SAFE_SYNC_TIMER)
    #include <omni/sync/basic_lock.hpp>
#endif

#if defined(OMNI_32BIT_SYNC_TIMER)
    #define OMNI_STMR_INT_FW uint32_t
#else
    #define OMNI_STMR_INT_FW uint64_t
#endif

namespace omni {
    namespace chrono {
        class sync_timer
        {
            public:
                sync_timer();
                sync_timer(const omni::chrono::sync_timer& cp);
                OMNI_EXPLICIT sync_timer(uint32_t interval_ms);
                sync_timer(uint32_t interval_ms,
                           const omni::chrono::timer_delegate& fn);
                sync_timer(uint32_t interval_ms,
                           const omni::chrono::timer_delegate& fn,
                           bool autoreset);
                sync_timer(uint32_t interval_ms,
                           const omni::chrono::timer_delegate& fn,
                           bool autoreset,
                           uint32_t delay);
                ~sync_timer();
                
                omni::generic_ptr state_object; // state object used when tick event passes
                omni::chrono::timer_event tick; // Occurs when the interval has passed
                
                bool auto_reset() const; 
                uint32_t interval() const; 
                bool is_running() const;
                void reset();
                void set_auto_reset(bool autoreset);
                void set_interval(uint32_t interval_ms);
                void start();
                void start(uint32_t delay);
                void stop();
                void stop(uint32_t join_timeout);
                void stop(uint32_t join_timeout, bool kill_on_timeout);
                void swap(omni::chrono::sync_timer& other);
                omni::chrono::timer_sync_type::enum_t tick_type() const { return omni::chrono::timer_sync_type::SYNCHRONOUS; }
                omni::chrono::sync_timer& operator=(const omni::chrono::sync_timer& other);
                bool operator==(const omni::chrono::sync_timer& o) const;
                inline bool operator!=(const omni::chrono::sync_timer& o) const { return !(*this == o); }
                
                OMNI_MEMBERS_FW(omni::chrono::sync_timer) // disposing,name,type(),hash()
                
            private:
                void _do_run();
                void _do_tick();
                void _run();
                void _run_delayed(omni::sync::thread_arg_t param);
                void _run_noblock();
                bool _stopreq() const;
                
                #if defined(OMNI_SAFE_SYNC_TIMER)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
                omni::sync::basic_thread *m_thread; // the main timer thread to _run on

                OMNI_STMR_INT_FW m_int; // "elapsed" interval in ms between ticks
                volatile OMNI_STMR_INT_FW m_status; // auto run (true by default), is_run, stop_req
        };
    } // namespace chrono
} // namespace omni

namespace std {
    inline void swap(omni::chrono::sync_timer& o1, omni::chrono::sync_timer& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_SYNC_TIMER_HPP
