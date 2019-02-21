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
#if !defined(OMNI_THIS_THREAD_HPP)
#define OMNI_THIS_THREAD_HPP 1
#include <omni/types/thread_t.hpp>

namespace omni {
    namespace sync {
        /**
         * Stops the current thread from processing messages for the specified time
         * 
         * @param milliseconds The number of milliseconds to sleep the current thread
         */
        inline void sleep(uint32_t ms)
        {
            switch (ms) {
                case 0: { // 0 sleep is equivalent to yield
                    OMNI_THREAD_YIELD();
                } break;
                case 1: {
                    OMNI_SLEEP_INIT();
                    OMNI_SLEEP1();
                } break;
                default: {
                    OMNI_SLEEP_INIT();
                    OMNI_SLEEP(ms);
                } break;
            }
        }

        /**
         * Causes the current thread to be rescheduled by the OS.
         * Not to be confused with sleep, this function does not
         * stop the current thread, it merely calls the OS to have
         * its thread scheduler move the current thread to a new
         * thread schedule. If the current thread is of higher priority
         * (or 'real time') this call might not have an effect.
         */
        inline bool yield_thread()
        {
            #if defined(OMNI_OS_WIN)
                return (::SwitchToThread() != 0);
            #else
                return (::sched_yield() == 0);
            #endif
        }
    }
}

#endif // OMNI_THIS_THREAD_HPP
