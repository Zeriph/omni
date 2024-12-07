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
#if !defined(OMNI_TIMER_HPP)
#define OMNI_TIMER_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/timer_t.hpp>
#if defined(OMNI_SAFE_QUEUE_TIMER)
    #include <omni/sync/basic_lock.hpp>
#endif

#if defined(OMNI_32BIT_QUEUE_TIMER)
    #define OMNI_QTMR_INT_FW uint32_t
#else
    #define OMNI_QTMR_INT_FW uint64_t
#endif

namespace omni {
    namespace chrono {
        /**
         * @brief          A timer class that invokes or queues a basic @c tick event.
         *
         * @details        This timer will invoke a @c tick event at a specified interval, and depending
         *                 on how long the delegate takes to complete, could queue up additional events.
         *                 In other words, if the timer elapses while an event is still executing, the
         *                 next event will be queued up and fire after the completion of the current event.
         *
         * @note           Since the timer event happens on a new thread, care must be taken to make sure
         *                 the attached delegate is re-entrant. It should also be noted that since these
         *                 events can be queued, even after the timer has been stopped, all events
         *                 remaining in the queue will continue to fire.
         */
        class queue_timer
        {
            public:
                queue_timer();
                queue_timer(const omni::chrono::queue_timer& cp);
                OMNI_EXPLICIT queue_timer(uint32_t interval_ms);
                queue_timer(uint32_t interval_ms,
                            const omni::chrono::timer_delegate& fn);
                queue_timer(uint32_t interval_ms,
                            const omni::chrono::timer_delegate& fn,
                            bool autoreset);
                queue_timer(uint32_t interval_ms,
                            const omni::chrono::timer_delegate& fn,
                            bool autoreset,
                            uint32_t delay);
                ~queue_timer();
                
                /**
                 * @brief       A basic object passed to the tick event.
                 * 
                 * @details     A stateful object passed into the tick event. This object is not
                 *              utilized by the internal tick code itself; it is simply a proxy
                 *              object that can be utilized in the user code of a tick event.
                 * 
                 * @warning     This object is not contained within the timer itself, and thus
                 *              not subject to any mutex locks or other thread-safe code. This
                 *              object is strictly accessed by user code only, and must be
                 *              as such. Take care when accessing or using this object.
                 */
                omni::generic_ptr state_object;
                /**
                 * @brief       The tick event that is called when the timer elapses.
                 * 
                 * @details     The event that is raised when the timer elapses. Each delegate
                 *              is called in the order to which it was attached. The tick event
                 *              is supposed to be a short-lived function, or you are to ensure
                 *              that a separate thread is called to handle the elapsed time.
                 * 
                 * @note        This timer will invoke a @c tick event at a specified interval, and depending
                 *              on how long the delegate takes to complete, could queue up additional events.
                 *              In other words, if the timer elapses while an event is still executing, the
                 *              next event will be queued up and fire after the completion of the current event.
                 *
                 * @warning     Since the timer event happens on a new thread, care must be taken to make sure
                 *              the attached delegate is re-entrant. It should also be noted that since these
                 *              events can be queued, even after the timer has been stopped, all events
                 *              remaining in the queue will continue to fire.
                 */
                omni::chrono::timer_event tick;
                
                /**
                 * @brief          Returns a boolean value based on if this timer auto-resets.
                 * 
                 * @details        If true, this timer will automatically tick again after
                 *                 the timer elapses. If false, then @c start must be called
                 *                 after each elapse of the timer.
                 */
                bool auto_reset() const; 
                /**
                 * @brief          Returns the interval, in milliseconds, of this timer.
                 * 
                 * @details        Returns the interval, in milliseconds, after which the
                 *                 tick event will be executed.
                 */
                uint32_t interval() const; 
                /**
                 * @brief          Returns the running state of this timer.
                 * 
                 * @details        Returns true if this timer is currently running, returns false
                 *                 if the timer will not execute any further tick events.
                 *
                 * @note           This does not indicate if an event is currently executing or
                 *                 is about to execute.
                 */
                bool is_running() const;
                /**
                 * @brief          Returns any queued up events.
                 * 
                 * @details        This will return the count of any tick events that are pending in the queue.
                 */
                std::size_t queue_count() const;
                /**
                 * @brief          Resets the current timer.
                 * 
                 * @details        This is the same as call @c start then @c stop and will effectively
                 *                 reset the timer back to 0. As an example, if a timer has a 6 second
                 *                 interval, and reset is called 3 seconds after it's started, instead
                 *                 of firing the tick event at 6 seconds, it will fire the event at 9
                 *                 seconds since it was reset to 0 after 3 seconds.
                 *
                 * @note           This does not interrupt any currently running ticks; that is, if a
                 *                 tick has been fired and then @c reset is called, the tick event
                 *                 will not be interrupted.
                 */
                void reset();
                /**
                 * @brief          Sets the timer to automatically reset after it elapses.
                 * 
                 * @details        If set to true, the timer will automatically tick again
                 *                 after the interval elapses. If set to false, then you
                 *                 must call @c start after each tick.
                 */
                void set_auto_reset(bool autoreset);
                /**
                 * @brief          Sets the timer interval.
                 * 
                 * @details        Sets the interval in between each timer tick event. This can be
                 *                 called after the timer has started and can lengthen or shorten
                 *                 when a tick is to happen. In other words, if an interval is initially
                 *                 set to 5 seconds, and the timer is started, then 3 seconds later
                 *                 the interval is set to 2 seconds, the timer will near immediately
                 *                 tick due to the interval being shortened.
                 *
                 *                 Inversely, if a timer has been set to 5 seconds, started, and then
                 *                 3 seconds later, the interval is set to 7 seconds, the timer will
                 *                 then fire at 7 seconds, prolonging any tick events from happening.
                 * 
                 * @warning        Care should be take to set the interval mid-tick or mid-interval
                 *                 as additional tick events can happen due to the change in interval
                 *                 time.
                 */
                void set_interval(uint32_t interval_ms);
                /**
                 * @brief          Starts the timer.
                 * 
                 * @details        Starts the timer and blocks until the timer is in a running state. If the
                 *                 timer is already running, nothing happens.
                 *
                 * @exception      omni::exceptions::invalid_delegate can be raised if there is no delegate
                 *                 attached to the tick event. Additionally omni::exceptions::index_out_of_range
                 *                 can be raised if the interval is set to 0.
                 */
                void start();
                /**
                 * @brief          Starts the timer after a delay.
                 * 
                 * @details        Starts the timer and blocks until the timer is in a running state. If the
                 *                 timer is already running, nothing happens.
                 * 
                 * @param delay    The delay, in milliseconds, to wait until the underlying timer thread starts.
                 *                 This allows you to add an additional delay to the first tick event. If the
                 *                 delay is 0, this has the same effect as just calling the @c start function.
                 *
                 * @exception      omni::exceptions::invalid_delegate can be raised if there is no delegate
                 *                 attached to the tick event. Additionally omni::exceptions::index_out_of_range
                 *                 can be raised if the interval is set to 0.
                 */
                void start(uint32_t delay);
                /**
                 * @brief          Stops the timer.
                 * 
                 * @details        Stops the timer and waits for any tick events to finish before continuing.
                 *                 This is a blocking call.
                 */
                void stop();
                /**
                 * @brief          Stops the timer.
                 * 
                 * @details        Stops the timer and waits for any tick events to finish before continuing.
                 *                 This is a blocking call.
                 * 
                 * @param join_timeout   The timeout to wait for any unfinished tick events before unblocking
                 *                       and continuing.
                 *
                 * @note           This call will essentially detach any running event threads before continuing.
                 */
                void stop(uint32_t join_timeout);
                /**
                 * @brief          Stops the timer.
                 * 
                 * @details        Stops the timer and waits for any tick events to finish before continuing.
                 *                 This is a blocking call.
                 * 
                 * @param join_timeout      The timeout to wait for any unfinished tick events before unblocking
                 *                          and continuing.
                 * @param kill_on_timeout   If this is true and the timeout elapses while waiting, the underlying
                 *                          event threads are killed.
                 *
                 * @note           If the timeout elapses and @c kill_on_timeout is true, the underlying threads will
                 *                 be killed. While killing a thread can be an option, it can leave the program
                 *                 in an undefined state. It's best to ensure your tick events are short lived
                 *                 and exit cleanly.
                 */
                void stop(uint32_t join_timeout, bool kill_on_timeout);
                /**
                 * @brief          Swaps the underlying timer data with another.
                 */
                void swap(omni::chrono::queue_timer& other);
                /**
                 * @brief          Returns the inline omni::chrono::timer_sync_type of this instance.
                 *
                 * @details        Returns omni::chrono::timer_sync_type::QUEUED
                 */
                inline omni::chrono::timer_sync_type::enum_t tick_type() const { return omni::chrono::timer_sync_type::QUEUED; }
                /**
                 * @brief          Assigns the underlying data from one timer to this one.
                 *
                 * @details        Assigns the interval, state object and tick event data of another
                 *                 timer to this one. If this timer is currently running, it is stopped
                 *                 before the assignment occurs.
                 *
                 * @warning        Care should be taken if your tick event delegate utilizes the
                 *                 state object of this instance since it could be destroyed
                 *                 in assignment.
                 */
                omni::chrono::queue_timer& operator=(const omni::chrono::queue_timer& other);
                /**
                 * @brief          Compares this timer instance to another.
                 *
                 * @details        Compares all aspects of this timer instance to another. This
                 *                 includes the state object, attached tick delegates, the interval,
                 *                 the queued events, and the current state of the timer
                 *                 (e.g. running/stopped).
                 */
                bool operator==(const omni::chrono::queue_timer& o) const;
                /**
                 * @brief          This the syntactic opposite of the equality operator.
                 */
                inline bool operator!=(const omni::chrono::queue_timer& o) const { return !(*this == o); }
                
                OMNI_MEMBERS_FW(omni::chrono::queue_timer) // disposing,name,type(),hash()
                
            private:
                #if defined(OMNI_SAFE_QUEUE_TIMER)
                    mutable omni::sync::basic_lock m_mtx;
                    mutable omni::sync::basic_lock m_qmtx;
                #endif
                omni_sequence_t<omni::chrono::timer_args> m_que; // the queue
                omni::sync::basic_thread* m_thread; // the main timer thread to _run on
                omni::sync::basic_thread* m_qthread; // the thread to run the queue on

                OMNI_QTMR_INT_FW m_int; // "elapsed" interval in ms between ticks
                volatile OMNI_QTMR_INT_FW m_status; // auto run (true by default), is_run, stop_req

                void _do_run();
                void _do_tick();
                void _run();
                void _run_delayed(omni::sync::thread_arg_t param);
                void _run_queued();
                bool _stopreq() const;
                bool _queue_empty() const;
        };
    } // namespace chrono
} // namespace omni

namespace std {
    inline void swap(omni::chrono::queue_timer& o1, omni::chrono::queue_timer& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_TIMER_HPP
