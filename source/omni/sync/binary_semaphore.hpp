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
#if !defined(OMNI_BINARY_SEMAPHORE_HPP)
#define OMNI_BINARY_SEMAPHORE_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/lock_t.hpp>
#include <omni/types/tick_t.hpp>
#include <omni/chrono/tick.hpp>
#include <omni/sync/auto_lock.hpp>
#include <omni/sync/scoped_lock.hpp>

#if defined(OMNI_32BIT_BINARY_SEMAPHORE)
    #define OMNI_BINSEM_INT_FW uint32_t
#else
    #define OMNI_BINSEM_INT_FW uint64_t
#endif

namespace omni {
    namespace sync {
        class binary_semaphore
        {
            public:
                binary_semaphore();
                OMNI_EXPLICIT binary_semaphore(bool initialy_owned);
                ~binary_semaphore(); // should not inherit
                omni::sync::semaphore_t handle() const;
                bool locked() const;
                bool lock();
                bool lock(uint32_t timeout_ms);
                bool unlock();
                bool trylock();
                bool operator==(const omni::sync::binary_semaphore& o) const;
                bool operator!=(const omni::sync::binary_semaphore& o) const;
                
                OMNI_MEMBERS_FW(omni::sync::binary_semaphore) // disposing,name,type(),hash()
                
            private:
                volatile OMNI_BINSEM_INT_FW m_lokd;
                omni::sync::semaphore_t m_sem;
                
                // defined but not implemented, should not be copied
                binary_semaphore(const omni::sync::binary_semaphore& cp);
                omni::sync::binary_semaphore& operator=(const omni::sync::binary_semaphore& other);
                
                void _init();
                void _dispose();
        };
        
        typedef omni::sync::auto_lock<omni::sync::binary_semaphore> auto_binary_semaphore;
        typedef omni::sync::scoped_lock<omni::sync::binary_semaphore> scoped_binary_semaphore;
    }
}

#endif // OMNI_BINARY_SEMAPHORE_HPP
