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
#if !defined(OMNI_LIBRARY_HPP)
#define OMNI_LIBRARY_HPP 1

/* Use this header to have access to the complete library, example:

#include <omni/library>

void some_thread(void* p)
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
    return omni::application::run();
}
 
*/

#include <omni/defs/global.hpp> // os.hpp, helper.hpp, omni_ver.hpp, debug.hpp, exception.hpp
#include <omni/defs/class_macros.hpp>

// delegates
#include <omni/delegates.hpp>
#include <omni/types/invoke_t.hpp>

// generic objects
#include <omni/generic_error.hpp>
#include <omni/types/ptr_t.hpp> // #include <omni/generic_ptr.hpp>
#include <omni/type.hpp>
#include <omni/object.hpp>
#include <omni/property.hpp>
#include <omni/smart_ptr.hpp>
#include <omni/sequence.hpp> // types/seq_t.hpp
#include <omni/types/enum_t.hpp>

// strings/constants
#include <omni/string/util.hpp> // types/string_t (types/char_t)
#include <omni/ostream.hpp>
#include <omni/strings.hpp> // cstring.hpp, wstring.hpp
#include <omni/constants.hpp> // cconsts.hpp, wconsts.hpp

// buffer types
#include <omni/buffer_types.hpp>

// drawing
#include <omni/color_types.hpp>

// math/geometry
#include <omni/math.hpp>
#include <omni/geometry_types.hpp>

// system/environment
#include <omni/environment.hpp>
#include <omni/system.hpp>
#include <omni/io.hpp>
#include <omni/application.hpp>
#include <omni/argparser.hpp>
#include <omni/bits.hpp>
#include <omni/version.hpp>
#include <omni/net/version.hpp>

// chrono
#include <omni/chrono_types.hpp> // chrono_t.hpp, time.hpp, span.hpp, stopwatch.hpp, timer.hpp

// threading/locks
// types: mutex_t.hpp, lock_t.hpp, thread_t.hpp, runnable_t.hpp
// threading: basic_thread.hpp, thread.hpp, threadpool.hpp, runnable.hpp 
// locks: basic_lock.hpp, mutex.hpp, binary_semaphore.hpp, semaphore.hpp, conditional.hpp, spin.hpp 
#include <omni/sync_types.hpp>

// net
#include <omni/net_types.hpp>

// crypto (hashing/etc.)
#include <omni/crypto_types.hpp>

// others
#include <omni/convert.hpp>

#if defined(OMNI_INCLUDE_EXTENSIONS)
    #include <extensions/extensions.hpp>
#endif

#endif // OMNI_LIBRARY_HPP
