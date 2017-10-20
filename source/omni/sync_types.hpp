/*
 * This file is part of the Omni C++ framework
 *
 * Copyright 2015, Zeriph Enterprises, LLC
 * 
 * PERMISSION TO USE, COPY, MODIFY, AND/OR DISTRIBUTE THIS SOFTWARE FOR ANY
 * PURPOSE WITH OR WITHOUT FEE IS HEREBY GRANTED, PROVIDED THAT THE ABOVE
 * COPYRIGHT NOTICE AND THIS PERMISSION NOTICE APPEAR IN ALL COPIES.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 * 
 * ZERIPH DOES NOT MAKE ANY ASSURANCES WITH REGARD TO THE ACCURACY OF THE RESULTS
 * OR OUTPUT THAT DERIVES FROM SUCH USE OF ANY SOFTWARE.
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
