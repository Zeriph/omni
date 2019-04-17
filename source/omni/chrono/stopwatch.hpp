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
#if !defined(OMNI_STOPWATCH_HPP)
#define OMNI_STOPWATCH_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/chrono/tick.hpp>
#include <omni/chrono/span.hpp>
#if defined(OMNI_SAFE_STOPWATCH)
    #include <omni/sync/basic_lock.hpp>
#endif

namespace omni {
    /**
     * @brief The stopwatch class is a simple timer class that will keep track of monotonic time.
     * 
     * @details 
     * 
     * @exception Errors
     * 
     * @warning Consideration
     * 
     * @attention Platform
     * 
     * @note Notes
     */
    class stopwatch
    {
        public:
            stopwatch();
            stopwatch(const omni::stopwatch &cp);
            ~stopwatch();

            omni::chrono::unsigned_timespan elapsed() const;
            uint64_t elapsed_us() const;
            uint64_t elapsed_ms() const;
            uint64_t elapsed_s() const;
            bool is_running() const;
            omni::stopwatch& reset();
            omni::stopwatch& restart();
            /**
             * @brief          Brief description.
             * 
             * @details        A more detailed description of the function.
             * 
             * @return         [optional] A return value if any.
             * 
             * @param [name]   [optional] Each parameter should be marked with this.
             * @tparam [name]  [optional] Each template parameter should be marked with this.
             * 
             * @exception      [optional] Any errors (or error conditions) specific to this context.
             * 
             * @warning        [optional] Any extra considerations to be aware of.
             * 
             * @attention      [optional] Any platform specific notes.
             * 
             * @note           [optional] Any notes to be aware of (like system calls, order of operations, etc.).
             * 
             * @invariant      [optional] This is the complexity of this function (e.g. O(1) for X conditions, etc.)
             */
            omni::stopwatch& restart(uint32_t offset_ms);
            omni::stopwatch& start();
            omni::stopwatch& start(uint32_t offset_ms);
            omni::stopwatch& stop();
            omni::stopwatch& operator=(const omni::stopwatch &other);
            omni::stopwatch& operator=(bool enable);
            bool operator==(const omni::stopwatch &o) const;
            bool operator!=(const omni::stopwatch &o) const;
            
            OMNI_MEMBERS_FW(omni::stopwatch) // disposing,name,type(),hash()

            OMNI_OSTREAM_RAW_FW(omni::stopwatch, value.elapsed_ms() << " ms")
            
        private:
            /** The internal end clock */
            omni::chrono::tick_t m_end;
            /** The internal start clock */
            omni::chrono::tick_t m_init;
            /** Determines of the current stopwatch is running (start called but not stop) */
            volatile bool m_isrun;
            /** Determines if the stopwatch has been started and not reset */
            volatile bool m_isstrt;

            #if defined(OMNI_SAFE_STOPWATCH)
                mutable omni::sync::basic_lock m_mtx;
            #endif

            /** zero's the clocks */
            void _zero();
    };
}

#endif // OMNI_STOPWATCH_HPP
