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
#if !defined(OMNI_FRAMEWORK_HPP)
#define OMNI_FRAMEWORK_HPP 1
/*
    The Omni framework is copyright Zeriph Enterprises LLC. The Zeriph name is trademarked
    Zeriph Enterprises LLC. For more licensing information, please see the included license.txt
    file or visit http://www.zeriph.com/legal.html
*/

/* Use this header to have access to the complete framework, example:

#include <omni/framework>

void some_thread(void *p)
{
    do (some_code) {
        here
        omni::sleep(1000);
    }
}
 
int main(int argc, char *argv[]) {
    omni::application::set_args(argc, argv);
    omni::thread t(&some_thread);
    t.start();
    omni::application::run();
}
 
*/

#include <omni/defs/global.hpp> // os.hpp, helper.hpp, omni_ver.hpp, debug.hpp, exception.hpp
#include <omni/defs/class_macros.hpp>
#if defined(OMNI_COMPILE_FLAGS)
    #include <omni/defs/compile_flags.hpp>
#endif

// delegates
#include <omni/delegates.hpp>

// generic objects
#include <omni/base_types.hpp> // char_t.hpp, string_t.hpp, seq_t.hpp, info.hpp, generic_ptr.hpp, smart_ptr.hpp, property.hpp, object.hpp

// strings/constants
#include <omni/string/util.hpp>
#include <omni/ostream.hpp>
#include <omni/strings.hpp> // cstring.hpp, wstring.hpp
#include <omni/constants.hpp> // cconsts.hpp, wconsts.hpp

// drawing/geometry
#include <omni/types/color_t.hpp>
#include <omni/types/point_t.hpp>

// system/environment
#include <omni/environment.hpp>
#include <omni/system.hpp>
#include <omni/io.hpp>
#include <omni/application.hpp>
#include <omni/argparser.hpp>
#include <omni/util/bits.hpp>
#include <omni/util/version.hpp>

// chrono
#include <omni/chrono_types.hpp> // chrono_t.hpp, time.hpp, span.hpp, stopwatch.hpp, timer.hpp

// threading/locks
// types: mutex_t.hpp, lock_t.hpp, thread_t.hpp, runnable_t.hpp
// threading: basic_thread.hpp, thread.hpp, threadpool.hpp, runnable.hpp 
// locks: basic_lock.hpp, mutex.hpp, binary_semaphore.hpp, semaphore.hpp, conditional.hpp, spin.hpp 
#include <omni/sync_types.hpp>

// net
#include <omni/net_types.hpp>
    
#endif // OMNI_FRAMEWORK_HPP
