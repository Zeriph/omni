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
#if defined(OMNI_32BIT_STOPWATCH)
    #define OMNI_SW_INT_FW uint32_t
#else
    #define OMNI_SW_INT_FW uint64_t
#endif

namespace omni {
    class stopwatch
    {
        public:
            stopwatch();
            stopwatch(const omni::stopwatch& cp);
            ~stopwatch();

            omni::chrono::unsigned_span_t elapsed() const;
            uint64_t elapsed_us() const;
            uint64_t elapsed_ms() const;
            uint64_t elapsed_s() const;
            bool is_running() const;
            omni::stopwatch& reset();
            omni::stopwatch& restart();
            omni::stopwatch& restart(uint32_t offset_ms);
            omni::stopwatch& start();
            omni::stopwatch& start(uint32_t offset_ms);
            omni::stopwatch& stop();
            void swap(omni::stopwatch& o);
            omni::string_t to_string_t() const;
            std::string to_string() const;
            std::wstring to_wstring() const;
            operator std::string() const { return this->to_string(); }
            operator std::wstring() const { return this->to_wstring(); }
            omni::stopwatch& operator=(const omni::stopwatch& other);
            omni::stopwatch& operator=(bool enable);
            bool operator==(const omni::stopwatch& o) const;
            bool operator!=(const omni::stopwatch& o) const;
            
            OMNI_MEMBERS_FW(omni::stopwatch) // disposing,name,type(),hash()

            OMNI_OSTREAM_FW(omni::stopwatch)
            
        private:
            omni::chrono::tick_t m_end;
            omni::chrono::tick_t m_init;
            volatile OMNI_SW_INT_FW m_status;

            #if defined(OMNI_SAFE_STOPWATCH)
                mutable omni::sync::basic_lock m_mtx;
            #endif

            void _zero();
    };
}

namespace std {
    inline void swap(omni::stopwatch& o1, omni::stopwatch& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_STOPWATCH_HPP
