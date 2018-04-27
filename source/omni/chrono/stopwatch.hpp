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
            // TODO: omni::timespan elapsed();
            
            uint64_t elapsed_us() const;
            uint64_t elapsed_ms() const;
            uint64_t elapsed_s() const;
            bool is_running() const;
            omni::stopwatch& reset();
            omni::stopwatch& restart();
            /**
             * @brief Brief
             * 
             * @details Details
             * 
             * @exception Errors
             * 
             * @warning Consideration
             * 
             * @attention Platform
             * 
             * @note Notes
             * 
             * @param offset_ms Parameter_Description
             * 
             * @return Return_Description
             */
            omni::stopwatch& restart(unsigned long offset_ms);
            omni::stopwatch& start();
            omni::stopwatch& start(unsigned long offset_ms);
            omni::stopwatch& stop();
            omni::stopwatch& operator=(const omni::stopwatch &other);
            omni::stopwatch& operator=(bool enable);
            bool operator==(const omni::stopwatch &o) const;
            bool operator!=(const omni::stopwatch &o) const;
            
            OMNI_MEMBERS_FW(omni::stopwatch) // disposing,name,type(),hash()

            OMNI_OSTREAM_RAW_FW(omni::stopwatch, value.elapsed_ms() << " ms")
            
        private:
            /** zero's the clocks */
            void _zero();
            
            /** The internal end clock */
            omni::chrono::tick_t m_end;
            /** The internal start clock */
            omni::chrono::tick_t m_init;
            /** Determines of the current stopwatch is running (start called but not stop) */
            volatile bool m_isrun;
            /** Determines if the stopwatch has been started and not reset */
            volatile bool m_isstrt;
    };
}

#endif // OMNI_STOPWATCH_HPP
