/*
 * This file is part of the Omni C++ framework
 *
 * Copyright 2015, Zeriph Enterprises, LLC
 * 
 * PERMISSION TO USE, COPY, MODIFY, AND/OR DISTRIBUTE THIS SOFTWARE FOR ANY
 * PURPOSE WITH OR WITHOUT FEE IS HEREBY GRANTED, PROVIDED THAT THE ABOVE
 * COPYRIGHT NOTICE AND THIS PERMISSION NOTICE APPEAR IN ALL COPIES.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 * 
 * ZERIPH DOES NOT MAKE ANY ASSURANCES WITH REGARD TO THE ACCURACY OF THE RESULTS
 * OR OUTPUT THAT DERIVES FROM SUCH USE OF ANY SOFTWARE.
 */
#if !defined(OMNI_CONDITIONAL_HPP)
#define OMNI_CONDITIONAL_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/tick_t.hpp>
#include <omni/types/thread_t.hpp>
#include <omni/sync/lock.hpp>
#include <omni/sync/scoped_lock.hpp>
#include <omni/chrono/tick.hpp>

#if !defined(OMNI_OS_WIN)
    #include <errno.h> // errno
#endif

namespace omni {
    namespace sync {
        class conditional
        {
            public:
                conditional();
                explicit conditional(bool initialy_signaled);
                ~conditional();
                void broadcast();
                void reset();
                
                inline bool signaled() const
                {
                    omni::sync::scoped_lock<omni::sync::mutex_t> slock(&this->m_wait);
                    return this->m_signaled;
                }
                
                void signal();
                bool wait();
                bool wait(unsigned long timeout_ms);
                bool operator==(const omni::sync::conditional& o);            
                bool operator!=(const omni::sync::conditional& o);
                
                OMNI_MEMBERS_FW(omni::sync::conditional) // disposing,name,type(),hash()
                
            private:
                // defined but not implemented, doesn't make sense to copy
                conditional(const omni::sync::conditional &cp);
                omni::sync::conditional& operator=(const omni::sync::conditional& other);
                
                void _init();
                
                #if defined(OMNI_TYPE_INFO)
                    omni::type<omni::sync::conditional> m_type;
                #endif
                
                omni::sync::cond_t m_signal;
                mutable omni::sync::mutex_t m_wait;
                unsigned long m_waitreq;
                volatile mutable bool m_signaled;
        };
    }
}

#endif // OMNI_CONDITIONAL_HPP
