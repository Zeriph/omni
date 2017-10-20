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
#include <omni/chrono/sync_timer.hpp>
#include <omni/defs/timer_def.hpp>

#if defined(OMNI_SAFE_SYNC_TIMER)
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_STMQMTX_FW OMNI_SAFE_TCTRMTX_FW
    #define OMNI_TMR_ALOCK_FW    OMNI_TMRALOCK_FW
    #define OMNI_TMR_MLOCK_FW    OMNI_TMRLOCK_FW
    #define OMNI_TMR_ULOCK_FW    OMNI_TMRUNLOCK_FW
#else
    #define OMNI_SAFE_STMQMTX_FW
    #define OMNI_TMR_ALOCK_FW
    #define OMNI_TMR_MLOCK_FW
    #define OMNI_TMR_ULOCK_FW
#endif

#define OMNI_TIMER_T_FW sync_timer
#include <omni/xx/timer.hxx>

omni::chrono::sync_timer::sync_timer() : 
    state_object(),
    tick(),
    OMNI_CTOR_FW(omni::chrono::sync_timer)
    OMNI_SAFE_STMQMTX_FW
    m_thread(OMNI_NULL),
    m_int(100),
    m_auto(true),
    m_isrun(false),
    m_stopreq(false)
{
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::sync_timer::sync_timer(const omni::chrono::sync_timer& cp) : 
    state_object(),
    tick(),
    OMNI_CPCTOR_FW(cp)
    OMNI_SAFE_STMQMTX_FW
    m_thread(OMNI_NULL),
    m_int(),
    m_auto(),
    m_isrun(),
    m_stopreq()
{
    #if defined(OMNI_SAFE_SYNC_TIMER)
        cp.m_mtx.lock();
    #endif
    this->state_object = cp.state_object;
    this->tick = cp.tick;
    this->m_int = cp.m_int;
    this->m_auto = cp.m_auto;
    if (cp.m_isrun && !cp.m_stopreq) { this->start(); }
    #if defined(OMNI_SAFE_SYNC_TIMER)
        cp.m_mtx.unlock();
    #endif
    OMNI_D5_FW("copied");
}

omni::chrono::sync_timer::sync_timer(std::size_t interval_ms) : 
    state_object(),
    tick(),
    OMNI_CTOR_FW(omni::chrono::sync_timer)
    OMNI_SAFE_STMQMTX_FW
    m_thread(OMNI_NULL),
    m_int(interval_ms),
    m_auto(true),
    m_isrun(false),
    m_stopreq(false)
{
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::sync_timer::sync_timer(std::size_t interval_ms, const omni::chrono::timer_delegate& fn) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::sync_timer)
    OMNI_SAFE_STMQMTX_FW
    m_thread(OMNI_NULL),
    m_int(interval_ms),
    m_auto(true),
    m_isrun(false),
    m_stopreq(false)
{
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::sync_timer::sync_timer(std::size_t interval_ms,
                           const omni::chrono::timer_delegate& fn,
                           bool autoreset) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::sync_timer)
    OMNI_SAFE_STMQMTX_FW
    m_thread(OMNI_NULL),
    m_int(interval_ms),
    m_auto(autoreset),
    m_isrun(false),
    m_stopreq(false)
{
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::sync_timer::sync_timer(std::size_t interval_ms,
                           const omni::chrono::timer_delegate& fn,
                           bool autoreset,
                           std::size_t delay) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::sync_timer)
    OMNI_SAFE_STMQMTX_FW
    m_thread(OMNI_NULL),
    m_int(interval_ms),
    m_auto(autoreset),
    m_isrun(false),
    m_stopreq(false)
{
    OMNI_DV5_FW("created with interval of ", this->m_int);
    this->start(delay);
}

omni::chrono::sync_timer& omni::chrono::sync_timer::operator=(const omni::chrono::sync_timer& other)
{
    if (this != &other) {
        this->stop();
        OMNI_ASSIGN_FW(other)
        #if defined(OMNI_SAFE_SYNC_TIMER)
            this->m_mtx.lock();
            other.m_mtx.lock();
        #endif
        bool isrun = other.m_isrun;
        bool stopreq = other.m_stopreq;
        this->m_isrun = false;
        this->m_stopreq = false;
        this->state_object = other.state_object;
        this->tick = other.tick;
        this->m_int = other.m_int;
        this->m_auto = other.m_auto;
        #if defined(OMNI_SAFE_SYNC_TIMER)
            other.m_mtx.unlock();
            this->m_mtx.unlock();
        #endif
        if (isrun && !stopreq) { this->start(); }
    }
    return *this;
}

bool omni::chrono::sync_timer::operator==(const omni::chrono::sync_timer& o) const
{
    if (this == &o) { return true; }
    #if defined(OMNI_SAFE_SYNC_TIMER)
        omni::sync::scoped_lock<omni::sync::basic_lock> mlock(&this->m_mtx);
        omni::sync::scoped_lock<omni::sync::basic_lock> omlock(&o.m_mtx);
    #endif
    return (this->state_object == o.state_object &&
            this->tick == o.tick &&
            (((this->m_thread != OMNI_NULL) && (o.m_thread != OMNI_NULL)) ?
            (*this->m_thread == *o.m_thread)
            : (this->m_thread == o.m_thread)) &&
            this->m_int == o.m_int &&
            this->m_auto == o.m_auto &&
            this->m_isrun == o.m_isrun &&
            this->m_stopreq == o.m_stopreq)
            OMNI_EQUAL_FW(o);
}

void omni::chrono::sync_timer::_do_tick()
{
    if (this->tick) {
        this->tick(omni::chrono::monotonic_tick(), this->state_object);
    }
}

#undef OMNI_TIMER_T_FW
#undef OMNI_TMR_ALOCK_FW
#undef OMNI_TMR_MLOCK_FW
#undef OMNI_TMR_ULOCK_FW
