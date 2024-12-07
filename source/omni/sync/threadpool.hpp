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
#if !defined(OMNI_THREADPOOL_HPP)
#define OMNI_THREADPOOL_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/threadpool_t.hpp>
#include <omni/sync/basic_thread.hpp>
#include <omni/sync/basic_lock.hpp>
#include <omni/chrono/span.hpp>
#include <list>

#if defined(OMNI_32BIT_THREADPOOL)
    #define OMNI_TPOOL_INT_FW uint32_t
#else
    #define OMNI_TPOOL_INT_FW uint64_t
#endif

namespace omni {
    namespace sync {
        class threadpool
        {
            public:
                threadpool();
                threadpool(std::size_t thread_min, std::size_t thread_max);
                ~threadpool();
                
                std::size_t available_threads() const;
                std::size_t active_threads() const;
                void clear_queue();
                std::size_t max_threads() const;
                std::size_t min_threads() const;
                void queue(const omni::sync::parameterized_thread_start& task);
                void queue(const omni::sync::parameterized_thread_start& task, omni::generic_ptr param);
                void queue(const omni::sync::threadpool_task& task);
                std::size_t queue_size() const;
                bool set_max_threads(std::size_t count);
                bool set_min_threads(std::size_t count);
                void wait_active_queue() const;
                
                OMNI_MEMBERS_FW(omni::sync::threadpool) // disposing,name,type(),hash()
                
            private:
                typedef std::list<omni::sync::basic_thread>::iterator omni_threadpool_itr;

                std::size_t m_act; // current active
                std::size_t m_min; // minimum thread count
                std::size_t m_max; // maximum thread count
                mutable omni::sync::basic_lock m_mtx; // threadpool lock

                /*
                    DEV_NOTE: threadpool uses a list for efficient removal of threads in the pool
                    if you define the following, it will use the sequence container used through
                    out the library, but if it is not a list, the deletion from the container
                    could have a performance impact if the element is not at the end or beginning
                */
                #if defined(OMNI_THREADPOOL_USE_SEQ_T)
                    omni_sequence_t<omni::sync::basic_thread> m_threads;
                    omni_sequence_t<omni::sync::threadpool_task> m_tasks;
                #else
                    std::list<omni::sync::basic_thread> m_threads;
                    std::list<omni::sync::threadpool_task> m_tasks;
                #endif
                
                volatile OMNI_TPOOL_INT_FW m_isdestroy;

                // if copy then 2 sets of the same tasks exits, that does not make sense
                threadpool(const threadpool& cp); // = delete
                omni::sync::threadpool& operator=(const omni::sync::threadpool& other); // = delete
                void _add_queue(const omni::sync::threadpool_task& task);
                omni_threadpool_itr _create_thread();
                void _initialize_min(std::size_t tmin);
                void _thread_fn();
        };
    }
}

#endif // OMNI_THREADPOOL_HPP
