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
#include <omni/sync/thread.hpp>
#if !defined(OMNI_OS_WIN)
    // need the following for POSIX thread set prio/join
    #include <unistd.h>
    #include <sched.h>
    #include <ctime>
    #include <cstring>
#endif
#include <omni/chrono/tick.hpp>
#include <omni/sync/scoped_lock.hpp>
#include <omni/consts/cconsts.hpp>
#include <omni/exception.hpp>

#if defined(OMNI_NON_PORTABLE)
    #define OMNI_PRIO_FW  m_priority(omni::sync::thread_priority::NORMAL),
    #define OMNI_PRIO_CP_FW m_priority(cp.m_priority),
#else
    #define OMNI_PRIO_FW
    #define OMNI_PRIO_CP_FW 
#endif
#if defined(OMNI_SAFE_THREAD)
    #define OMNI_SAFE_THREAD_MILST_FW  m_mtx(),
    #define OMNI_SAFE_THREAD_LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_THREAD_UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_THREAD_ALOCK_FW  omni::sync::scoped_lock<omni::sync::basic_lock> smal(&this->m_mtx);
#else
    #define OMNI_SAFE_THREAD_MILST_FW
    #define OMNI_SAFE_THREAD_LOCK_FW
    #define OMNI_SAFE_THREAD_UNLOCK_FW
    #define OMNI_SAFE_THREAD_ALOCK_FW
#endif

namespace omni {
    namespace sync {
        typedef struct thread_args {
            omni::sync::thread* bthread;
            omni::sync::safe_spin_wait swait;
        } thread_args;
    }
}

//// start static thread management methods ////

void omni::sync::thread::manager::abort(omni::sync::thread_t tid)
{
    this->m_lock.lock();
    if (this->m_aborts.find(tid) != this->m_aborts.end()) {
        this->m_aborts[tid] = true;
    }
    this->m_lock.unlock();
}

bool omni::sync::thread::manager::abort_requested()
{
    bool ret = false;
    this->m_lock.lock();
    omni::sync::thread::manager::abort_map::iterator it = this->m_aborts.find(omni::sync::thread_id());
    if (it != this->m_aborts.end()) { ret = it->second; }
    this->m_lock.unlock();
    return ret;
}

void omni::sync::thread::manager::push_back(omni::sync::thread_t tid, omni::sync::thread& bthread)
{
    this->m_lock.lock();
    OMNI_DV5_FW("adding managed thread id: ", tid);
    this->m_threads[tid] = &bthread;
    this->m_aborts[tid] = false;
    this->m_lock.unlock();
}

void omni::sync::thread::manager::pop_back(omni::sync::thread_t tid)
{
    this->m_lock.lock();
    // erase the abort state first
    omni::sync::thread::manager::abort_map::iterator aitr = this->m_aborts.find(tid);
    if (aitr != this->m_aborts.end()) { this->m_aborts.erase(aitr); }
    omni::sync::thread::manager::thread_map::iterator itr = this->m_threads.find(tid);
    if (itr != this->m_threads.end()) {
        /* if the tid is still in the map, then the thread object is still attached to the
        state machine and it is safe to call the sate machine function on the thread object
        we grabbed from above */
        omni::sync::thread* t = itr->second;
        this->m_threads.erase(itr);
        this->m_lock.unlock();
        t->_state_machine();
    } else {
        this->m_lock.unlock();
    }
}

void omni::sync::thread::manager::remove(omni::sync::thread_t tid)
{
    this->m_lock.lock();
    omni::sync::thread::manager::thread_map::iterator it = this->m_threads.find(tid);
    if (it != this->m_threads.end()) {
        OMNI_DV5_FW("removing managed thread id: ", tid);
        this->m_threads.erase(it);
    }
    this->m_lock.unlock();
}

void omni::sync::thread::manager::request_abort(omni::sync::thread_t tid)
{
    bool found = false;
    this->m_lock.lock();
    omni::sync::thread::manager::thread_map::iterator itr = this->m_threads.find(tid);
    if (itr != this->m_threads.end()) {
        if (itr->second) {
            /* if the tid is still in the map, then the thread is still
            attached to the state machine (i.e. still being managed), so
            grab the underlying thread object and call abort on it */
            omni::sync::thread* t = itr->second;
            found = true;
            this->m_lock.unlock();
            t->abort(); // calls the m_aborts[tid] = true;
        }
    }
    if (!found) {
        if (this->m_aborts.find(tid) != this->m_aborts.end()) {
            this->m_aborts[tid] = true;
        }
        this->m_lock.unlock();
    }
}

OMNI_THREAD_FNPTR_T OMNI_THREAD_CALL_T omni::sync::thread::_start(void* param)
{
    /* note: we do not call t->any_function() since that could potentially introduce a deadlock.
    If the thread gets this far, then the thread::start() function has already called scoped_lock
    and it is safe to use t->m_ values (since no other threads can operate on the values) */
    omni::sync::thread* t = (static_cast<omni::sync::thread_args*>(param))->bthread;
    if (t->m_mthd != OMNI_NULL) {
        omni::sync::thread_t tid = omni::sync::thread_id();
        omni::sync::parameterized_thread_start* pstartfn = OMNI_NULL;
        omni::sync::thread_start* startfn = OMNI_NULL;
        omni::sync::thread::manager::instance().push_back(tid, *t);
        if (t->m_ispmthd) {
            pstartfn = new omni::sync::parameterized_thread_start(*(static_cast<omni::sync::parameterized_thread_start*>(t->m_mthd)));
        } else {
            startfn = new omni::sync::thread_start(*(static_cast<omni::sync::thread_start*>(t->m_mthd)));
        }
        #if !defined(OMNI_OS_WIN)
            /*
                we do not check for any errors here as it is not a good idea to ever kill a thread.
                setting to async cancel type sets the cross platform compatibility as TerminateThread
                is async in nature.
                
                !!!! NOTE !!!!
                
                remember, it is a better idea to use abort and the state_changed handler to end
                your threads nicely (avoid resource leaks)
            */
            ::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
        #endif
        #if defined(OMNI_NON_PORTABLE)
            if (t->m_priority != omni::sync::thread_priority::NORMAL) {
                OMNI_D4_FW("setting thread priority");
                t->_set_prio();
            }
        #endif
        t->m_state = omni::sync::thread_state::RUNNING;
        // wrap the delegate in a try..catch in case the user code errors, we can handle it here
        if (pstartfn != OMNI_NULL) {
            OMNI_THREAD_TRY_FW
            omni::sync::thread_arg_t args = t->m_args;
            (static_cast<omni::sync::thread_args*>(param))->swait.signal();
            pstartfn->invoke(args);
            OMNI_THREAD_CATCHEX_FW(delete pstartfn;)
        } else if (startfn != OMNI_NULL) {
            OMNI_THREAD_TRY_FW
            (static_cast<omni::sync::thread_args*>(param))->swait.signal();
            startfn->invoke();
            OMNI_THREAD_CATCHEX_FW(delete startfn;)
        }
        pstartfn = OMNI_NULL; startfn = OMNI_NULL;
        omni::sync::thread::manager::instance().pop_back(tid);
    } else {
        // should not happen since this should be caught in the calling thread::start
        OMNI_DBGE(OMNI_INVALID_DELEGATE_FUNC_STR)
        OMNI_THROW_FW(omni::exceptions::invalid_delegate())        
        // if nothrow then act as killed
        // DEV_NOTE: if OMNI_THROW_FW is defined, you might get warnings about this code being unreachable
        t->m_state = omni::sync::thread_state::STOPPED;
        (static_cast<omni::sync::thread_args*>(param))->swait.signal();
    }
    t = OMNI_NULL;
    return 0;
}

bool omni::sync::thread::abort_requested()
{
    return omni::sync::thread::manager::instance().abort_requested();
}

void omni::sync::thread::request_abort(omni::sync::thread_t tid)
{
    omni::sync::thread::manager::instance().request_abort(tid);
}

//// start thread constructors ////

omni::sync::thread::thread() : 
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(OMNI_NULL),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created");
}

omni::sync::thread::thread(const omni::sync::thread &cp) : 
    aborted(cp.aborted),
    completed(cp.completed),
    OMNI_CPCTOR_FW(cp)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(cp.m_args),
    m_mthd(OMNI_NULL),
    m_tid(cp.m_tid),
    m_thread(cp.m_thread),
    m_ops(cp.m_ops),
    m_state(cp.m_state),
    OMNI_PRIO_CP_FW
    m_isjoined(cp.m_isjoined),
    m_ispmthd(cp.m_ispmthd)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    if (cp.m_mthd != OMNI_NULL) {
        if (cp.m_ispmthd) {
            this->m_mthd = new omni::sync::parameterized_thread_start(*(static_cast<omni::sync::parameterized_thread_start*>(cp.m_mthd)));
        } else {
            this->m_mthd = new omni::sync::thread_start(*(static_cast<omni::sync::thread_start*>(cp.m_mthd)));
        }
    }
    OMNI_D5_FW("thread copied");
}

omni::sync::thread::thread(const omni::sync::thread_flags &ops) : 
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(OMNI_NULL),
    m_tid(0),
    m_thread(0),
    m_ops(ops),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    OMNI_D5_FW("thread const copied");
}

omni::sync::thread::thread(std::size_t max_stack_sz) : 
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(OMNI_NULL),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd) : 
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd, const omni::sync::thread::delegate& abort_req) : 
    aborted(abort_req),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd, const omni::sync::thread::delegate& abort_req, const omni::sync::thread::delegate& comp) : 
    aborted(abort_req),
    completed(comp),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
}

omni::sync::thread::thread(const omni::sync::thread_start& mthd, omni::sync::thread_start_type::enum_t st) :
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
    if (st == omni::sync::thread_start_type::NOW) {
        this->start();
    }
}

omni::sync::thread::thread(const omni::sync::thread_start& mthd, const omni::sync::thread::delegate& abort_req, omni::sync::thread_start_type::enum_t st) :
    aborted(abort_req),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
    if (st == omni::sync::thread_start_type::NOW) {
        this->start();
    }
}

omni::sync::thread::thread(const omni::sync::thread_start& mthd, const omni::sync::thread::delegate& abort_req, const omni::sync::thread::delegate& comp, omni::sync::thread_start_type::enum_t st) :
    aborted(abort_req),
    completed(comp),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
    if (st == omni::sync::thread_start_type::NOW) {
        this->start();
    }
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd, std::size_t max_stack_sz) :
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd, const omni::sync::thread::delegate& abort_req, std::size_t max_stack_sz) :
    aborted(abort_req),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd, const omni::sync::thread::delegate& abort_req, const omni::sync::thread::delegate& comp, std::size_t max_stack_sz) :
    aborted(abort_req),
    completed(comp),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st) :
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
    if (st == omni::sync::thread_start_type::NOW) {
        this->start();
    }
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd, const omni::sync::thread::delegate& abort_req, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st) :
    aborted(abort_req),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
    if (st == omni::sync::thread_start_type::NOW) {
        this->start();
    }
}

omni::sync::thread::thread(const omni::sync::thread_start &mthd, const omni::sync::thread::delegate& abort_req, const omni::sync::thread::delegate& comp, std::size_t max_stack_sz, omni::sync::thread_start_type::enum_t st) :
    aborted(abort_req),
    completed(comp),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
    if (st == omni::sync::thread_start_type::NOW) {
        this->start();
    }
}

omni::sync::thread::thread(const omni::sync::thread_start& mthd, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val) : 
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with specific options");
    this->set_option(op, val);
}

// parameterized thread start constructors

omni::sync::thread::thread(const omni::sync::parameterized_thread_start &mthd) : 
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::parameterized_thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(true)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
}

omni::sync::thread::thread(const omni::sync::parameterized_thread_start &mthd, const omni::sync::thread::delegate& abort_req) : 
    aborted(abort_req),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::parameterized_thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(true)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
}

omni::sync::thread::thread(const omni::sync::parameterized_thread_start &mthd, const omni::sync::thread::delegate& abort_req, const omni::sync::thread::delegate& comp) : 
    aborted(abort_req),
    completed(comp),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::parameterized_thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(true)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with delegate method");
}

omni::sync::thread::thread(const omni::sync::parameterized_thread_start &mthd, std::size_t max_stack_sz) :
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::parameterized_thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(true)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
}

omni::sync::thread::thread(const omni::sync::parameterized_thread_start &mthd, const omni::sync::thread::delegate& abort_req, std::size_t max_stack_sz) :
    aborted(abort_req),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::parameterized_thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(true)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
}

omni::sync::thread::thread(const omni::sync::parameterized_thread_start &mthd, const omni::sync::thread::delegate& abort_req, const omni::sync::thread::delegate& comp, std::size_t max_stack_sz) :
    aborted(abort_req),
    completed(comp),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::parameterized_thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(max_stack_sz),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(true)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_DV5_FW("thread created with stack size of ", this->m_ops.stack_size());
}

omni::sync::thread::thread(const omni::sync::parameterized_thread_start& mthd, omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val) :
    aborted(),
    completed(),
    OMNI_CTOR_FW(omni::sync::thread)
    OMNI_SAFE_THREAD_MILST_FW
    m_args(),
    m_mthd(new omni::sync::parameterized_thread_start(mthd)),
    m_tid(0),
    m_thread(0),
    m_ops(),
    m_state(omni::sync::thread_state::UNSTARTED),
    OMNI_PRIO_FW
    m_isjoined(false),
    m_ispmthd(true)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
    OMNI_D5_FW("thread created with specific options");
    this->set_option(op, val);
}

//// end thread constructors ////

omni::sync::thread::~thread()
{
    OMNI_D5_FW("thread tearing down");
    OMNI_TRY_FW
    OMNI_DTOR_FW
    OMNI_SAFE_THREAD_LOCK_FW
    bool do_detach = true;
    if (this->_hvalid() && this->_state_running()) {
        if (this->m_ops.detach_on_destroy()) {
            this->_hreset(true, false); // detach
            do_detach = false;
        } else {
            if (this->m_ops.abort_on_destroy()) {
                OMNI_D5_FW("abort on destroy");
                this->m_state = omni::sync::thread_state::ABORT_REQUESTED;
                omni::sync::thread::manager::instance().abort(this->m_tid);
                OMNI_SAFE_THREAD_UNLOCK_FW
                if (this->aborted) { this->aborted(*this); }
                OMNI_SAFE_THREAD_LOCK_FW
            }
            if (this->m_ops.auto_join()) {
                OMNI_D5_FW("auto join");
                std::size_t to = this->m_ops.auto_join_timeout();
                if (to > 0) {
                    bool kod = this->m_ops.kill_on_destroy();
                    OMNI_SAFE_THREAD_UNLOCK_FW
                    this->join(static_cast<uint32_t>(to));
                    if (kod) { this->kill(); }
                    OMNI_SAFE_THREAD_LOCK_FW
                } else {
                    OMNI_SAFE_THREAD_UNLOCK_FW
                    this->join();
                    OMNI_SAFE_THREAD_LOCK_FW
                }
            } else {
                if (this->m_ops.kill_on_destroy()) {
                    OMNI_D5_FW("killing");
                    OMNI_SAFE_THREAD_UNLOCK_FW
                    this->kill();
                    OMNI_SAFE_THREAD_LOCK_FW
                }
            }
        }
    }
    if (do_detach) { this->_hreset(true, false); }
    this->_chkmthd();
    OMNI_SAFE_THREAD_UNLOCK_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

void omni::sync::thread::abort()
{
    OMNI_SAFE_THREAD_LOCK_FW
    bool valid = this->_hvalid();
    bool running = this->_state_running();
    OMNI_SAFE_THREAD_UNLOCK_FW
    if (!valid) { OMNI_ERR_FW(OMNI_INVALID_THREAD_HANDLE_STR, omni::exceptions::invalid_thread_handle()) }
    if (running) { this->_state_changed(omni::sync::thread_state::ABORT_REQUESTED); }
    #if defined(OMNI_DBG_L3)
    else { OMNI_D3_FW("thread is not running"); }
    #endif
}

bool omni::sync::thread::abort_join()
{
    this->abort();
    return this->join();
}

bool omni::sync::thread::abort_join(uint32_t timeout)
{
    this->abort();
    return this->join(timeout);
}

bool omni::sync::thread::bind(const omni::sync::parameterized_thread_start& mthd)
{
    if (!this->unbind()) { return false; }
    OMNI_SAFE_THREAD_LOCK_FW
    this->m_mthd = new omni::sync::parameterized_thread_start(mthd);
    this->m_ispmthd = true;
    OMNI_SAFE_THREAD_UNLOCK_FW
    return true;
}

bool omni::sync::thread::bind(const omni::sync::thread_start& mthd)
{
    if (!this->unbind()) { return false; }
    OMNI_SAFE_THREAD_LOCK_FW
    this->m_mthd = new omni::sync::thread_start(mthd);
    OMNI_SAFE_THREAD_UNLOCK_FW
    return true;
}

void omni::sync::thread::detach()
{
    this->detach(false);
}

void omni::sync::thread::detach(bool allow_rejoin)
{
    OMNI_SAFE_THREAD_ALOCK_FW
    this->_hreset(true, allow_rejoin);
}

const omni::sync::thread_union_t omni::sync::thread::get_option(omni::sync::thread_option::enum_t op) const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    switch (op) {
        case omni::sync::thread_option::ALLOW_THREAD_REUSE:
            return this->m_ops.allow_reuse();
        case omni::sync::thread_option::AUTO_JOIN:
            return this->m_ops.auto_join();
        case omni::sync::thread_option::DETACH_ON_DESTROY:
            return this->m_ops.detach_on_destroy();
        case omni::sync::thread_option::ABORT_ON_DESTROY:
            return this->m_ops.abort_on_destroy();
        case omni::sync::thread_option::KILL_ON_DESTROY:
            return this->m_ops.kill_on_destroy();
        case omni::sync::thread_option::DETACH_ON_ASSIGN:
            return this->m_ops.detach_on_assign();
        case omni::sync::thread_option::ABORT_ON_ASSIGN:
            return this->m_ops.abort_on_assign();
        case omni::sync::thread_option::KILL_ON_ASSIGN:
            return this->m_ops.kill_on_assign();
        case omni::sync::thread_option::STACK_SIZE:
            return this->m_ops.stack_size();
        case omni::sync::thread_option::AUTO_JOIN_TIMEOUT:
            return this->m_ops.auto_join_timeout();
        case omni::sync::thread_option::NONE:
        default: // invalid_option
            OMNI_ERRV_FW("invalid option: ", op, omni::exceptions::invalid_thread_option(static_cast<std::size_t>(op)))
            break;
    }
    return false;
}

omni::sync::thread_flags omni::sync::thread::options() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    return this->m_ops;
}

omni::sync::thread_handle_t omni::sync::thread::handle() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    return this->m_thread;
}

omni::sync::thread_t omni::sync::thread::id() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    return this->m_tid;
}

bool omni::sync::thread::is_alive() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    /*
    DEV_NOTE: we do not use pthread_kill or GetExitCodeThread
    since those might give erroneous results for these purposes.
    That is to say, using JUST those APIs will not guarantee
    that our underlying thread is actually running.
    
    omni::sync::thread_state::UNSTARTED = 0,
    // Defines a thread has completed its function (method complete)
    omni::sync::thread_state::COMPLETED = 4,
    // Defines a thread is stopped (killed)
    omni::sync::thread_state::STOPPED = 16,
    // Defines a thread has been aborted
    omni::sync::thread_state::ABORTED = 64,
    // Defines a thread is attempting to spawn
    omni::sync::thread_state::START_REQUESTED = 1,
    
    // Defines a thread is running (method has been called)
    omni::sync::thread_state::RUNNING = 2,
    // Defines a thread has a stop request (kill request)
    omni::sync::thread_state::STOP_REQUESTED = 8,
    // Defines a thread has an abort request
    omni::sync::thread_state::ABORT_REQUESTED = 32,
    // Defines a thread has a state that can not be determined (when creating threads from handles for instance)
    omni::sync::thread_state::UNKNOWN = 255
    */
    return this->_hvalid() && this->_state_running();
}

bool omni::sync::thread::is_bound() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    if (this->m_mthd != OMNI_NULL) {
        if (this->m_ispmthd) {
            return (static_cast<omni::sync::parameterized_thread_start*>(this->m_mthd))->valid();
        } else {
            return (static_cast<omni::sync::thread_start*>(this->m_mthd))->valid();
        }
    }
    return false;
}

bool omni::sync::thread::is_parameter_bound() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    if (this->m_ispmthd) {
        return (static_cast<omni::sync::parameterized_thread_start*>(this->m_mthd))->valid();
    }
    return false;
}

bool omni::sync::thread::is_detached() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    return (this->m_state == omni::sync::thread_state::UNSTARTED &&
            this->m_tid == 0 &&
            this->m_thread == 0);
}

bool omni::sync::thread::join()
{
    return this->join(omni::sync::INFINITE_TIMEOUT);
}

bool omni::sync::thread::join(uint32_t timeout)
{
    // Unknown states can still be joined
    if (!this->is_alive()) {
        OMNI_D2_FW("thread is not running");
        return true;
    }
    OMNI_SAFE_THREAD_LOCK_FW
    if (!this->_hvalid()) { 
        OMNI_SAFE_THREAD_UNLOCK_FW
        OMNI_ERR_RETV_FW(OMNI_INVALID_THREAD_HANDLE_STR, omni::exceptions::invalid_thread_handle(), false)
    }
    omni::sync::thread_handle_t hndl = this->m_thread;
    if (hndl == omni::sync::thread_handle()) {
        OMNI_SAFE_THREAD_UNLOCK_FW
        OMNI_ERR_RETV_FW(OMNI_INVALID_THREAD_OWNER, omni::exceptions::invalid_thread_owner(), false)
    }
    #if defined(OMNI_OS_WIN)
        this->m_isjoined = true;
        OMNI_SAFE_THREAD_UNLOCK_FW
        return (
            (::WaitForSingleObject(OMNI_WIN_TOHNDL_FW(hndl), timeout) == 0) ? true :
            #if !defined(OMNI_DBG_L1)
                false
            #else
                !(OMNI_DBGEV_FW("error while waiting for thread handle: ", OMNI_GLE_PRNT))
            #endif
        );
    #else
        /* There is not a portable mechanism with pthreads to wait on a specific thread without
        implementing a timed_wait condition variable. We do not want the user to have to implement
        a seperate variable based on system, so we implement a timeout loop*/
        this->m_isjoined = true;
        OMNI_SAFE_THREAD_UNLOCK_FW
        if (timeout != omni::sync::INFINITE_TIMEOUT) {
            OMNI_SLEEP_INIT();
            volatile bool iav = true;
            omni::chrono::tick_t ts = omni::chrono::monotonic_tick();
            // iav = (::pthread_kill(hndl, 0) != ESRCH); // == "alive"
            while ((iav = (::pthread_kill(hndl, 0) != ESRCH)) && (omni::chrono::elapsed_ms(ts) < timeout)) {
                OMNI_SLEEP1();
            }
            return (::pthread_kill(hndl, 0) == ESRCH); // == "dead"
        }
        return (
            (::pthread_join(hndl, NULL) == 0) ? true :
            #if !defined(OMNI_DBG_L1)
                false
            #else
                !(OMNI_DBGEV_FW("error while waiting for thread handle: ", OMNI_GLE_PRNT))
            #endif
        );
    #endif
}

bool omni::sync::thread::join(const omni::chrono::unsigned_span_t& span)
{
    return this->join(static_cast<uint32_t>(span.total_milliseconds()));
}

bool omni::sync::thread::kill()
{
    if (!this->is_alive()) {
        // threads already dead, no need to kill
        OMNI_D2_FW("thread is not running");
        return true;
    }
    OMNI_SAFE_THREAD_LOCK_FW
    if (!this->_hvalid()) {
        OMNI_SAFE_THREAD_UNLOCK_FW
        OMNI_ERR_RETV_FW(OMNI_INVALID_THREAD_HANDLE_STR, omni::exceptions::invalid_thread_handle(), false)
    }
    int perr = 0;
    omni::sync::thread_handle_t hndl = this->m_thread;
    if (hndl == omni::sync::thread_handle()) {
        OMNI_SAFE_THREAD_UNLOCK_FW
        OMNI_ERR_RETV_FW(OMNI_INVALID_THREAD_OWNER, omni::exceptions::invalid_thread_owner(), false)
    }
    this->m_state = omni::sync::thread_state::STOP_REQUESTED;
    OMNI_SAFE_THREAD_UNLOCK_FW
    // attempt to kill it
    #if defined(OMNI_OS_WIN)
        if (::TerminateThread(OMNI_WIN_TOHNDL_FW(hndl), 0) == 0) {
            perr = OMNI_GLE;
        }
    #else
        perr = ::pthread_cancel(hndl);
    #endif
    if (perr == 0) {
        this->_state_changed(omni::sync::thread_state::STOPPED);
        return true;
    }
    OMNI_DV1_FW("thread termination error code: ", perr);
    // Something unknown happened...
    OMNI_SAFE_THREAD_LOCK_FW
    this->m_state = omni::sync::thread_state::UNKNOWN;
    OMNI_SAFE_THREAD_UNLOCK_FW
    return false;
}

bool omni::sync::thread::reset()
{
    if (this->is_alive()) {        
        OMNI_ERR_RETV_FW("cannot reset thread while running", omni::exceptions::thread_running_exception(), false)
    } else {
        this->detach();
    }
    return true;
}

bool omni::sync::thread::restart()
{
    if (!this->reset()) { return false; }
    this->start();
    return true;
}

bool omni::sync::thread::restart(omni::sync::thread_arg_t args)
{
    if (!this->reset()) { return false; }
    this->start(args);
    return true;
}

bool omni::sync::thread::restart(const omni::sync::parameterized_thread_start& mthd)
{
    this->bind(mthd);
    return this->restart();
}

bool omni::sync::thread::restart(const omni::sync::thread_start& mthd)
{
    this->bind(mthd);
    return this->restart();
}

bool omni::sync::thread::restart(const omni::sync::parameterized_thread_start& mthd, omni::sync::thread_arg_t args)
{
    this->bind(mthd);
    return this->restart(args);
}

omni::sync::thread_state omni::sync::thread::status() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    return this->m_state;
}

void omni::sync::thread::set_option(omni::sync::thread_option::enum_t op, omni::sync::thread_union_t val)
{
    OMNI_SAFE_THREAD_ALOCK_FW
    switch (op) {
        case omni::sync::thread_option::STACK_SIZE:
            this->m_ops.set_stack_size(val.s_val);
            break;
        case omni::sync::thread_option::AUTO_JOIN_TIMEOUT:
            {
                if (val.s_val > 0) {
                    // if timeout > 0 then auto join should be true
                    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, true);
                    // auto-join over-rides detach (since detach is default)
                    this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_DESTROY, false);
                }
                this->m_ops.set_auto_join_timeout(val.s_val);
            } break;
        case omni::sync::thread_option::ALLOW_THREAD_REUSE:
            this->m_ops.set_flag(omni::sync::thread_option::ALLOW_THREAD_REUSE, val.b_val);
            break;
        case omni::sync::thread_option::AUTO_JOIN:
            {
                if (val.b_val) {
                    // auto-join over-rides detach
                    this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_DESTROY, false);
                }
                this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, val.b_val);
            } break;
        case omni::sync::thread_option::DETACH_ON_DESTROY:
            {
                if (val.b_val) {
                    // if the user sets detach, then auto-join should be false
                    this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, false);
                }
                this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_DESTROY, val.b_val);
            } break;
        case omni::sync::thread_option::ABORT_ON_DESTROY:
            {
                if (val.b_val) {
                    // abort over-rides detach
                    this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_DESTROY, false);
                    this->m_ops.set_flag(omni::sync::thread_option::KILL_ON_DESTROY, false);
                }
                this->m_ops.set_flag(omni::sync::thread_option::ABORT_ON_DESTROY, val.b_val);
            } break;
        case omni::sync::thread_option::KILL_ON_DESTROY:
            {
                if (val.b_val) {
                    this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_DESTROY, false);
                    this->m_ops.set_flag(omni::sync::thread_option::ABORT_ON_DESTROY, false);
                }
                this->m_ops.set_flag(omni::sync::thread_option::KILL_ON_DESTROY, val.b_val);
            } break;
        case omni::sync::thread_option::DETACH_ON_ASSIGN:
            this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_ASSIGN, val.b_val);
            break;
        case omni::sync::thread_option::ABORT_ON_ASSIGN:
            {
                if (val.b_val) {
                    this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_ASSIGN, false);
                }
                this->m_ops.set_flag(omni::sync::thread_option::ABORT_ON_ASSIGN, val.b_val);
            } break;
        case omni::sync::thread_option::KILL_ON_ASSIGN:
            {
                if (val.b_val) {
                    this->m_ops.set_flag(omni::sync::thread_option::ABORT_ON_ASSIGN, false);
                    this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_ASSIGN, false);
                }
                this->m_ops.set_flag(omni::sync::thread_option::KILL_ON_ASSIGN, val.b_val);
            } break;
        case omni::sync::thread_option::NONE:
        default:
            OMNI_ERRV_FW("invalid option: ", op, omni::exceptions::invalid_thread_option(static_cast<std::size_t>(op)))
            break;
    }
}

void omni::sync::thread::set_options(unsigned char op, bool val)
{
    OMNI_SAFE_THREAD_ALOCK_FW
    bool valid_op = false;
    if (OMNI_VAL_HAS_FLAG_BIT(op, omni::sync::thread_option::ALLOW_THREAD_REUSE)) {
        this->m_ops.set_flag(omni::sync::thread_option::ALLOW_THREAD_REUSE, val);
        valid_op = true;
    }
    if (OMNI_VAL_HAS_FLAG_BIT(op, omni::sync::thread_option::AUTO_JOIN)) {
        this->m_ops.set_flag(omni::sync::thread_option::AUTO_JOIN, val);
        valid_op = true;
    }
    if (OMNI_VAL_HAS_FLAG_BIT(op, omni::sync::thread_option::DETACH_ON_DESTROY)) {
        this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_DESTROY, val);
        valid_op = true;
    }
    if (OMNI_VAL_HAS_FLAG_BIT(op, omni::sync::thread_option::ABORT_ON_DESTROY)) {
        this->m_ops.set_flag(omni::sync::thread_option::ABORT_ON_DESTROY, val);
        valid_op = true;
    }
    if (OMNI_VAL_HAS_FLAG_BIT(op, omni::sync::thread_option::KILL_ON_DESTROY)) {
        this->m_ops.set_flag(omni::sync::thread_option::KILL_ON_DESTROY, val);
        valid_op = true;
    }
    if (OMNI_VAL_HAS_FLAG_BIT(op, omni::sync::thread_option::DETACH_ON_ASSIGN)) {
        this->m_ops.set_flag(omni::sync::thread_option::DETACH_ON_ASSIGN, val);
        valid_op = true;
    }
    if (OMNI_VAL_HAS_FLAG_BIT(op, omni::sync::thread_option::ABORT_ON_ASSIGN)) {
        this->m_ops.set_flag(omni::sync::thread_option::ABORT_ON_ASSIGN, val);
        valid_op = true;
    }
    if (OMNI_VAL_HAS_FLAG_BIT(op, omni::sync::thread_option::KILL_ON_ASSIGN)) {
        this->m_ops.set_flag(omni::sync::thread_option::KILL_ON_ASSIGN, val);
        valid_op = true;
    }
    if (!valid_op) {
        OMNI_ERRV_FW("invalid option: ", op, omni::exceptions::invalid_thread_option(static_cast<std::size_t>(op)))
    }
}

void omni::sync::thread::set_options(const omni::sync::thread_flags& ops)
{
    OMNI_SAFE_THREAD_ALOCK_FW
    this->m_ops = ops;
}

omni::sync::thread_t omni::sync::thread::start()
{
    return this->start(OMNI_THREAD_ARG_NULL_T);
}

omni::sync::thread_t omni::sync::thread::start(omni::sync::thread_arg_t args)
{
    OMNI_SAFE_THREAD_ALOCK_FW
    if (this->m_state != omni::sync::thread_state::UNSTARTED) {
        if (this->m_ops.allow_reuse()) {
            // thread reuse is enabled, so reset the handles
            this->_hreset(true, false);
        } else {
            OMNI_ERR_RET_FW("Can not start a thread once it has been started or if it is in an unknown state", omni::exceptions::thread_running_exception());
        }
    }
    if (this->m_mthd == OMNI_NULL) {
        // no delegate attached to this thread so we cannot actually start anything
        OMNI_ERR_RET_FW(OMNI_INVALID_DELEGATE_FUNC_STR, omni::exceptions::invalid_delegate())
    }
    int perr = 0;
    std::size_t stack_size = this->m_ops.stack_size();
    omni::sync::thread_args bargs;
    this->m_args = (this->m_ispmthd ? args : OMNI_THREAD_ARG_NULL_T);
    this->m_state = omni::sync::thread_state::START_REQUESTED;
    this->m_thread = 0;
    bargs.bthread = this;
    #if defined(OMNI_OS_WIN)
        OMNI_TMPIDT_FW tmptid = 0;
        this->m_thread = OMNI_CREATE_THREAD_FW(NULL, // default security attr
                                              stack_size, // stack size
                                              &omni::sync::thread::_start, // _start(void*)
                                              static_cast<void*>(&bargs), // args
                                              0, // start now
                                              &tmptid); // thread id
        // Win32 returns !0 for a valid thread, 0 means error
        if (this->m_thread == 0) { perr = OMNI_GLE; } // error, set perr
        else { this->m_tid = static_cast<omni::sync::thread_t>(tmptid); } // success, set tid
    #else
        // if any of these fails, then thread creation should fail
        if (stack_size == 0) {
            perr = ::pthread_create(&this->m_tid, // the thread id
                                    NULL, // stack size == 0, so null attributes
                                    &omni::sync::thread::_start, // _start(void*)
                                    static_cast<void*>(&bargs)); // args
            if (perr == 0) {
                this->m_thread = this->m_tid; // copy TID to m_thread handle
            } else {
                OMNI_ERRV_FW("system create thread failed: ", perr, omni::exceptions::thread_exception("Create system thread failed: ", perr));
            }
        } else {
            pthread_attr_t attr;
            perr = ::pthread_attr_init(&attr);
            if (perr == 0) {
                perr = ::pthread_attr_setstacksize(&attr, stack_size);
                if (perr == 0) {
                    perr = ::pthread_create(&this->m_tid, // the thread id
                                            &attr, // stack size
                                            &omni::sync::thread::_start, // _start(void*)
                                            static_cast<void*>(&bargs)); // args
                    if (perr == 0) {
                        this->m_thread = this->m_tid; // copy TID to m_thread handle
                    } else {
                        OMNI_ERRV_FW("system create thread failed: ", perr, omni::exceptions::thread_exception("Create system thread failed: ", perr));
                    }
                } else {
                    OMNI_ERR_FW("could not set stack size of " << stack_size << ": " << perr, omni::exceptions::thread_exception("System error setting stack size: ", perr))
                }
                if (perr == 0) {
                    // Destroy the attributes handle
                    perr = ::pthread_attr_destroy(&attr);
                    if (perr != 0) {
                        /* this should only ever happen if attr is not valid
                        but to be safe we want to alert the user since this could signal
                        other issues (we also do not want any rouge handles not being
                        destroyed, ie a memory leak) */
                        OMNI_ERRV_FW("could not destroy attributes: ", perr, omni::exceptions::thread_exception("Could not destroy attributes: ", perr));
                    }
                } else {
                    /* if we got here then there were other errors in thread creation, so
                    do not reset the perr value, just call the function */
                    ::pthread_attr_destroy(&attr);
                }
            } else {
                OMNI_ERR_FW("could not initialize thread attributes @" << &attr << ": " << perr, omni::exceptions::thread_exception("Could not initialize thread attributes: ", perr));
            }
        }
    #endif
    if (perr == 0) {
        OMNI_D4_FW("thread handle valid, waiting for thread switch");
        // valid handle so wait until the thread is actually reported as started
        bargs.swait.sleep_wait();
    } else {
        this->m_thread = 0; 
        OMNI_ERRV_FW("could not create system thread: ", perr, omni::exceptions::thread_exception(perr))
    }
    OMNI_D3_FW(((this->m_tid == 0) ? "invalid" : "created") << " thread:" << this->m_tid);
    return this->m_tid;
}

void omni::sync::thread::swap(omni::sync::thread &o)
{
    if (this != &o) {
        #if defined(OMNI_SAFE_THREAD)
            this->m_mtx.lock();
            o.m_mtx.lock();
        #endif
        std::swap(this->aborted, o.aborted);
        std::swap(this->completed, o.completed);
        std::swap(this->m_args, o.m_args);
        std::swap(this->m_tid, o.m_tid);
        std::swap(this->m_thread, o.m_thread);
        std::swap(this->m_ops, o.m_ops);
        std::swap(this->m_state, o.m_state);
        #if defined(OMNI_NON_PORTABLE)
            std::swap(this->m_priority, o.m_priority);
        #endif
        std::swap(this->m_isjoined, o.m_isjoined);
        std::swap(this->m_mthd, o.m_mthd);
        std::swap(this->m_ispmthd, o.m_ispmthd);
        #if defined(OMNI_SAFE_THREAD)
            this->m_mtx.unlock();
            o.m_mtx.unlock();
        #endif
        
        // old code only here for direct reference...
        // we do not get a copy because of the thread dtor
        //omni::sync::thread tmp(o); // get a copy
        //o._set_context(*this);
        //this->_set_context(tmp);
    }
}

bool omni::sync::thread::unbind()
{
    OMNI_SAFE_THREAD_ALOCK_FW
    if ((this->_hvalid() && this->_state_running()))
    {
        /* do not check thread re-use here since it does not make sense here;
        the logic is that the user must explicitly detach or reset the thread before they can unbind */
        OMNI_ERR_RETV_FW("cannot detach method while thread is running", omni::exceptions::thread_running_exception(), false)
    }
    this->_chkmthd();
    return true;
}

omni::sync::thread &omni::sync::thread::operator=(const omni::sync::thread &o)
{
    if (this != &o) {
        OMNI_SAFE_THREAD_LOCK_FW
        if (this->_hvalid() && this->_state_running()) {
            if (this->m_ops.detach_on_assign()) {
                this->_hreset(true, false); // detach
            } else {
                if (this->m_ops.abort_on_assign()) {
                    this->m_state = omni::sync::thread_state::ABORT_REQUESTED;
                    omni::sync::thread::manager::instance().abort(this->m_tid);
                    OMNI_SAFE_THREAD_UNLOCK_FW
                    if (this->aborted) { this->aborted(*this); }
                    OMNI_SAFE_THREAD_LOCK_FW
                }
                if (this->m_ops.kill_on_assign()) {
                    OMNI_SAFE_THREAD_UNLOCK_FW
                    this->kill();
                    OMNI_SAFE_THREAD_LOCK_FW
                }
                // no auto_join in this context
            }
        }
        OMNI_ASSIGN_FW(o)
        this->_set_context(o);
        OMNI_SAFE_THREAD_UNLOCK_FW
    }
    return *this;
}

bool omni::sync::thread::operator==(const omni::sync::thread &o) const
{
    if (this == &o) { return true; }
    #if defined(OMNI_SAFE_THREAD)
        omni::sync::scoped_lock<omni::sync::basic_lock> am(&this->m_mtx);
        omni::sync::scoped_lock<omni::sync::basic_lock> am2(&o.m_mtx);
    #endif
    return (this->aborted == o.aborted &&
        this->completed == o.completed &&
        this->m_args == o.m_args &&
        this->m_ops == o.m_ops &&
        this->m_state == o.m_state &&
        this->m_tid == o.m_tid &&
        this->m_thread == o.m_thread &&
        this->m_isjoined == o.m_isjoined &&
        ((this->m_mthd == o.m_mthd) ||
        (((this->m_mthd != OMNI_NULL) && (o.m_mthd != OMNI_NULL)) && (this->m_ispmthd == o.m_ispmthd) &&
        (this->m_ispmthd ? (*static_cast<omni::sync::parameterized_thread_start*>(this->m_mthd) == *static_cast<omni::sync::parameterized_thread_start*>(o.m_mthd))
                         : (*static_cast<omni::sync::thread_start*>(this->m_mthd) == *static_cast<omni::sync::thread_start*>(o.m_mthd)))))
        #if defined(OMNI_NON_PORTABLE)
            && this->m_priority == o.m_priority
        #endif
        OMNI_EQUAL_FW(o)
        );
}

bool omni::sync::thread::operator!=(const omni::sync::thread &o) const
{
    return !(*this == o);
}

///////// private methods /////////

void omni::sync::thread::_chkmthd()
{
    if (this->m_mthd != OMNI_NULL) {
        if (this->m_ispmthd) {
            delete static_cast<omni::sync::parameterized_thread_start*>(this->m_mthd);
        } else {
            delete static_cast<omni::sync::thread_start*>(this->m_mthd);
        }
    }
    this->m_mthd = OMNI_NULL;
    this->m_ispmthd = false;
}

void omni::sync::thread::_close_handle(bool allow_rejoin)
{
    if (this->m_tid != 0) { omni::sync::thread::manager::instance().remove(this->m_tid); }
    this->m_state = omni::sync::thread_state::UNSTARTED;
    if (this->m_thread != 0 && !allow_rejoin) {
        // detach the handle so the OS can cleanup when it is done
        if (!this->m_isjoined) {
            OMNI_D5_FW("closing handle");
            #if defined(OMNI_OS_WIN)
                ::CloseHandle(OMNI_WIN_TOHNDL_FW(this->m_thread));
            #else
                /* if we have called pthread_join on this thread then do not detach
                it as that releases it is resources and makes it unjoinable */
                ::pthread_detach(this->m_thread);
            #endif
        }
    }
    this->m_isjoined = false;
    this->m_thread = 0;
    this->m_tid = 0;
    OMNI_D5_FW("handle closed");
}

void omni::sync::thread::_hreset(bool force, bool allow_rejoin)
{
    #if defined(OMNI_NON_PORTABLE)
        this->m_priority = omni::sync::thread_priority::NORMAL;
    #endif
    if (this->m_ops.allow_reuse() || force) { this->_close_handle(allow_rejoin); }
}

bool omni::sync::thread::_hvalid() const
{
    return (this->m_thread != 0);
}

bool omni::sync::thread::_state_running() const
{
    return (this->m_state == omni::sync::thread_state::RUNNING ||
            this->m_state == omni::sync::thread_state::STOP_REQUESTED ||
            this->m_state == omni::sync::thread_state::ABORT_REQUESTED ||
            this->m_state == omni::sync::thread_state::UNKNOWN);
}

void omni::sync::thread::_state_changed(omni::sync::thread_state::enum_t nstate)
{
    OMNI_SAFE_THREAD_LOCK_FW
    omni::sync::thread_t tid = this->m_tid;
    this->m_state = nstate;
    OMNI_SAFE_THREAD_UNLOCK_FW
    switch (nstate) {
        case omni::sync::thread_state::ABORT_REQUESTED: {
            omni::sync::thread::manager::instance().abort(tid);
            if (this->aborted) { this->aborted(*this); }
        } break;
        case omni::sync::thread_state::ABORTED:
        case omni::sync::thread_state::COMPLETED:
        case omni::sync::thread_state::STOPPED:
            if (this->completed) { this->completed(*this); }
            // _hreset is called on dtor/detach or on start when thread_reuse==true
            // calling anything after this statement is not guaranteed
            break;
        // here for pedant, no need to throw errors as this simply changes the state of the thread enum
        case omni::sync::thread_state::START_REQUESTED: case omni::sync::thread_state::STOP_REQUESTED:
        case omni::sync::thread_state::UNSTARTED: case omni::sync::thread_state::UNKNOWN:
        case omni::sync::thread_state::RUNNING: default: break;
    }
}

void omni::sync::thread::_state_machine()
{
    // We cannot check for a stop request since that is a user killing
    // this thread, and if that succeeded then we would not get here
    OMNI_SAFE_THREAD_LOCK_FW
    omni::sync::thread_state::enum_t st = this->m_state;
    OMNI_SAFE_THREAD_UNLOCK_FW
    switch (st) {
        case omni::sync::thread_state::RUNNING:
            this->_state_changed(omni::sync::thread_state::COMPLETED);
            break;
        case omni::sync::thread_state::ABORT_REQUESTED:
            this->_state_changed(omni::sync::thread_state::ABORTED);
            break;
        case omni::sync::thread_state::ABORTED: case omni::sync::thread_state::COMPLETED:
        case omni::sync::thread_state::STOP_REQUESTED: case omni::sync::thread_state::START_REQUESTED:
        case omni::sync::thread_state::UNSTARTED: case omni::sync::thread_state::UNKNOWN:
        case omni::sync::thread_state::STOPPED:
        default:
            /* everything else is a "stopped" by default because this "state machine" function is intended to only
            handle if an abort_request came or if the thread completed on the internal thread function (_start)
            so if this "state machine" function gets any others, it should be noted and the thread object put
            in a "stopped" state (since there is a chance this would happen on a kill) */
            OMNI_DBGE("An invalid thread state was specified for the state_machine");
            this->_state_changed(omni::sync::thread_state::STOPPED);
            break;
    }
    // do not throw an error if the pointers are different .. this is in the event a thread object is detached
}

void omni::sync::thread::_set_context(const omni::sync::thread& t2)
{
    /* The point of this function to avoid a temporary; if a temp omni::sync::thread is created it
    will then be destructed and call thread dtor (and abort/kill/etc. accordingly). Hence the need
    for this function. */
    #if defined(OMNI_SAFE_THREAD)
        this->m_mtx.lock();
        t2.m_mtx.lock();
    #endif
    this->aborted = t2.aborted;
    this->completed = t2.completed;
    this->m_args = t2.m_args;
    this->m_tid = t2.m_tid;
    this->m_thread = t2.m_thread;
    this->m_ops = t2.m_ops;
    this->m_state = t2.m_state;
    #if defined(OMNI_NON_PORTABLE)
        this->m_priority = t2.m_priority;
    #endif
    this->m_isjoined = t2.m_isjoined;    
    this->_chkmthd();
    if (t2.m_mthd != OMNI_NULL) {
        if (t2.m_ispmthd) {
            this->m_mthd = new omni::sync::thread_start(*(static_cast<omni::sync::thread_start*>(t2.m_mthd)));
        } else {
            this->m_mthd = new omni::sync::parameterized_thread_start(*(static_cast<omni::sync::parameterized_thread_start*>(t2.m_mthd)));
            this->m_ispmthd = true;
        }
    }
    #if defined(OMNI_SAFE_THREAD)
        t2.m_mtx.unlock();
        this->m_mtx.unlock();
    #endif
}

///////// non portable methods /////////

#if defined(OMNI_NON_PORTABLE)

void omni::sync::thread::_set_prio()
{
    int pri = static_cast<int>(this->m_priority);
    OMNI_DV4_FW("changing priority to ", pri);
    /* we do not throw an error if we cannot set the thread priority since the
    OS could decide not to do it any ways or the system may not support it */ 
    #if defined(OMNI_OS_WIN)
        if (::SetThreadPriority(OMNI_WIN_TOHNDL_FW(this->m_thread), pri) == 0) {
            OMNI_DBGE(OMNI_ERR_SET_PRI_STR << ": " << OMNI_GLE)
        }
    #else
        int sched = 0;
        struct sched_param param;
        std::memset(&param, 0, sizeof(sched_param));
        if (::pthread_getschedparam(this->m_thread, &sched, &param) == 0) {
            int min = ::sched_get_priority_min(sched);
            int max = ::sched_get_priority_max(sched);
            if (pri < min) { pri = min; }
            if (pri > max) { pri = max; }
            /* if max < min, there are system errors, however, if min == max
            chances are the scheduling priority is OS dependant (i.e. min=0, max=0 for SCHED_OTHER)
            thus, the OS will decide the scheduling priority for the thread
            regardless if we set the thread priority. */
            if (max > min) {
                int skip = (max - min) / omni::sync::thread_priority::COUNT();
                /* getting a normalized value that is representative of
                this->m_priority according to the system scheduling policy */
                param.sched_priority = (min + ((pri+2) * (skip+1))) + (skip / 2);
                if (::pthread_setschedparam(this->m_thread, sched, &param) != 0) {
                    OMNI_DBGE(OMNI_ERR_SET_PRI_STR << ": " << OMNI_GLE)
                }
            }
            #if defined(OMNI_SHOW_DEBUG_ERR)
            else { OMNI_DBGEV(OMNI_ERR_SET_PRI_STR, ": sched prio max <= min") }
            #endif
        }
        #if defined(OMNI_SHOW_DEBUG_ERR)
        else { OMNI_DBGE(OMNI_ERR_SET_PRI_STR << ": " << OMNI_GLE) }
        #endif
    #endif
}

omni::sync::thread_priority omni::sync::thread::priority() const
{
    OMNI_SAFE_THREAD_ALOCK_FW
    return this->m_priority;
}

void omni::sync::thread::set_priority(omni::sync::thread_priority::enum_t p)
{
    /*
        DEV_NOTE: Thread scheduling is system dependent, this means that even
        though you can ask the scheduler to set a threads priority, it will not always listen.
        Some systems implement a more robust scheduler; OpenBSD for instance implements
        a type of round robin scheduler that schedules threads according to set priority.
        Others implement a load based scheduler; Ubuntu (and quite a few other Linux variants)
        for example implement an approach where by a thread is scheduled on it is priority
        only when the CPU is under heavy stress, otherwise all threads get equal priority.
        
        As such, setting the thread priority is not guaranteed (per MSDN and the POSIX
        documentation), which means while we can give this functionality to you in a
        platform independent manor, be aware that thread priorities are in fact
        system dependent and even the systems themselves state they cannot guarantee
        setting the priority will mean anything.
        
        To a degree this makes sense in the fact that allowing a user land thread to
        have a higher priority than a kernel thread could be potentially harmful, so
        again be aware of this non guaranteed function.
    */
    
    int pri = static_cast<int>(p);
    if (pri < omni::sync::thread_priority::LOWEST) { pri = omni::sync::thread_priority::IDLE; }
    if (pri > omni::sync::thread_priority::HIGHEST) { pri = omni::sync::thread_priority::REAL_TIME; }
    if ((pri < omni::sync::thread_priority::LOWEST && pri != omni::sync::thread_priority::IDLE) ||
        (pri > omni::sync::thread_priority::HIGHEST && pri != omni::sync::thread_priority::REAL_TIME))
    {
        // invalid_priority
        OMNI_ERRV_RET_FW("invalid priority: ", pri, omni::exceptions::invalid_thread_option(static_cast<size_t>(pri)))
    }
    OMNI_SAFE_THREAD_LOCK_FW
    // if we are not running, just set the priority til next time
    this->m_priority = pri;
    OMNI_SAFE_THREAD_UNLOCK_FW
    if (this->is_alive()) {
        OMNI_SAFE_THREAD_ALOCK_FW
        // we can only set the priority if the thread is running and handle is valid
        if (!this->_hvalid()) {
            OMNI_ERR_FW(OMNI_INVALID_THREAD_HANDLE_STR, omni::exceptions::invalid_thread_handle())
        } else {
            this->_set_prio();
        }
    }
}

#endif

///////// omni::sync::thread (end) /////////
