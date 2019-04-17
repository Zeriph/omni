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


/* The purpose of this file is to compile the entire Omni library in one large
object file or in one 'step' for a compile script/command line. This is mostly
for convenience; you could do the following

*nix: g++ your_source.cpp /source/omni/library.cpp -I/source/omni -O3 -rt -pthread
win: cl.exe your_source.cpp C:\source\omni\library.cpp /IC:\source\omni /Ox

If you have a need such that you don't want this file built (possibly a script
that automatically compiles any .cpp files), you can define OMNI_NO_SINGLE_FILE
to ensure this file isn't built with the rest. */ 

#if !defined(OMNI_NO_SINGLE_FILE)

#include <omni/framework.hpp>

#if !defined(OMNI_TIMER_LIB) && !defined(OMNI_THREAD_LIB) && !defined(OMNI_NET_LIB)
    #include "application.cpp"
    #include "argparser.cpp"
    #include "environment.cpp"
    #include "externs.cpp"
    #include "io.cpp"
    #include "system.cpp"
    #include "version.cpp"
#endif

#if defined(OMNI_TIMER_LIB) || (!defined(OMNI_THREAD_LIB) && !defined(OMNI_NET_LIB))
    #include "async_timer.cpp"
    #include "drop_timer.cpp"
    #include "queue_timer.cpp"
    #include "sync_timer.cpp"
#endif

#if defined(OMNI_NET_LIB) || (!defined(OMNI_TIMER_LIB) && !defined(OMNI_THREAD_LIB))
    // #include "net_util.cpp" # INCOMPLETE
    // #include "socket.cpp" # INCOMPLETE
    // #include "tcp.cpp" # INCOMPLETE
    // #include "udp.cpp" # INCOMPLETE
#endif

#include "datetime.cpp"
#include "stopwatch.cpp"
    
#include "binary_semaphore.cpp"
#include "conditional.cpp"
#include "mutex.cpp"
#include "semaphore.cpp"

#include "basic_thread.cpp"
#include "runnable.cpp"
#include "thread.cpp"
#include "threadpool.cpp"

#endif
