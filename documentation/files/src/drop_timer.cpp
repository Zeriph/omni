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
#include <omni/chrono/drop_timer.hpp>
#include <omni/defs/timer_def.hpp>

#if defined(OMNI_SAFE_DROP_TIMER)
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_DTMQMTX_FW OMNI_SAFE_TCTRMTX_FW
    #define OMNI_TMR_ALOCK_FW    OMNI_TMRALOCK_FW
    #define OMNI_TMR_OLOCK_FW(o) OMNI_TMROLOCK_FW(o)
    #define OMNI_TMR_MLOCK_FW    OMNI_TMRLOCK_FW
    #define OMNI_TMR_ULOCK_FW    OMNI_TMRUNLOCK_FW
#else
    #define OMNI_SAFE_DTMQMTX_FW
    #define OMNI_TMR_ALOCK_FW
    #define OMNI_TMR_OLOCK_FW(o)
    #define OMNI_TMR_MLOCK_FW
    #define OMNI_TMR_ULOCK_FW
#endif

#define OMNI_TIMER_T_FW drop_timer
#define OMNI_TIMER_EX_RUN_END_FW OMNI_TMR_MLOCK_FW \
    if (this->m_exec != 0) { omni::sync::thread_handle_t tid = this->m_exec; \
        OMNI_TMR_ULOCK_FW omni::sync::join_thread(tid); OMNI_TMR_MLOCK_FW \
    } OMNI_TMR_ULOCK_FW
#define OMNI_TIMER_EX_STOP_FW OMNI_TIMER_EX_RUN_END_FW
#include <omni/xx/timer.hxx>

omni::chrono::drop_timer::drop_timer() : 
    state_object(),
    tick(),
    OMNI_CTOR_FW(omni::chrono::drop_timer)
    OMNI_SAFE_DTMQMTX_FW
    m_thread(OMNI_NULL_PTR),
    m_exec(0),
    m_int(100),
    m_status(1)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::drop_timer::drop_timer(const omni::chrono::drop_timer& cp) : 
    state_object(),
    tick(),
    OMNI_CPCTOR_FW(cp)
    OMNI_SAFE_DTMQMTX_FW
    m_thread(OMNI_NULL_PTR),
    m_exec(0),
    m_int(),
    m_status()
{
    #if defined(OMNI_SAFE_DROP_TIMER)
        cp.m_mtx.lock();
    #endif
    this->state_object = cp.state_object;
    this->tick = cp.tick;
    this->m_int = cp.m_int;

    if (OMNI_VAL_HAS_FLAG_BIT(cp.m_status, OMNI_TIMER_AUTO_FLAG_FW)) {
        OMNI_VAL_SET_FLAG_BIT(this->m_status, OMNI_TIMER_AUTO_FLAG_FW);
    }
    
    if (OMNI_VAL_HAS_FLAG_BIT(cp.m_status, OMNI_TIMER_RUN_FLAG_FW) &&
        !OMNI_VAL_HAS_FLAG_BIT(cp.m_status, OMNI_TIMER_STOP_FLAG_FW)) { this->start(); }

    #if defined(OMNI_SAFE_DROP_TIMER)
        cp.m_mtx.unlock();
    #endif
    OMNI_D5_FW("copied");
}

omni::chrono::drop_timer::drop_timer(uint32_t interval_ms) : 
    state_object(),
    tick(),
    OMNI_CTOR_FW(omni::chrono::drop_timer)
    OMNI_SAFE_DTMQMTX_FW
    m_thread(OMNI_NULL_PTR),
    m_exec(0),
    m_int(interval_ms),
    m_status(1)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::drop_timer::drop_timer(uint32_t interval_ms, const omni::chrono::timer_delegate& fn) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::drop_timer)
    OMNI_SAFE_DTMQMTX_FW
    m_thread(OMNI_NULL_PTR),
    m_exec(0),
    m_int(interval_ms),
    m_status(1)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::drop_timer::drop_timer(uint32_t interval_ms,
                           const omni::chrono::timer_delegate& fn,
                           bool autoreset) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::drop_timer)
    OMNI_SAFE_DTMQMTX_FW
    m_thread(OMNI_NULL_PTR),
    m_exec(0),
    m_int(interval_ms),
    m_status(1)
{
    if (!autoreset) {
        OMNI_VAL_UNSET_FLAG_BIT(this->m_status, OMNI_TIMER_AUTO_FLAG_FW);
    }
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::drop_timer::drop_timer(uint32_t interval_ms,
                           const omni::chrono::timer_delegate& fn,
                           bool autoreset,
                           uint32_t delay) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::drop_timer)
    OMNI_SAFE_DTMQMTX_FW
    m_thread(OMNI_NULL_PTR),
    m_exec(0),
    m_int(interval_ms),
    m_status(1)
{
    if (!autoreset) {
        OMNI_VAL_UNSET_FLAG_BIT(this->m_status, OMNI_TIMER_AUTO_FLAG_FW);
    }
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
    this->start(delay);
}

void omni::chrono::drop_timer::swap(omni::chrono::drop_timer& other)
{
    if (this != &other) {
        OMNI_TMR_ALOCK_FW
        OMNI_TMR_OLOCK_FW(other)
        std::swap(this->m_thread, other.m_thread);
        std::swap(this->m_exec, other.m_exec);
        std::swap(this->m_int, other.m_int);
        std::swap(this->m_status, other.m_status);
    }
}

omni::chrono::drop_timer& omni::chrono::drop_timer::operator=(const omni::chrono::drop_timer& other)
{
    if (this != &other) {
        this->stop();
        OMNI_ASSIGN_FW(other)
        #if defined(OMNI_SAFE_DROP_TIMER)
            this->m_mtx.lock();
            other.m_mtx.lock();
        #endif

        bool isrun = OMNI_VAL_HAS_FLAG_BIT(other.m_status, OMNI_TIMER_RUN_FLAG_FW);
        bool stopreq = OMNI_VAL_HAS_FLAG_BIT(other.m_status, OMNI_TIMER_STOP_FLAG_FW);

        this->m_status = 0;
        if (OMNI_VAL_HAS_FLAG_BIT(other.m_status, OMNI_TIMER_AUTO_FLAG_FW)) {
            OMNI_VAL_SET_FLAG_BIT(this->m_status, OMNI_TIMER_AUTO_FLAG_FW);
        }

        this->state_object = other.state_object;
        this->tick = other.tick;
        this->m_int = other.m_int;
        #if defined(OMNI_SAFE_DROP_TIMER)
            other.m_mtx.unlock();
            this->m_mtx.unlock();
        #endif
        if (isrun && !stopreq) { this->start(); }
    }
    return *this;
}

bool omni::chrono::drop_timer::operator==(const omni::chrono::drop_timer& o) const
{
    if (this == &o) { return true; }
    #if defined(OMNI_SAFE_DROP_TIMER)
        omni::sync::scoped_lock<omni::sync::basic_lock> mlock(&this->m_mtx);
        omni::sync::scoped_lock<omni::sync::basic_lock> omlock(&o.m_mtx);
    #endif
    return (this->state_object == o.state_object &&
            this->tick == o.tick &&
            this->m_int == o.m_int &&
            this->m_status == o.m_status)
            OMNI_EQUAL_FW(o);
}

void omni::chrono::drop_timer::_do_tick()
{
    // skip if it is executing already
    OMNI_TMR_MLOCK_FW
    if (this->m_exec == 0) {
        this->m_exec =
            (omni::sync::create_basic_thread<omni::chrono::drop_timer, &omni::chrono::drop_timer::_run_skip>(*this)).handle();
    }
    OMNI_TMR_ULOCK_FW
}

void omni::chrono::drop_timer::_run_skip()
{
    if (this->tick) {
        this->tick(omni::chrono::monotonic_tick(), this->state_object);
    }
    OMNI_TMR_MLOCK_FW
    this->m_exec = 0;
    OMNI_TMR_ULOCK_FW
}
    
#undef OMNI_TIMER_T_FW
#undef OMNI_TMR_ALOCK_FW
#undef OMNI_TMR_MLOCK_FW
#undef OMNI_TMR_ULOCK_FW
