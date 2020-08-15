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
#if !defined(OMNI_THREADPOOL_T_HPP)
#define OMNI_THREADPOOL_T_HPP 1
#include <omni/types/thread_t.hpp>

namespace omni {
    namespace sync {
        typedef struct threadpool_task {
            omni::sync::parameterized_thread_start task;
            omni::generic_ptr param;
            
            threadpool_task() : task(), param() {}
            threadpool_task(const omni::sync::threadpool_task& cp) : task(cp.task), param(cp.param) {}
            explicit threadpool_task(omni::sync::parameterized_thread_start t) : task(t), param() {}
            threadpool_task(omni::sync::parameterized_thread_start t, omni::generic_ptr p) : task(t), param(p) {}
            ~threadpool_task() { }
            
            threadpool_task& operator=(const omni::sync::threadpool_task& o)
            {
                if (this != &o) {
                    this->task = o.task;
                    this->param = o.param;
                }
                return *this;
            }
        } threadpool_task;
    }
}

#endif // OMNI_THREADPOOL_T_HPP
