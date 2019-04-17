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
#if !defined(OMNI_SAFE_DEF_HPP)
#define OMNI_SAFE_DEF_HPP 1

// TODO: add any other "safe" framework entities here

// DEV_NOTE: while most classes in the framework will have a 'safe' version, enum classes will _not_

#if defined(OMNI_SAFE_FRAMEWORK) && defined(OMNI_NO_SAFE_FRAMEWORK)
    #undef OMNI_SAFE_FRAMEWORK
#endif

#if defined(OMNI_SAFE_FRAMEWORK)
    #define OMNI_SAFE_APPLICATION
    #define OMNI_SAFE_COLOR
    #define OMNI_SAFE_DELEGATES
    #define OMNI_SAFE_EVENTS
    #define OMNI_SAFE_PROP
    #define OMNI_SAFE_CHRONO
    #define OMNI_SAFE_LOCKS
    #define OMNI_SAFE_TIMERS
    #define OMNI_SAFE_THREADS
    #define OMNI_SAFE_GEOMETRY
    #define OMNI_CHECK_ARITHMETIC_OVERFLOW
#endif

#if defined(OMNI_SAFE_TIMERS) && (defined(OMNI_NO_SAFE_TIMERS) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_TIMERS
    #if !defined(OMNI_NO_SAFE_TIMERS)
        #define OMNI_NO_SAFE_TIMERS
    #endif
#endif
#if defined(OMNI_SAFE_GEOMETRY) && (defined(OMNI_NO_SAFE_GEOMETRY) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_GEOMETRY
    #if !defined(OMNI_NO_SAFE_GEOMETRY)
        #define OMNI_NO_SAFE_GEOMETRY
    #endif
#endif
#if defined(OMNI_SAFE_CHRONO) && (defined(OMNI_NO_SAFE_CHRONO) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_CHRONO
    #if !defined(OMNI_NO_SAFE_CHRONO)
        #define OMNI_NO_SAFE_CHRONO
    #endif
#endif
#if defined(OMNI_SAFE_LOCKS) && (defined(OMNI_NO_SAFE_LOCKS) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_LOCKS
    #if !defined(OMNI_NO_SAFE_LOCKS)
        #define OMNI_NO_SAFE_LOCKS
    #endif
#endif
#if defined(OMNI_SAFE_THREADS) && (defined(OMNI_NO_SAFE_THREADS) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_THREADS
    #if !defined(OMNI_NO_SAFE_THREADS)
        #define OMNI_NO_SAFE_THREADS
    #endif
#endif

#if defined(OMNI_SAFE_CHRONO)
    #define OMNI_SAFE_SPAN
    #define OMNI_SAFE_STOPWATCH
    #define OMNI_SAFE_DATETIME
#endif

#if defined(OMNI_SAFE_LOCKS)
    #define OMNI_SAFE_MUTEX
    #define OMNI_SAFE_SEMAPHORE
#endif

#if defined(OMNI_SAFE_TIMERS)
    #define OMNI_SAFE_ASYNC_TIMER
    #define OMNI_SAFE_SYNC_TIMER
    #define OMNI_SAFE_DROP_TIMER
    #define OMNI_SAFE_QUEUE_TIMER
#endif

#if defined(OMNI_SAFE_THREADS)
    #define OMNI_SAFE_THREAD
    #define OMNI_SAFE_BASIC_THREAD
    #define OMNI_SAFE_RUNNABLE_THREAD
#endif

#if defined(OMNI_SAFE_GEOMETRY)
    #define OMNI_SAFE_POINT2D
    #define OMNI_SAFE_GEO_SIZE
    #define OMNI_SAFE_POINT3D
    #define OMNI_SAFE_RECTANGLE
    #define OMNI_SAFE_VECTOR2
#endif

#if defined(OMNI_SAFE_APPLICATION) && (defined(OMNI_NO_SAFE_APPLICATION) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_APPLICATION
    #if !defined(OMNI_NO_SAFE_APPLICATION)
        #define OMNI_NO_SAFE_APPLICATION
    #endif
#endif
#if defined(OMNI_SAFE_COLOR) && (defined(OMNI_NO_SAFE_COLOR) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_COLOR
    #if !defined(OMNI_NO_SAFE_COLOR)
        #define OMNI_NO_SAFE_COLOR
    #endif
#endif
#if defined(OMNI_SAFE_DELEGATES) && (defined(OMNI_NO_SAFE_DELEGATES) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_DELEGATES
    #if !defined(OMNI_NO_SAFE_DELEGATES)
        #define OMNI_NO_SAFE_DELEGATES
    #endif
#endif
#if defined(OMNI_SAFE_EVENTS) && (defined(OMNI_NO_SAFE_EVENTS) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_EVENTS
    #if !defined(OMNI_NO_SAFE_EVENTS)
        #define OMNI_NO_SAFE_EVENTS
    #endif
#endif
#if defined(OMNI_SAFE_PROP) && (defined(OMNI_NO_SAFE_PROP) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_PROP
    #if !defined(OMNI_NO_SAFE_PROP)
        #define OMNI_NO_SAFE_PROP
    #endif
#endif
#if defined(OMNI_SAFE_MUTEX) && (defined(OMNI_NO_SAFE_MUTEX) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_MUTEX
    #if !defined(OMNI_NO_SAFE_MUTEX)
        #define OMNI_NO_SAFE_MUTEX
    #endif
#endif
#if defined(OMNI_SAFE_SEMAPHORE) && (defined(OMNI_NO_SAFE_SEMAPHORE) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_SEMAPHORE
    #if !defined(OMNI_NO_SAFE_SEMAPHORE)
        #define OMNI_NO_SAFE_SEMAPHORE
    #endif
#endif
#if defined(OMNI_SAFE_THREAD) && (defined(OMNI_NO_SAFE_THREAD) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_THREAD
    #if !defined(OMNI_NO_SAFE_THREAD)
        #define OMNI_NO_SAFE_THREAD
    #endif
#endif
#if defined(OMNI_SAFE_BASIC_THREAD) && (defined(OMNI_NO_SAFE_BASIC_THREAD) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_BASIC_THREAD
    #if !defined(OMNI_NO_SAFE_BASIC_THREAD)
        #define OMNI_NO_SAFE_BASIC_THREAD
    #endif
#endif
#if defined(OMNI_SAFE_RUNNABLE_THREAD) && (defined(OMNI_NO_SAFE_RUNNABLE_THREAD) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_RUNNABLE_THREAD
    #if !defined(OMNI_NO_SAFE_RUNNABLE_THREAD)
        #define OMNI_NO_SAFE_RUNNABLE_THREAD
    #endif
#endif
#if defined(OMNI_SAFE_ASYNC_TIMER) && (defined(OMNI_NO_SAFE_ASYNC_TIMER) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_ASYNC_TIMER
    #if !defined(OMNI_NO_SAFE_ASYNC_TIMER)
        #define OMNI_NO_SAFE_ASYNC_TIMER
    #endif
#endif
#if defined(OMNI_SAFE_SYNC_TIMER) && (defined(OMNI_NO_SAFE_SYNC_TIMER) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_SYNC_TIMER
    #if !defined(OMNI_NO_SAFE_SYNC_TIMER)
        #define OMNI_NO_SAFE_SYNC_TIMER
    #endif
#endif
#if defined(OMNI_SAFE_DROP_TIMER) && (defined(OMNI_NO_SAFE_DROP_TIMER) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_DROP_TIMER
    #if !defined(OMNI_NO_SAFE_DROP_TIMER)
        #define OMNI_NO_SAFE_DROP_TIMER
    #endif
#endif
#if defined(OMNI_SAFE_QUEUE_TIMER) && (defined(OMNI_NO_SAFE_QUEUE_TIMER) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_QUEUE_TIMER
    #if !defined(OMNI_NO_SAFE_QUEUE_TIMER)
        #define OMNI_NO_SAFE_QUEUE_TIMER
    #endif
#endif
#if defined(OMNI_SAFE_POINT2D) && (defined(OMNI_NO_SAFE_POINT2D) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_POINT2D
    #if !defined(OMNI_NO_SAFE_POINT2D)
        #define OMNI_NO_SAFE_POINT2D
    #endif
#endif
#if defined(OMNI_SAFE_GEO_SIZE) && (defined(OMNI_NO_SAFE_GEO_SIZE) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_GEO_SIZE
    #if !defined(OMNI_NO_SAFE_GEO_SIZE)
        #define OMNI_NO_SAFE_GEO_SIZE
    #endif
#endif
#if defined(OMNI_SAFE_POINT3D) && (defined(OMNI_NO_SAFE_POINT3D) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_POINT3D
    #if !defined(OMNI_NO_SAFE_POINT3D)
        #define OMNI_NO_SAFE_POINT3D
    #endif
#endif
#if defined(OMNI_SAFE_RECTANGLE) && (defined(OMNI_NO_SAFE_RECTANGLE) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_RECTANGLE
    #if !defined(OMNI_NO_SAFE_RECTANGLE)
        #define OMNI_NO_SAFE_RECTANGLE
    #endif
#endif
#if defined(OMNI_SAFE_VECTOR2) && (defined(OMNI_NO_SAFE_VECTOR2) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_VECTOR2
    #if !defined(OMNI_NO_SAFE_VECTOR2)
        #define OMNI_NO_SAFE_VECTOR2
    #endif
#endif
#if defined(OMNI_SAFE_STOPWATCH) && (defined(OMNI_NO_SAFE_STOPWATCH) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_STOPWATCH
    #if !defined(OMNI_NO_SAFE_STOPWATCH)
        #define OMNI_NO_SAFE_STOPWATCH
    #endif
#endif
#if defined(OMNI_SAFE_SPAN) && (defined(OMNI_NO_SAFE_SPAN) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_SPAN
    #if !defined(OMNI_NO_SAFE_SPAN)
        #define OMNI_NO_SAFE_SPAN
    #endif
#endif
#if defined(OMNI_SAFE_DATETIME) && (defined(OMNI_NO_SAFE_DATETIME) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_SAFE_DATETIME
    #if !defined(OMNI_NO_SAFE_DATETIME)
        #define OMNI_NO_SAFE_DATETIME
    #endif
#endif

#if defined(OMNI_SAFE_MUTEX) && !defined(OMNI_MUTEX_OWNER)
    #define OMNI_MUTEX_OWNER
#endif

#if defined(OMNI_CHECK_ARITHMETIC_OVERFLOW) && (defined(OMNI_NO_CHECK_ARITHMETIC_OVERFLOW) || defined(OMNI_NO_SAFE_FRAMEWORK))
    #undef OMNI_CHECK_ARITHMETIC_OVERFLOW
    #if !defined(OMNI_NO_CHECK_ARITHMETIC_OVERFLOW)
        #define OMNI_NO_CHECK_ARITHMETIC_OVERFLOW
    #endif
#endif

#endif // OMNI_SAFE_DEF_HPP
