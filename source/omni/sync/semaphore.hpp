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
#if defined(OMNI_SAFE_SEMAPHORE)
    #include <omni/sync/lock.hpp>
#endif

namespace omni {
    namespace sync {
        class semaphore
        {
            public:
                semaphore();
                explicit semaphore(unsigned long maxent);
                explicit semaphore(unsigned long maxent, bool lock1st);
                ~semaphore(); // shouldn't inherit
                const omni::sync::semaphore_t handle() const;
                unsigned long locked() const;
                unsigned long max_ent() const;
                unsigned long open() const;
                inline unsigned long release() { return this->release(1); }
                unsigned long release(unsigned long count);
                unsigned long release_all();
                bool wait();
                bool wait(unsigned long timeout_ms);
                bool trywait();
                // TODO: bool wait(omni::timespan &t); when omni::timespan complete
                bool operator==(const omni::sync::semaphore& o) const;
                bool operator!=(const omni::sync::semaphore& o) const;
                
                OMNI_MEMBERS_FW(omni::sync::semaphore) // disposing,name,type(),hash()
                
            private:
                // defined but not implemented, shouldn't be copied
                semaphore(const omni::sync::semaphore& cp); // = delete;
                omni::sync::semaphore& operator=(const omni::sync::semaphore& other); // = delete;
                
                // Functions
                void _init(unsigned long maxent);
                void _dispose();

                // Members
                unsigned long m_cnt;
                unsigned long m_max;
                omni::sync::semaphore_t m_sem;
                #if defined(OMNI_SAFE_SEMAPHORE)
                    mutable omni::sync::mutex_t m_mtx;
                #endif
        };
    }
}

#endif // OMNI_SEMAPHORE_HPP
