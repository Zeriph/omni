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
#include <omni/sync/semaphore.hpp>
#include <omni/chrono/stopwatch.hpp> // for the wait timeout
#include <omni/system.hpp> // OMNI_GLE_PRNT
#include <omni/exception.hpp>

#if defined(OMNI_SAFE_SEMAPHORE)
    #define OMNI_SAFE_SEM_MILST_FW , m_mtx()
    #define OMNI_SAFE_SEM_INIT_FW omni::sync::mutex_init(this->m_mtx);
    #define OMNI_SAFE_SEM_DTOR_FW omni::sync::mutex_destroy(this->m_mtx);
    #define OMNI_SAFE_SEM_LOCK_FW omni::sync::mutex_lock(this->m_mtx);
    #define OMNI_SAFE_SEM_UNLOCK_FW omni::sync::mutex_unlock(this->m_mtx);
    #define OMNI_SAFE_SEM_ALOCK_FW omni::sync::scoped_lock<omni::sync::mutex_t> smal(&this->m_mtx);
    #define OMNI_SAFE_SEM_EQU_FW(o) (&this->m_mtx == &o.m_mtx) &&
#else
    #define OMNI_SAFE_SEM_MILST_FW
    #define OMNI_SAFE_SEM_INIT_FW
    #define OMNI_SAFE_SEM_DTOR_FW
    #define OMNI_SAFE_SEM_LOCK_FW
    #define OMNI_SAFE_SEM_UNLOCK_FW
    #define OMNI_SAFE_SEM_ALOCK_FW
    #define OMNI_SAFE_SEM_EQU_FW(o)
#endif

omni::sync::semaphore::semaphore() :
    OMNI_CTOR_FW(omni::sync::semaphore)
    m_cnt(0),
    m_max(),
    m_sem()
    OMNI_SAFE_SEM_MILST_FW
{
    this->_init(5);
}

omni::sync::semaphore::semaphore(uint32_t maxent) :
    OMNI_CTOR_FW(omni::sync::semaphore)
    m_cnt(0),
    m_max(),
    m_sem()
    OMNI_SAFE_SEM_MILST_FW
{
    this->_init(maxent);
}

omni::sync::semaphore::semaphore(uint32_t maxent, bool lock1st) :
    OMNI_CTOR_FW(omni::sync::semaphore)
    m_cnt(0),
    m_max(),
    m_sem()
    OMNI_SAFE_SEM_MILST_FW
{
    this->_init(maxent);
    if (lock1st) { this->wait(); }
}

omni::sync::semaphore::~semaphore()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    this->_dispose();
    OMNI_D5_FW("destroyed");
    OMNI_CATCH_FW
}

omni::sync::semaphore_t omni::sync::semaphore::handle() const
{
    return this->m_sem;
}

uint32_t omni::sync::semaphore::locked() const
{
    OMNI_SAFE_SEM_ALOCK_FW
    return this->m_cnt;
}

uint32_t omni::sync::semaphore::max_ent() const
{
    OMNI_SAFE_SEM_ALOCK_FW
    return this->m_max;
}

uint32_t omni::sync::semaphore::open() const
{
    OMNI_SAFE_SEM_ALOCK_FW
    return (this->m_max - this->m_cnt);
}

uint32_t omni::sync::semaphore::release_all()
{
    OMNI_SAFE_SEM_LOCK_FW
    uint32_t cnt = this->m_cnt;
    OMNI_SAFE_SEM_UNLOCK_FW
    return this->release(cnt);
}

uint32_t omni::sync::semaphore::release(uint32_t rcount)
{
    OMNI_SAFE_SEM_ALOCK_FW
    uint32_t pcnt = this->m_cnt;
    if (rcount == 0 || rcount > pcnt) {
        OMNI_ERR_RETV_FW("an invalid release count was specified", omni::exceptions::invalid_release_count(), 0)
    }
    #if defined(OMNI_OS_WIN)
        if (::ReleaseSemaphore(this->m_sem, rcount, NULL) == 0) {
            OMNI_ERRV_RETV_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT, omni::exceptions::semaphore_system_exception(OMNI_GLE_PRNT), 0)
        } else {
            this->m_cnt -= rcount;
        }
    #else
        for (uint32_t i = rcount; i > 0; --i) {
            #if defined(OMNI_OS_APPLE)
                if (::semaphore_signal(this->m_sem) != KERN_SUCCESS)
            #else
                if (::sem_post(&this->m_sem) == -1)
            #endif
            {
                OMNI_ERRV_RETV_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT, omni::exceptions::semaphore_system_exception(OMNI_GLE_PRNT), 0)
            } else {
                --this->m_cnt;
            }
        }
    #endif
    OMNI_DV3_FW("new count of ", this->m_cnt);
    return pcnt; // return old count
}

bool omni::sync::semaphore::wait()
{
    bool aq = false;
    #if defined(OMNI_OS_WIN)
        switch(::WaitForSingleObject(this->m_sem, INFINITE)) {
            case WAIT_OBJECT_0: aq = true; break; // 0x00000000L
            #if defined(OMNI_DBG_L3)
                // If debug isn't enabled the following flags aren't relevant to this context
                // WAIT_FAILED (0xFFFFFFFF) is something to note, but in this context, it has not effect
                case WAIT_FAILED: OMNI_DBGEV("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT); break;
                OMNI_DSW_FW(WAIT_ABANDONED); // 0x00000080L
                OMNI_DSW_FW(WAIT_TIMEOUT); // 0x00000102L
            #endif
            default: break;
        }
    #else
        #if defined(OMNI_OS_APPLE)
            if (::semaphore_wait(this->m_sem) == KERN_SUCCESS)
        #else
            if (::sem_wait(&this->m_sem) != -1)
        #endif
        { aq = true; }
        #if defined(OMNI_DBG_L3)
            else { OMNI_DV3_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT); }
        #endif
    #endif
    if (aq) {
        OMNI_SAFE_SEM_LOCK_FW
        ++this->m_cnt;
        OMNI_DV4_FW("new count of ", this->m_cnt);
        OMNI_SAFE_SEM_UNLOCK_FW
    }
    return aq;
}

bool omni::sync::semaphore::wait(uint32_t timeout_ms)
{
    bool aq = false;
    #if defined(OMNI_OS_WIN)
        switch(::WaitForSingleObject(this->m_sem, timeout_ms)) {
            case WAIT_OBJECT_0: aq = true; break; // 0x00000000L
            #if defined(OMNI_DBG_L3)
                case WAIT_FAILED: OMNI_DV3_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT); break;
                OMNI_DSW_FW(WAIT_ABANDONED);
                OMNI_DSW_FW(WAIT_TIMEOUT);
            #endif
            default: break;
        }
    #elif defined(OMNI_OS_APPLE)
        mach_timespec_t tm;
        if (timeout_ms > 0) {
            if (timeout_ms >= 1000) { tm.tv_sec = (timeout_ms / 1000); }
            tm.tv_nsec = ((timeout_ms % 1000) * 1000);
        }
        switch(::semaphore_timedwait(this->m_sem, tm)) {
            case KERN_SUCCESS:
                aq = true; break;
            #if defined(OMNI_DBG_L3)
                OMNI_DSW_FW(KERN_OPERATION_TIMED_OUT);
            #endif
            default:
                OMNI_DV3_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT);
                break;
        }
    #else
        if (timeout_ms == 0) {
            if (::sem_trywait(&this->m_sem) == 0) { aq = true; }
            #if defined(OMNI_DBG_L3)
                else { OMNI_DV3_FW("a system error occurred on the semaphore object : ", OMNI_GLE_PRNT); }
            #endif
        } else {
            omni::chrono::tick_t start = omni::chrono::monotonic_tick();
            do {
                if (::sem_trywait(&this->m_sem) == 0) {
                    aq = true;
                    break;
                }
                #if defined(OMNI_DBG_L5) // normally L3 level, but inside loop == l5
                    else { OMNI_DV3_FW("a system error occurred on the semaphore object : ", OMNI_GLE_PRNT); }
                #endif
            } while (omni::chrono::elapsed_ms(start) <= timeout_ms);
        }
    #endif
    if (aq) {
        OMNI_SAFE_SEM_LOCK_FW
        ++this->m_cnt;
        OMNI_DV3_FW("new count of ", this->m_cnt);
        OMNI_SAFE_SEM_UNLOCK_FW
    }
    return aq;
}

bool omni::sync::semaphore::wait(const omni::chrono::unsigned_timespan& span)
{
    return this->wait(static_cast<uint32_t>(span.total_milliseconds()));
}

bool omni::sync::semaphore::trywait()
{
    return this->wait(0);
}

bool omni::sync::semaphore::operator==(const omni::sync::semaphore& o) const
{
    if (this == &o) { return true; }
    uint32_t ocnt = o.locked();
    OMNI_SAFE_SEM_ALOCK_FW
    return (OMNI_SAFE_SEM_EQU_FW(o)
        this->m_cnt == ocnt &&
        this->m_max == o.m_max &&
        &this->m_sem == &o.m_sem)
        OMNI_EQUAL_FW(o);
}

bool omni::sync::semaphore::operator!=(const omni::sync::semaphore& o) const
{
    return !(*this == o);
}

///////// start private methods /////////

void omni::sync::semaphore::_dispose()
{
    OMNI_SAFE_SEM_LOCK_FW
    bool await = (this->m_cnt > 0);
    OMNI_SAFE_SEM_UNLOCK_FW
    OMNI_SAFE_SEM_DTOR_FW
    if (await) {
        OMNI_ERR_FW("the semaphore has active waits on call to dispose", omni::exceptions::active_wait_exception())
    }
#if defined(OMNI_OS_WIN)
    if (::CloseHandle(this->m_sem) == 0)
#elif defined(OMNI_OS_APPLE)
    if (::semaphore_destroy(::mach_task_self(), this->m_sem) != KERN_SUCCESS)
#else
    if (::sem_destroy(&this->m_sem) == -1)
#endif
    {
        OMNI_ERRV_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT, omni::exceptions::semaphore_system_exception(OMNI_GLE_PRNT))
    }
}

void omni::sync::semaphore::_init(uint32_t maxent)
{
#if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
    omni::chrono::monotonic::initialize();
#endif
    OMNI_SAFE_SEM_INIT_FW
#if defined(OMNI_OS_WIN)
    this->m_sem = ::CreateSemaphore(NULL, maxent, maxent, NULL);
    if (this->m_sem == NULL)
#elif defined(OMNI_OS_APPLE)
    if (::semaphore_create(::mach_task_self(), &this->m_sem, SYNC_POLICY_FIFO, static_cast<int>(maxent)) != KERN_SUCCESS)
#else
    if (::sem_init(&this->m_sem, 0, static_cast<int>(maxent)) == -1)
#endif
    {
        // this will hit as well if 'maxent' > SEM_VALUE_MAX
        OMNI_ERRV_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT, omni::exceptions::semaphore_system_exception(OMNI_GLE_PRNT))
    }
    this->m_max = maxent;
    OMNI_D5_FW("created");
}
