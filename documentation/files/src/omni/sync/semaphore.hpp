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
#if !defined(OMNI_SEMAPHORE_HPP)
#define OMNI_SEMAPHORE_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/lock_t.hpp>
#include <omni/chrono/span.hpp>
#if defined(OMNI_SAFE_SEMAPHORE)
    #include <omni/sync/lock.hpp>
#endif

namespace omni {
    namespace sync {
        class semaphore
        {
            public:
                semaphore();
                OMNI_EXPLICIT semaphore(uint32_t maxent);
                semaphore(uint32_t maxent, bool lock1st);
                ~semaphore(); // should not inherit
                omni::sync::semaphore_t handle() const;
                uint32_t locked() const;
                uint32_t max_ent() const;
                uint32_t open() const;
                inline uint32_t release() { return this->release(1); }
                uint32_t release(uint32_t count);
                uint32_t release_all();
                bool wait();
                bool wait(uint32_t timeout_ms);
                bool wait(const omni::chrono::unsigned_span_t& span);
                bool trywait();
                bool operator==(const omni::sync::semaphore& o) const;
                bool operator!=(const omni::sync::semaphore& o) const;
                
                OMNI_MEMBERS_FW(omni::sync::semaphore) // disposing,name,type(),hash()
                
            private:
                // defined but not implemented, should not be copied
                semaphore(const omni::sync::semaphore& cp); // = delete;
                omni::sync::semaphore& operator=(const omni::sync::semaphore& other); // = delete;
                
                // Functions
                void _init(uint32_t maxent);
                void _dispose();

                // Members
                uint32_t m_cnt;
                uint32_t m_max;
                omni::sync::semaphore_t m_sem;
                #if defined(OMNI_SAFE_SEMAPHORE)
                    mutable omni::sync::mutex_t m_mtx;
                #endif
        };
    }
}

#endif // OMNI_SEMAPHORE_HPP
