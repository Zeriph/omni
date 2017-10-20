/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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
#if !defined(OMNI_TIMER_T_HPP)
#define OMNI_TIMER_T_HPP 1
#include <omni/defs/global.hpp>
// TODO: why was this included here?
// #include <omni/chrono/stopwatch.hpp>
#include <omni/generic_ptr.hpp>
#include <omni/sync/basic_thread.hpp>
#include <omni/delegate/2.hpp>

namespace omni {
    namespace chrono {
        typedef struct timer_sync_type {
            typedef enum enum_t {
                /**
                 * When the timer interval passes, the interval counter is reset and a separate thread is
                 * spawned and detached in which the tick event will be fired. Care should be taken for any
                 * attached delegates since the event fires in a separate thread, if a function takes longer
                 * than the interval, a tick can happen and thus the function can be called while still
                 * executing; as such, any functions should be re-entrant or thread safe.
                 */
                ASYNCHRONOUS,
                /**
                 * When the timer interval passes the tick event will block and execute any delegates
                 * in the order they were attached. The timer interval counter will not be reset until
                 * the last attached delegate returns, thus adding additional time between official ticks.
                 */
                SYNCHRONOUS,
                /**
                 * When the timer interval passes, the interval counter is reset and any attached delegates
                 * are called in the order they were attached. If any functions should take longer than the
                 * timer interval and an interval lapse happens, any subsequent ticks will be dropped while
                 * the attached delegates are still executing. It is possible to have an events fire immediately
                 * after each other if the timing works out such that the delegate call finishes as the tick
                 * event is about to occur.
                 */
                DROP,
                /**
                 * When the timer interval passes, the interval counter is reset and any attached delegates
                 * are pushed to a queue that are executed on a separate thread that monitors said queue. If
                 * an attached delegates take longer than the tick interval, any subsequent tick events are
                 * queued up and called in succession without regards to the tick event or interval on the
                 * queue monitor thread.
                 */
                QUEUED
            } enum_t;
            
            /** Defines the number of elements in the enum */
            static const unsigned short COUNT = 4;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(ASYNCHRONOUS);
                    OMNI_E2S_FW(SYNCHRONOUS);
                    OMNI_E2S_FW(DROP);
                    OMNI_E2S_FW(QUEUED);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(ASYNCHRONOUS);
                    OMNI_E2WS_FW(SYNCHRONOUS);
                    OMNI_E2WS_FW(DROP);
                    OMNI_E2WS_FW(QUEUED);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } timer_sync_type;
        
        typedef struct timer_args {
            timer_args() :
                signal_time(),
                state_object()
                { }
            
            timer_args(const timer_args& cp) :
                signal_time(cp.signal_time),
                state_object(cp.state_object)
                { }
            
            timer_args(omni::chrono::tick_t st, const omni::generic_ptr& sobj) :
                signal_time(st),
                state_object(sobj)
                { }
                
            omni::chrono::timer_args& operator=(const omni::chrono::timer_args& o)
            {
                this->signal_time = o.signal_time;
                this->state_object = o.state_object;
                return *this;
            }
            
            bool operator==(const omni::chrono::timer_args& o) const
            {
                if (this == &o) { return true; }
                return (omni::chrono::equal(this->signal_time, o.signal_time) &&
                        this->state_object == o.state_object);
            }
            
            bool operator!=(const omni::chrono::timer_args& o) const
            {
                return !(*this == o);
            }
        
            omni::chrono::tick_t signal_time;
            omni::generic_ptr state_object;
        } timer_args;
        
        typedef omni::event2<void, omni::chrono::tick_t, const omni::generic_ptr&> timer_event;
        typedef omni::chrono::timer_event::delegate_t timer_delegate;
        typedef omni::chrono::timer_sync_type::enum_t timer_sync_t;
    }
}

#endif // OMNI_TIMER_T_HPP
