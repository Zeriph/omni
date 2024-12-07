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
#if !defined(OMNI_32BIT_DEF_HPP)
#define OMNI_32BIT_DEF_HPP 1

// TODO: (continuous) add any other no-library entities here that do _not_ relate to the safe options

// DEV_NOTE: color and endpoint_descriptor are both defaulted to 32-bit to allow for proper padding
#define OMNI_32BIT_COLOR
#define OMNI_32BIT_ENDPOINT_DESCRIPTOR

#if defined(OMNI_32BIT)
    #define OMNI_32BIT_STOPWATCH
    #define OMNI_32BIT_BASIC_LOCK
    #define OMNI_32BIT_MUTEX
    #define OMNI_32BIT_THREAD
    #define OMNI_32BIT_BASIC_THREAD
    #define OMNI_32BIT_ASYNC_TIMER
    #define OMNI_32BIT_DROP_TIMER
    #define OMNI_32BIT_QUEUE_TIMER
    #define OMNI_32BIT_SYNC_TIMER
    #define OMNI_32BIT_BINARY_SEMAPHORE
    #define OMNI_32BIT_CONDITIONAL
    #define OMNI_32BIT_RUNNABLE_THREAD
    #define OMNI_32BIT_SPIN
    #define OMNI_32BIT_THREADPOOL
#endif

#if defined(OMNI_32BIT_STOPWATCH) && defined(OMNI_NO_32BIT_STOPWATCH)
    #undef OMNI_32BIT_STOPWATCH
#endif
#if defined(OMNI_32BIT_BASIC_LOCK) && defined(OMNI_NO_32BIT_BASIC_LOCK)
    #undef OMNI_32BIT_BASIC_LOCK
#endif
#if defined(OMNI_32BIT_MUTEX) && defined(OMNI_NO_32BIT_MUTEX)
    #undef OMNI_32BIT_MUTEX
#endif
#if defined(OMNI_32BIT_THREAD) && defined(OMNI_NO_32BIT_THREAD)
    #undef OMNI_32BIT_THREAD
#endif
#if defined(OMNI_32BIT_BASIC_THREAD) && defined(OMNI_NO_32BIT_BASIC_THREAD)
    #undef OMNI_32BIT_BASIC_THREAD
#endif
#if defined(OMNI_32BIT_ASYNC_TIMER) && defined(OMNI_NO_32BIT_ASYNC_TIMER)
    #undef OMNI_32BIT_ASYNC_TIMER
#endif
#if defined(OMNI_32BIT_DROP_TIMER) && defined(OMNI_NO_32BIT_DROP_TIMER)
    #undef OMNI_32BIT_DROP_TIMER
#endif
#if defined(OMNI_32BIT_QUEUE_TIMER) && defined(OMNI_NO_32BIT_QUEUE_TIMER)
    #undef OMNI_32BIT_QUEUE_TIMER
#endif
#if defined(OMNI_32BIT_SYNC_TIMER) && defined(OMNI_NO_32BIT_SYNC_TIMER)
    #undef OMNI_32BIT_SYNC_TIMER
#endif
#if defined(OMNI_32BIT_BINARY_SEMAPHORE) && defined(OMNI_NO_32BIT_BINARY_SEMAPHORE)
    #undef OMNI_32BIT_BINARY_SEMAPHORE
#endif
#if defined(OMNI_32BIT_CONDITIONAL) && defined(OMNI_NO_32BIT_CONDITIONAL)
    #undef OMNI_32BIT_CONDITIONAL
#endif
#if defined(OMNI_32BIT_RUNNABLE_THREAD) && defined(OMNI_NO_32BIT_RUNNABLE_THREAD)
    #undef OMNI_32BIT_RUNNABLE_THREAD
#endif
#if defined(OMNI_32BIT_SPIN) && defined(OMNI_NO_32BIT_SPIN)
    #undef OMNI_32BIT_SPIN
#endif
#if defined(OMNI_32BIT_THREADPOOL) && defined(OMNI_NO_32BIT_THREADPOOL)
    #undef OMNI_32BIT_THREADPOOL
#endif
#if defined(OMNI_32BIT_COLOR) && defined(OMNI_NO_32BIT_COLOR)
    #undef OMNI_32BIT_COLOR
#endif
#if defined(OMNI_32BIT_ENDPOINT_DESCRIPTOR) && defined(OMNI_NO_32BIT_ENDPOINT_DESCRIPTOR)
    #undef OMNI_32BIT_ENDPOINT_DESCRIPTOR
#endif

#endif // OMNI_32BIT_DEF_HPP
