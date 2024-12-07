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
#include <omni/sync/binary_semaphore.hpp>
#include <omni/system.hpp> // OMNI_GLE_PRNT
#include <omni/exception.hpp>

omni::sync::binary_semaphore::binary_semaphore() :
    OMNI_CTOR_FW(omni::sync::binary_semaphore)
    m_lokd(0),
    m_sem()
{
    this->_init();
}

omni::sync::binary_semaphore::binary_semaphore(bool initialy_owned) :
    OMNI_CTOR_FW(omni::sync::binary_semaphore)
    m_lokd(0),
    m_sem()
{
    this->_init();
    if (initialy_owned) { this->lock(); }
}

omni::sync::binary_semaphore::~binary_semaphore()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    this->_dispose();
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

omni::sync::semaphore_t omni::sync::binary_semaphore::handle() const
{
    return this->m_sem;
}

bool omni::sync::binary_semaphore::locked() const
{
    return (this->m_lokd == 1);
}

bool omni::sync::binary_semaphore::lock()
{
    #if defined(OMNI_OS_WIN)
        switch(::WaitForSingleObject(this->m_sem, INFINITE)) {
            case WAIT_OBJECT_0: // 0x00000000L
                this->m_lokd = 1;
                return true; break;
            #if defined(OMNI_DBG_L3)
                // If debug is not enabled the following flags are not relevant to this context
                // WAIT_FAILED (0xFFFFFFFF) is something to note, but in this context, it has no effect
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
        { this->m_lokd = 1; return true; }
        #if defined(OMNI_DBG_L3)
            else { OMNI_DV3_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT); }
        #endif
    #endif
    this->m_lokd = 0;
    return false;
}

bool omni::sync::binary_semaphore::lock(uint32_t timeout_ms)
{
    #if defined(OMNI_OS_WIN)
        switch(::WaitForSingleObject(this->m_sem, timeout_ms)) {
            case WAIT_OBJECT_0: // 0x00000000L
                this->m_lokd = 1;
                return true; break;
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
                this->m_lokd = 1;
                return true; break;
            #if defined(OMNI_DBG_L3)
                OMNI_DSW_FW(KERN_OPERATION_TIMED_OUT);
            #endif
            default: OMNI_DV3_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT); break;
        }
    #else
        if (timeout_ms == 0) {
            if (::sem_trywait(&this->m_sem) == 0) {
                this->m_lokd = 1;
                return true;
            }
            #if defined(OMNI_DBG_L3)
                else { OMNI_DV3_FW("a system error occurred on the semaphore object : ", OMNI_GLE_PRNT); }
            #endif
        } else {
            omni::chrono::tick_t start = omni::chrono::monotonic_tick();
            do {
                if (::sem_trywait(&this->m_sem) == 0) {
                    this->m_lokd = 1;
                    return true;
                }
                #if defined(OMNI_DBG_L3)
                    else { OMNI_DV3_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT); }
                #endif
            } while (omni::chrono::elapsed_ms(start) <= timeout_ms);
        }
    #endif
    this->m_lokd = 0;
    return false;
}

bool omni::sync::binary_semaphore::unlock()
{
    if (this->m_lokd == 0) {
        OMNI_ERR_RETV_FW("the binary semaphore is not locked on call to release", omni::exceptions::semaphore_release_exception(), true)
    }
#if defined(OMNI_OS_WIN)
    if (::ReleaseSemaphore(this->m_sem, 1, NULL) != 0)
#elif defined(OMNI_OS_APPLE)
    if (::semaphore_signal(this->m_sem) == KERN_SUCCESS)
#else
    if (::sem_post(&this->m_sem) != -1)
#endif
    {
        this->m_lokd = 0;
        return true;
    } else {
        OMNI_ERRV_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT, omni::exceptions::semaphore_system_exception(OMNI_GLE_PRNT));
    }
    return false;
}

bool omni::sync::binary_semaphore::trylock()
{
    return this->lock(0);
}

bool omni::sync::binary_semaphore::operator==(const omni::sync::binary_semaphore& o) const
{
    if (this == &o) { return true; }
    return (this->m_lokd == o.m_lokd &&
            &this->m_sem == &o.m_sem)
            OMNI_EQUAL_FW(o);
}

bool omni::sync::binary_semaphore::operator!=(const omni::sync::binary_semaphore& o) const
{
    return !(*this == o);
}

///////// start private methods /////////

void omni::sync::binary_semaphore::_dispose()
{
    // only release if we are locked
    if (this->m_lokd == 1) {
        OMNI_ERR_FW("the binary semaphore is locked on call to dispose", omni::exceptions::active_wait_exception())
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

void omni::sync::binary_semaphore::_init()
{
#if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
    omni::chrono::monotonic::initialize();
#endif
#if defined(OMNI_OS_WIN)
    this->m_sem = ::CreateSemaphore(NULL, 1, 1, NULL);
    if (this->m_sem == NULL)
#elif defined(OMNI_OS_APPLE)
    if (::semaphore_create(::mach_task_self(), &this->m_sem, SYNC_POLICY_FIFO, 1) != KERN_SUCCESS)
#else
    if (::sem_init(&this->m_sem, 0, 1) == -1)
#endif
    {
        // this will hit as well if maxent > SEM_VALUE_MAX
        OMNI_ERRV_FW("a system error occurred on the semaphore object: ", OMNI_GLE_PRNT, omni::exceptions::semaphore_system_exception(OMNI_GLE_PRNT))
    }
    OMNI_D5_FW("created");
}
