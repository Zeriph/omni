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
#if !defined(OMNI_LOCK_T_HPP)
#define OMNI_LOCK_T_HPP 1
#include <omni/defs/global.hpp>

#if defined(OMNI_OS_WIN)
    #define OMNI_SPIN_LOCK_T volatile long 
    #define OMNI_SEM_T HANDLE
    // Critical sections do not enter the kernel
    // CreateMutex is for "named" mutexes, crit_sec is for thread safe code
    #define OMNI_MUTEX_T    CRITICAL_SECTION
    #if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
        #define OMNI_COND_T HANDLE
    #else
        #if defined(OMNI_OS_WIN8)
            #include <synchapi.h>
        #endif
        #define OMNI_COND_T CONDITION_VARIABLE
    #endif
#elif defined(OMNI_OS_APPLE)
    #include <libkern/OSAtomic.h>
    #include <mach/mach_init.h>
    #include <mach/task.h>
    #include <mach/semaphore.h>
    #include <mach/sync_policy.h>
    #include <mach/mach_error.h>
    #include <mach/clock_types.h> 
    #include <pthread.h>
    #if defined(OMNI_OS_MACOS)
        #include <os/lock.h>
        #define OMNI_SPIN_LOCK_T os_unfair_lock_t
    #else
        #define OMNI_SPIN_LOCK_T OSSpinLock
    #endif
    #define OMNI_SEM_T semaphore_t
    #define OMNI_MUTEX_T pthread_mutex_t
    #define OMNI_COND_T pthread_cond_t
#else
    #include <pthread.h>
    #include <errno.h>
    #include <semaphore.h>
    #include <pthread.h>
    #define OMNI_SPIN_LOCK_T pthread_spinlock_t
    #define OMNI_SEM_T sem_t
    #define OMNI_MUTEX_T pthread_mutex_t
    #define OMNI_COND_T pthread_cond_t
#endif

namespace omni {
    namespace sync {
        /** Defines the basic mutex type */
        typedef OMNI_MUTEX_T mutex_t;
        /** Defines the basic spin lock type */
        typedef OMNI_SPIN_LOCK_T spin_lock_t;
        /** Defines the basic semaphore type */
        typedef OMNI_SEM_T semaphore_t;
        /** Defines the basic conditional type */
        typedef OMNI_COND_T cond_t;
    }
}

#endif // OMNI_LOCK_T_HPP
