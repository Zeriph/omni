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
#include <omni/sync/threadpool.hpp>
#include <omni/sync/basic_thread.hpp>
#include <omni/sync/this_thread.hpp>
#include <omni/sync/scoped_lock.hpp>

#define OMNI_TPAMTX_FW omni::sync::scoped_lock<omni::sync::basic_lock> acmt(&this->m_mtx);
#define OMNI_TPMIN_TH_FW 4    // default min thread count
#define OMNI_TPMAX_TH_FW 64   // default max thread count

omni::sync::threadpool::threadpool() :
    OMNI_CTOR_FW(omni::sync::threadpool)
    m_act(0),
    m_min(OMNI_TPMIN_TH_FW),
    m_max(OMNI_TPMAX_TH_FW),
    m_mtx(),
    m_threads(),
    m_tasks(),
    m_isdestroy(false)
{
    this->_initialize_min(this->m_min);
    OMNI_D5_FW("created with 5,25");
}

omni::sync::threadpool::threadpool(std::size_t thread_min, std::size_t thread_max) :
    OMNI_CTOR_FW(omni::sync::threadpool)
    m_act(0),
    m_min(thread_min),
    m_max(thread_max),
    m_mtx(),
    m_threads(),
    m_tasks(),
    m_isdestroy(false)
{
    if (thread_min > thread_max) {
        this->m_min = thread_max;
        this->m_max = thread_min;
    }
    if (this->m_max == 0) {
        this->m_max = this->m_min;
    }
    this->_initialize_min(this->m_min);
    OMNI_D5_FW("created with " << this->m_min << "," << this->m_max);
}

omni::sync::threadpool::~threadpool()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    this->m_mtx.lock();
    OMNI_DV5_FW("active thread count: ", this->m_act);
    this->m_isdestroy = true;
    this->m_tasks.clear();
    this->m_mtx.unlock();
    for (omni_threadpool_itr itr = this->m_threads.begin(); itr != this->m_threads.end(); ++itr)
    {
        if (itr->is_alive()) { itr->join(); }
    }
    this->m_mtx.lock();
    this->m_threads.clear();
    this->m_mtx.unlock();
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

std::size_t omni::sync::threadpool::available_threads() const
{
    OMNI_TPAMTX_FW
    /* Active thread count "could" be > max in the instance the user resets
    the max thread count and there are still running threads; in this instance 
    'max-active' would result in overflow and return garbage. */
    return ((this->m_act < this->m_max) ? (this->m_max - this->m_act) : 0);
}

std::size_t omni::sync::threadpool::active_threads() const
{
    OMNI_TPAMTX_FW
    return this->m_act;
}

void omni::sync::threadpool::clear_queue()
{
    OMNI_TPAMTX_FW
    this->m_tasks.clear();
}

std::size_t omni::sync::threadpool::max_threads() const
{
    OMNI_TPAMTX_FW
    return this->m_max;
}

std::size_t omni::sync::threadpool::min_threads() const
{
    OMNI_TPAMTX_FW
    return this->m_min;
}

void omni::sync::threadpool::queue(const omni::sync::parameterized_thread_start& task)
{
    this->_add_queue(omni::sync::threadpool_task(task));
}

void omni::sync::threadpool::queue(const omni::sync::parameterized_thread_start& task, omni::generic_ptr param)
{
    this->_add_queue(omni::sync::threadpool_task(task, param));
}

void omni::sync::threadpool::queue(const omni::sync::threadpool_task& task)
{
    this->_add_queue(task);
}

std::size_t omni::sync::threadpool::queue_size() const
{
    OMNI_TPAMTX_FW
    return this->m_tasks.size();
}

bool omni::sync::threadpool::set_max_threads(std::size_t count)
{
    OMNI_TPAMTX_FW
    if (count == this->m_max ) { return true; }
    if (count < this->m_min || count > this->m_threads.max_size()) {
        return false;
    }
    // we only care if count > max and the active count is at the max and we have tasks
    if ((count > this->m_max) && (this->m_act == this->m_max) && (!this->m_tasks.empty()))
    {
        // we have tasks to do, so create some threads
        std::size_t diff = (count - this->m_max);
        if (this->m_tasks.size() < diff) {
            diff = this->m_tasks.size();
        }
        for (; diff > 0; --diff) {
            this->_create_thread()->start();
        }
    }
    this->m_max = count;
    return true;
}

bool omni::sync::threadpool::set_min_threads(std::size_t count)
{
    OMNI_TPAMTX_FW
    if (count == this->m_min) { return true; } // quick check
    if (count > this->m_max) { return false; }
    this->m_min = count;
    return true;
}

void omni::sync::threadpool::wait_active_queue() const
{
    OMNI_SLEEP_INIT();
    while (true) {
        this->m_mtx.lock();
        if (this->m_act == 0 && this->m_tasks.empty()) {
            this->m_mtx.unlock();
            break;
        }
        this->m_mtx.unlock();
        OMNI_SLEEP(10);
    }
}

///////// start private methods /////////

void omni::sync::threadpool::_add_queue(const omni::sync::threadpool_task& tpt)
{
    OMNI_TPAMTX_FW
    if (this->m_isdestroy) { return; }
    this->m_tasks.push_back(tpt);
    if (this->m_act < this->m_max) {
        if (this->m_act < this->m_min) {
            for (omni_threadpool_itr itr = this->m_threads.begin();
                 itr != this->m_threads.end(); ++itr) 
            {
                if (!itr->is_alive()) {
                    itr->start(); // thread_reuse = true
                    break;
                }
            }
        } else {
            this->_create_thread()->start();
        }
    }
}

omni::sync::threadpool::omni_threadpool_itr omni::sync::threadpool::_create_thread()
{
    this->m_threads.push_back(omni::sync::basic_thread::create_threadpool_thread(
            omni::sync::thread_start::bind<omni::sync::threadpool, &omni::sync::threadpool::_thread_fn>(this)));
    return --(this->m_threads.end());
}

void omni::sync::threadpool::_initialize_min(std::size_t tmin)
{
    for (; tmin > 0; --tmin) { this->_create_thread(); }
}

void omni::sync::threadpool::_thread_fn()
{
    omni::sync::threadpool_task tpt;
    this->m_mtx.lock();
    while (!this->m_isdestroy && !this->m_tasks.empty()) {
        tpt = this->m_tasks.front();
        this->m_tasks.pop_front();
        ++this->m_act;
        this->m_mtx.unlock();
        OMNI_THREAD_TRY_FW
        if (tpt.task) { tpt.task(tpt.param); }
        OMNI_THREAD_CATCH_FW
        this->m_mtx.lock();
        --this->m_act;
    }
    if ((this->m_act >= this->m_min) && !this->m_isdestroy) {
        // find the thread in the list and remove it
        omni::sync::thread_t tid = omni::sync::thread_id();
        for (omni_threadpool_itr itr = this->m_threads.begin(); itr != this->m_threads.end(); ++itr)
        {
            if (itr->id() == tid) {
                this->m_threads.erase(itr);
                break;
            }
        }
    }
    this->m_mtx.unlock();
}
