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
#if !defined(OMNI_THREADING_HPP)
#define OMNI_THREADING_HPP 1

// lock: a basic recursive mutex wrapper class
// mutex: a recursive synchronisation object with thread ownership and lock count
// binary_semaphore: a non-recursive synchronisation object
// semaphore: a non-recursive multi-lock sync object
// spin_lock: a synchronisation object that does a basic spin lock
// spin_wait: a synchronisation object that offers a busy wait (tight loop) or a sleep wait (tight loop with a 1ms sleep)
// conditional: a synchronisation object that allows for conditional waits

// chrono (for sleep/synchronization)
#include <omni/chrono_types.hpp>

// locks
#include <omni/sync/lock.hpp>
#include <omni/sync/auto_lock.hpp>
#include <omni/sync/basic_lock.hpp>
#include <omni/sync/basic_thread.hpp>
#include <omni/sync/binary_semaphore.hpp>
#include <omni/sync/conditional.hpp>
#include <omni/sync/mutex.hpp>
#include <omni/sync/semaphore.hpp>
#include <omni/sync/spin.hpp>
// threading
#include <omni/sync/this_thread.hpp>
#include <omni/sync/basic_thread.hpp>
#include <omni/sync/thread.hpp>
#include <omni/sync/threadpool.hpp>
#include <omni/sync/runnable_thread.hpp>
#include <omni/sync/thread_allocate.hpp>
#include <omni/sync/basic_thread_allocate.hpp>

#endif // OMNI_THREADING_HPP
