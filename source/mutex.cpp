/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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
#include <omni/sync/mutex.hpp>

// DEV_NOTE: reason for the #def calls for mutex lock/unlock/etc. is to avoid extra function calls to omni::sync::mutex_init/lock/etc.
// which are just function wrappers for the #def values

#if defined(OMNI_MUTEX_OWNER)
    #define OMNI_MOLIST_FW , m_owner()
    #if defined(OMNI_OS_WIN)
        #define OMNI_MOCALL_FW ::GetCurrentThreadId()
    #else
        #define OMNI_MOCALL_FW ::pthread_self()
    #endif
    #if defined(OMNI_THROW)
        #define OMNI_MOERR_FW throw omni::exceptions::invalid_thread_owner();
    #else
        #if defined(OMNI_TERMINATE)
            #define OMNI_MOERR_FW OMNI_TERMINATE;
        #else
            #define OMNI_MOERR_FW
        #endif
    #endif
    #define OMNI_MOCHK_FW if (this->m_owner != OMNI_MOCALL_FW) { OMNI_MOERR_FW }
    #define OMNI_MOGET_FW this->m_owner = OMNI_MOCALL_FW;
#else
    #define OMNI_MOLIST_FW
    #define OMNI_MOCHK_FW 
    #define OMNI_MOGET_FW 
#endif
#if defined OMNI_SAFE_MUTEX
    #define OMNI_SAFE_XMTX_FW       , m_imtx()
    #define OMNI_SAFE_XALOCK_FW     omni::sync::scoped_lock<omni::sync::mutex_t> amtimtx(&this->m_imtx);
    #define OMNI_SAFE_XINIT_FW      omni::sync::mutex_init(this->m_imtx);
    #define OMNI_SAFE_XLOCK_FW      omni::sync::mutex_lock(this->m_imtx);
    #define OMNI_SAFE_XUNLOCK_FW    omni::sync::mutex_unlock(this->m_imtx);
    #define OMNI_SAFE_XDTOR_FW      omni::sync::mutex_destroy(this->m_imtx);
#else
    #define OMNI_SAFE_XMTX_FW
    #define OMNI_SAFE_XALOCK_FW
    #define OMNI_SAFE_XINIT_FW 
    #define OMNI_SAFE_XLOCK_FW
    #define OMNI_SAFE_XUNLOCK_FW
    #define OMNI_SAFE_XDTOR_FW
#endif

omni::sync::mutex::mutex() : 
    OMNI_CTOR_FW(omni::sync::mutex)
    m_lokd(0), m_mtx()
    OMNI_SAFE_XMTX_FW
    OMNI_MOLIST_FW
{
    OMNI_SAFE_XINIT_FW
    omni::sync::mutex_init(this->m_mtx);
    OMNI_D5_FW("created");
}

omni::sync::mutex::mutex(bool initialy_owned) : 
    OMNI_CTOR_FW(omni::sync::mutex)
    m_lokd(0), m_mtx()
    OMNI_SAFE_XMTX_FW
    OMNI_MOLIST_FW
{
    OMNI_SAFE_XINIT_FW
    omni::sync::mutex_init(this->m_mtx);
    OMNI_D5_FW("created");
    if (initialy_owned) { this->lock(); }
}

omni::sync::mutex::~mutex()
{
    OMNI_DTOR_FW
    if (this->locked()) {
        /* DEV_NOTE: the sync objects (mutex/semaphore/etc.) will not unlock on destruction
        since that would assume the user wants this. If they want an 'auto' mutex, they can
        use the omni::sync::auto_lock */
        OMNI_TERMINATE_FW("mutex is locked on destruction")
    }
    OMNI_TRY_FW
    omni::sync::mutex_destroy(this->m_mtx);
    OMNI_CATCH_FW
    OMNI_SAFE_XDTOR_FW
    OMNI_D5_FW("destroyed");
}

const omni::sync::mutex_t omni::sync::mutex::handle() const
{
    OMNI_SAFE_XALOCK_FW
    return this->m_mtx;
}

bool omni::sync::mutex::locked() const
{
    OMNI_SAFE_XALOCK_FW
    return (this->m_lokd > 0);
}

void omni::sync::mutex::lock()
{
    OMNI_D4_FW("retrieving lock");
    omni::sync::mutex_lock(this->m_mtx);
    OMNI_SAFE_XLOCK_FW
    OMNI_MOGET_FW
    ++this->m_lokd;
    OMNI_SAFE_XUNLOCK_FW
    OMNI_D4_FW("lock acquired");
}

bool omni::sync::mutex::lock(std::size_t timeout_ms)
{
    if (timeout_ms == 0) { return this->trylock(); }
    omni::chrono::tick_t start = omni::chrono::monotonic_tick();
    while (omni::chrono::elapsed_ms(start) <= timeout_ms) {
        if (this->trylock()) { return true; }
    }
    return false;
}

void omni::sync::mutex::unlock()
{
    OMNI_SAFE_XALOCK_FW
    // 'undefined' behaviour if 'unlock' on 'non-locked' system mutex
    if (this->m_lokd > 0) {
        // 'undefined' if 'unlock' not from owning thread
        OMNI_MOCHK_FW
        OMNI_D4_FW("unlocking");
        omni::sync::mutex_unlock(this->m_mtx);
        --this->m_lokd;
        OMNI_D4_FW("unlocked");
    } else {
        OMNI_ERR_FW("mutex object is not locked", omni::exceptions::mutex_unlock_exception())
    }
}

bool omni::sync::mutex::trylock()
{
    if (omni::sync::mutex_trylock(this->m_mtx)) {
        OMNI_SAFE_XALOCK_FW
        OMNI_MOGET_FW
        ++this->m_lokd;
        return true;
    }
    return false;
}

bool omni::sync::mutex::operator==(const omni::sync::mutex &o) const
{
    if (this == &o) { return true; }
    OMNI_SAFE_XALOCK_FW
    return (&this->m_mtx == &o.m_mtx &&
            this->m_lokd == o.m_lokd)
            OMNI_EQUAL_FW(o);
}

bool omni::sync::mutex::operator!=(const omni::sync::mutex &o) const
{
    return !(*this == o);
}
