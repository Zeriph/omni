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
#include <omni/chrono/queue_timer.hpp>
#include <omni/defs/timer_def.hpp>

#if defined(OMNI_SAFE_QUEUE_TIMER)
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_QTMQMTX_FW OMNI_SAFE_TCTRMTX_FW m_qmtx(),
    #define OMNI_TMR_ALOCK_FW    OMNI_TMRALOCK_FW
    #define OMNI_TMR_OLOCK_FW(o) OMNI_TMROLOCK_FW(o)
    #define OMNI_TMR_MLOCK_FW    OMNI_TMRLOCK_FW
    #define OMNI_TMR_ULOCK_FW    OMNI_TMRUNLOCK_FW
#else
    #define OMNI_SAFE_QTMQMTX_FW
    #define OMNI_TMR_ALOCK_FW
    #define OMNI_TMR_OLOCK_FW(o)
    #define OMNI_TMR_MLOCK_FW
    #define OMNI_TMR_ULOCK_FW
#endif

#define OMNI_TIMER_T_FW queue_timer
#define OMNI_TIMER_EX_STOP_FW if (this->m_qthread != OMNI_NULL) { delete this->m_qthread; this->m_qthread = OMNI_NULL; }
#define OMNI_TIMER_EX_RUN_BEG_FW this->m_qthread = omni::sync::allocate_basic_thread< omni::chrono::queue_timer, &omni::chrono::queue_timer::_run_queued >(*this, omni::sync::thread_start_type::USER);   
// this->m_qmtx.lock();  if (!this->m_que.empty()) { this->m_que.clear(); } this->m_qmtx.unlock();
#define OMNI_TIMER_EX_RUN_END_FW this->m_qthread->join(); delete this->m_qthread; this->m_qthread = OMNI_NULL;
#include <omni/xx/timer.hxx>

omni::chrono::queue_timer::queue_timer() : 
    state_object(),
    tick(),
    OMNI_CTOR_FW(omni::chrono::queue_timer)
    OMNI_SAFE_QTMQMTX_FW
    m_que(),
    m_thread(OMNI_NULL),
    m_qthread(OMNI_NULL),
    m_int(100),
    m_auto(true),
    m_isrun(false),
    m_stopreq(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::queue_timer::queue_timer(const omni::chrono::queue_timer& cp) : 
    state_object(),
    tick(),
    OMNI_CPCTOR_FW(cp)
    OMNI_SAFE_QTMQMTX_FW
    m_que(cp.m_que),
    m_thread(OMNI_NULL),
    m_qthread(OMNI_NULL),
    m_int(cp.m_int),
    m_auto(cp.m_auto),
    m_isrun(cp.m_isrun),
    m_stopreq(cp.m_stopreq)
{
    #if defined(OMNI_SAFE_QUEUE_TIMER)
        cp.m_mtx.lock();
        cp.m_qmtx.lock();
    #endif
    this->state_object = cp.state_object;
    this->tick = cp.tick;
    this->m_que = cp.m_que;
    this->m_int = cp.m_int;
    this->m_auto = cp.m_auto;
    if (cp.m_isrun && !cp.m_stopreq) { this->start(); }
    #if defined(OMNI_SAFE_QUEUE_TIMER)
        cp.m_qmtx.unlock();
        cp.m_mtx.unlock();
    #endif
    OMNI_D5_FW("copied");
}

omni::chrono::queue_timer::queue_timer(uint32_t interval_ms) : 
    state_object(),
    tick(),
    OMNI_CTOR_FW(omni::chrono::queue_timer)
    OMNI_SAFE_QTMQMTX_FW
    m_que(),
    m_thread(OMNI_NULL),
    m_qthread(OMNI_NULL),
    m_int(interval_ms),
    m_auto(true),
    m_isrun(false),
    m_stopreq(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::queue_timer::queue_timer(uint32_t interval_ms, const omni::chrono::timer_delegate& fn) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::queue_timer)
    OMNI_SAFE_QTMQMTX_FW
    m_que(),
    m_thread(OMNI_NULL),
    m_qthread(OMNI_NULL),
    m_int(interval_ms),
    m_auto(true),
    m_isrun(false),
    m_stopreq(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::queue_timer::queue_timer(uint32_t interval_ms,
                           const omni::chrono::timer_delegate& fn,
                           bool autoreset) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::queue_timer)
    OMNI_SAFE_QTMQMTX_FW
    m_que(),
    m_thread(OMNI_NULL),
    m_qthread(OMNI_NULL),
    m_int(interval_ms),
    m_auto(autoreset),
    m_isrun(false),
    m_stopreq(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
}

omni::chrono::queue_timer::queue_timer(uint32_t interval_ms,
                           const omni::chrono::timer_delegate& fn,
                           bool autoreset,
                           uint32_t delay) : 
    state_object(),
    tick(fn),
    OMNI_CTOR_FW(omni::chrono::queue_timer)
    OMNI_SAFE_QTMQMTX_FW
    m_que(),
    m_thread(OMNI_NULL),
    m_qthread(OMNI_NULL),
    m_int(interval_ms),
    m_auto(autoreset),
    m_isrun(false),
    m_stopreq(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_DV5_FW("created with interval of ", this->m_int);
    this->start(delay);
}

void omni::chrono::queue_timer::swap(omni::chrono::queue_timer& other)
{
    if (this != &other) {
        OMNI_TMR_ALOCK_FW
        OMNI_TMR_OLOCK_FW(other)
        std::swap(this->m_thread, other.m_thread);
        std::swap(this->m_qthread, other.m_qthread);
        std::swap(this->m_que, other.m_que);
        std::swap(this->m_int, other.m_int);
        std::swap(this->m_auto, other.m_auto);
        std::swap(this->m_isrun, other.m_isrun);
        std::swap(this->m_stopreq, other.m_stopreq);
    }
}

omni::chrono::queue_timer& omni::chrono::queue_timer::operator=(const omni::chrono::queue_timer& other)
{
    if (this != &other) {
        this->stop();
        OMNI_ASSIGN_FW(other)
        #if defined(OMNI_SAFE_QUEUE_TIMER)
            this->m_mtx.lock();
            this->m_qmtx.lock();
            other.m_mtx.lock();
            other.m_qmtx.lock();
        #endif
        bool isrun = other.m_isrun;
        bool stopreq = other.m_stopreq;
        this->m_isrun = false;
        this->m_stopreq = false;
        this->state_object = other.state_object;
        this->tick = other.tick;
        this->m_int = other.m_int;
        this->m_que = other.m_que;
        this->m_auto = other.m_auto;
        #if defined(OMNI_SAFE_QUEUE_TIMER)
            other.m_qmtx.unlock();
            other.m_mtx.unlock();
            this->m_qmtx.unlock();
            this->m_mtx.unlock();
        #endif
        if (isrun && !stopreq) { this->start(); }
    }
    return *this;
}

bool omni::chrono::queue_timer::operator==(const omni::chrono::queue_timer &o) const
{
    if (this == &o) { return true; }
    #if defined(OMNI_SAFE_QUEUE_TIMER)
        omni::sync::scoped_lock<omni::sync::basic_lock> mlock(&this->m_mtx);
        omni::sync::scoped_lock<omni::sync::basic_lock> qlock(&this->m_qmtx);
        omni::sync::scoped_lock<omni::sync::basic_lock> omlock(&o.m_mtx);
        omni::sync::scoped_lock<omni::sync::basic_lock> oqlock(&o.m_qmtx);
    #endif
    return (this->state_object == o.state_object &&
            this->tick == o.tick &&
            this->m_que == o.m_que && 
            (((this->m_thread != OMNI_NULL) && (o.m_thread != OMNI_NULL)) ?
            (*this->m_thread == *o.m_thread)
            : (this->m_thread == o.m_thread)) &&
            (((this->m_qthread != OMNI_NULL) && (o.m_qthread != OMNI_NULL)) ?
            (*this->m_qthread == *o.m_qthread)
            : (this->m_qthread == o.m_qthread)) &&
            this->m_int == o.m_int &&
            this->m_auto == o.m_auto &&
            this->m_isrun == o.m_isrun &&
            this->m_stopreq == o.m_stopreq)
            OMNI_EQUAL_FW(o);
}

void omni::chrono::queue_timer::_do_tick()
{
    // queue up the event and spawn a thread to do the queue if necessary
    #if defined(OMNI_SAFE_QUEUE_TIMER)
        this->m_qmtx.lock();
    #endif
    omni::chrono::timer_args tea(omni::chrono::monotonic_tick(), this->state_object);
    this->m_que.push_back(tea);
    if (!this->m_qthread->is_alive()) {
        // restart the basic_thread (detach/start)
        this->m_qthread->detach();
        this->m_qthread->start();
    }
    #if defined(OMNI_SAFE_QUEUE_TIMER)
        this->m_qmtx.unlock();
    #endif
}

void omni::chrono::queue_timer::_run_queued()
{
    #if defined(OMNI_SAFE_QUEUE_TIMER)
        this->m_qmtx.lock();
        while (!this->m_que.empty()) {
            omni::chrono::timer_args arg(this->m_que.front());
            this->m_qmtx.unlock();
            if (this->tick) { this->tick(arg.signal_time, arg.state_object); }
            this->m_qmtx.lock();
            // Don't pop until we are done
            this->m_que.pop_front();
        }
        this->m_qmtx.unlock();
    #else
        while (!this->m_que.empty()) {
            omni::chrono::timer_args arg(this->m_que.front());
            if (this->tick) { this->tick(arg.signal_time, arg.state_object); }
            // Don't pop until we are done
            this->m_que.pop_front();
        }
    #endif
}

bool omni::chrono::queue_timer::_queue_empty() const
{
    #if defined(OMNI_SAFE_QUEUE_TIMER)
        omni::sync::scoped_lock<omni::sync::basic_lock> qlock(&this->m_qmtx);
    #endif
    return this->m_que.empty();
}

#undef OMNI_TIMER_T_FW
#undef OMNI_TMR_ALOCK_FW
#undef OMNI_TMR_MLOCK_FW
#undef OMNI_TMR_ULOCK_FW
