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
#include <omni/sync/conditional.hpp>
#include <omni/sync/scoped_lock.hpp>
#include <omni/system.hpp> // OMNI_GLE_PRNT
#include <omni/exception.hpp>

omni::sync::conditional::conditional() :
    OMNI_CTOR_FW(omni::sync::conditional)
    m_signal(),
    m_wait(),
    m_waitreq(0),
    m_signaled(false)
{
    this->_init();
}

omni::sync::conditional::conditional(bool initially_signaled) :
    OMNI_CTOR_FW(omni::sync::conditional)
    m_signal(),
    m_wait(),
    m_waitreq(0),
    m_signaled(false)
{
    this->_init();
    if (initially_signaled) { this->signal(); }
}

omni::sync::conditional::~conditional()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    omni::sync::mutex_lock(this->m_wait);
    bool await = this->m_waitreq > 0;
    omni::sync::mutex_unlock(this->m_wait);
    if (await) {
        OMNI_ERR_FW("the conditional has active waits on call to dispose", omni::exceptions::active_wait_exception())
    }
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
            ::CloseHandle(this->m_signal);
            this->m_signal = 0;
        #endif
    #else
        int ret = ::pthread_cond_destroy(&this->m_signal);
        if (ret != 0) {
            OMNI_ERRV_FW("An error occurred destroying the conditional: ", ret, omni::exceptions::conditional_exception(ret))
        }
    #endif
    omni::sync::mutex_destroy(this->m_wait);
    OMNI_CATCH_FW
}

void omni::sync::conditional::broadcast()
{
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
            omni::sync::mutex_lock(this->m_wait);
            uint32_t wreq = this->m_waitreq+1;
            this->m_signaled = true;
            while (--wreq > 0) {
                if (::SetEvent(this->m_signal) == 0) {
                    omni::sync::mutex_unlock(this->m_wait);
                    OMNI_ERRV_RET_FW("An error occurred on the conditional: ", OMNI_GLE, omni::exceptions::conditional_exception(OMNI_GLE))
                }
                omni::sync::mutex_unlock(this->m_wait);
                omni::sync::yield_thread();
                omni::sync::mutex_lock(this->m_wait);
            }
            omni::sync::mutex_unlock(this->m_wait);
        #else
            omni::sync::mutex_lock(this->m_wait);
            this->m_signaled = true;
            ::WakeAllConditionVariable(&this->m_signal);
            omni::sync::mutex_unlock(this->m_wait);
        #endif
    #else
        omni::sync::mutex_lock(this->m_wait);
        this->m_signaled = true;
        int ret = ::pthread_cond_broadcast(&this->m_signal);
        omni::sync::mutex_unlock(this->m_wait);
        if (ret != 0) {
            OMNI_ERRV_FW("An error occurred on the conditional: ", ret, omni::exceptions::conditional_exception(ret))
        }
    #endif
}

void omni::sync::conditional::reset()
{
    omni::sync::mutex_lock(this->m_wait);
    this->m_signaled = false;
    #if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
        ::ResetEvent(this->m_signal);
    #endif
    omni::sync::mutex_unlock(this->m_wait);
}

void omni::sync::conditional::signal()
{
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
            omni::sync::mutex_lock(this->m_wait);
            this->m_signaled = true;
            if (::SetEvent(this->m_signal) == 0) {
                omni::sync::mutex_unlock(this->m_wait);
                OMNI_ERRV_RET_FW("An error occurred on the conditional: ", OMNI_GLE, omni::exceptions::conditional_exception(OMNI_GLE))
            }
            omni::sync::mutex_unlock(this->m_wait);
        #else
            omni::sync::mutex_lock(this->m_wait);
            this->m_signaled = true;
            ::WakeConditionVariable(&this->m_signal);
            omni::sync::mutex_unlock(this->m_wait);
        #endif
    #else
        omni::sync::mutex_lock(this->m_wait);
        this->m_signaled = true;
        int ret = ::pthread_cond_signal(&this->m_signal);
        omni::sync::mutex_unlock(this->m_wait);
        if (ret != 0) {
            OMNI_ERRV_FW("An error occurred on the conditional: ", ret, omni::exceptions::conditional_exception(ret))
        }
    #endif
}

bool omni::sync::conditional::wait()
{
    omni::sync::mutex_lock(this->m_wait);
    if (this->m_signaled) {
        omni::sync::mutex_unlock(this->m_wait);
        return false;
    }
    ++this->m_waitreq;
    omni::sync::mutex_unlock(this->m_wait);
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
            switch (::WaitForSingleObject(this->m_signal, INFINITE)) {
                case WAIT_OBJECT_0: { // 0x00000000L
                    omni::sync::mutex_lock(this->m_wait);
                    if (this->m_signaled) { --this->m_waitreq; }
                    omni::sync::mutex_unlock(this->m_wait);
                    return true;
                } break;
                #if defined(OMNI_DBG_L3)
                    case WAIT_FAILED: OMNI_DV3_FW("a system error occurred on the conditional object: ", OMNI_GLE_PRNT); break;
                    OMNI_DSW_FW(WAIT_ABANDONED); // 0x00000080L
                    OMNI_DSW_FW(WAIT_TIMEOUT); // 0x00000102L
                #endif
                default: break;
            }
        #else
            DWORD ret = 0;
            while (!this->signaled()) {
                omni::sync::scoped_lock<omni::sync::mutex_t> mlock(&this->m_wait);
                if (!::SleepConditionVariableCS(&this->m_signal, &this->m_wait, INFINITE)) {
                    #if defined(OMNI_DBG_L3)
                    OMNI_DV3_FW("a system error occurred on the conditional object: ", OMNI_GLE);
                    #endif
                }
                // spurious wake up?
                if (!this->m_signaled) { continue; }
                --this->m_waitreq;
                return true;
            }
        #endif
    #else
        int ret = 0;
        while (!this->signaled()) {
            omni::sync::scoped_lock<omni::sync::mutex_t> mlock(&this->m_wait);
            ret = ::pthread_cond_wait(&this->m_signal, &this->m_wait);
            if (ret == 0) {
                // spurious wake up?
                if (!this->m_signaled) { continue; }
                --this->m_waitreq;
                return true;
            }
            #if defined(OMNI_DBG_L3)
            else { OMNI_DV3_FW("a system error occurred on the conditional object: ", ret); }
            #endif
        }
    #endif
    omni::sync::mutex_lock(this->m_wait);
    --this->m_waitreq;
    omni::sync::mutex_unlock(this->m_wait);
    return false;
}

bool omni::sync::conditional::wait(uint32_t timeout_ms)
{
    omni::sync::mutex_lock(this->m_wait);
    if (this->m_signaled) {
        omni::sync::mutex_unlock(this->m_wait);
        return false;
    }
    ++this->m_waitreq;
    omni::sync::mutex_unlock(this->m_wait);
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
            switch (::WaitForSingleObject(this->m_signal, timeout_ms)) {
                case WAIT_OBJECT_0: { // 0x00000000L
                    omni::sync::mutex_lock(this->m_wait);
                    if (this->m_signaled) { --this->m_waitreq; }
                    omni::sync::mutex_unlock(this->m_wait);
                    return true;
                } break;
                #if defined(OMNI_DBG_L3)
                    case WAIT_FAILED: OMNI_DBGEV("a system error occurred on the conditional object: ", OMNI_GLE_PRNT); break;
                    OMNI_DSW_FW(WAIT_ABANDONED); // 0x00000080L
                    OMNI_DSW_FW(WAIT_TIMEOUT); // 0x00000102L
                #endif
                default: break;
            }
        #else
            DWORD ret = 0;
            while (!this->signaled()) {
                omni::sync::scoped_lock<omni::sync::mutex_t> mlock(&this->m_wait);
                if (!::SleepConditionVariableCS(&this->m_signal, &this->m_wait, timeout_ms)) {
                    ret = OMNI_GLE;
                    if (ret == ERROR_TIMEOUT) { // time out while waiting
                        --this->m_waitreq;
                        return false;
                    }
                    #if defined(OMNI_DBG_L3)
                    else { OMNI_DV3_FW("a system error occurred on the conditional object: ", ret); }
                    #endif
                }
                // spurious wake up?
                if (!this->m_signaled) { continue; }
                --this->m_waitreq;
                return true;
            }
        #endif
    #else
        int ret = 0;
        struct timespec tm;
        #if defined(OMNI_OS_APPLE)
            struct timeval tv;
            if (::gettimeofday(&tv, NULL) != 0) {
                OMNI_ERRV_RETV_FW("An error occurred getting the clock time: ", errno, omni::exceptions::clock_exception(errno), false)
            }
            tm.tv_sec = tv.tv_sec + 0;
            tm.tv_nsec = 0;
        #else
            if (::clock_gettime(CLOCK_REALTIME, &tm) != 0) {
                OMNI_ERRV_RETV_FW("An error occurred getting the clock time: ", errno, omni::exceptions::clock_exception(errno), false)
            }
        #endif
        if (timeout_ms > 0) {
            if (timeout_ms >= 1000) { tm.tv_sec += (timeout_ms / 1000); }
            tm.tv_nsec += ((timeout_ms % 1000) * 1000);
        }
        while (!this->signaled()) {
            omni::sync::scoped_lock<omni::sync::mutex_t> mlock(&this->m_wait);
            ret = ::pthread_cond_timedwait(&this->m_signal, &this->m_wait, &tm);
            if (ret == 0) {
                // spurious wake up?
                if (!this->m_signaled) { continue; }
                --this->m_waitreq;
                return true;
            } else if (ret == ETIMEDOUT) { // time out while waiting
                --this->m_waitreq;
                return false;
            }
            #if defined(OMNI_DBG_L3)
            else { OMNI_DV3_FW("a system error occurred on the conditional object: ", ret); }
            #endif
        }
    #endif
    omni::sync::mutex_lock(this->m_wait);
    --this->m_waitreq;
    omni::sync::mutex_unlock(this->m_wait);
    return false;
}

bool omni::sync::conditional::operator==(const omni::sync::conditional& o)
{
    if (this == &o) { return true; }
    omni::sync::scoped_lock<omni::sync::mutex_t> mlock(&this->m_wait);
    omni::sync::scoped_lock<omni::sync::mutex_t> mlock2(&o.m_wait);
    return (this->m_signaled == o.m_signaled &&
           &this->m_signal == &o.m_signal &&
           this->m_waitreq == o.m_waitreq)
           OMNI_EQUAL_FW(o);
}

bool omni::sync::conditional::operator!=(const omni::sync::conditional& o)
{
    return !(*this == o);
}

///////// start private methods /////////

void omni::sync::conditional::_init()
{
    omni::sync::mutex_init(this->m_wait);
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
            // NULL security attributes, auto-reset event, initially non-signalled, no name
            this->m_signal = ::CreateEvent(NULL, FALSE, FALSE, NULL);
            // auto-reset == FALSE gives the same functionality as a pthread_cond_t
            if (this->m_signal == NULL) {
                OMNI_ERRV_FW("The event could not be created: ", OMNI_GLE, omni::exceptions::conditional_exception(OMNI_GLE))
            }
        #else
            ::InitializeConditionVariable(&this->m_signal);
        #endif
    #else
        int ret = ::pthread_cond_init(&this->m_signal, NULL);
        if (ret != 0) {
            OMNI_ERRV_FW("The event could not be created: ", ret, omni::exceptions::conditional_exception(ret))
        }
    #endif
}
