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
#if !defined(OMNI_EXCEPT_DEF_HPP)
#define OMNI_EXCEPT_DEF_HPP 1

/* 
  The order of error reporting in the framework:
   -Default is to throw base class omni::exception (which derives from std::execption) on framework errors
   -If OMNI_NO_THROW is defined, then OMNI_TERMINATE, which is default defined as std::terminate(), is called
    on exception instead of throwing the omni::exception. Since std::terminate calls the installed
    std::terminate_handler, the Omni framework will leave it to the user to catch this if they wish
    by using the std::set_terminate function or using the omni::application::terminate_handler::attach.
    Otherwise, if no handler is installed, then std::abort is called, in which case the framework
    will catch that via the std::signal(SIGABRT, sig_handler) function call, but only if the user made
    use of the omni::application::run function(s). If no facility is installed, nor a 'run' function called
    to facilitate a std::abort trap, then the program will crash when std::abort is called upon std::terminate
   -If OMNI_NO_THROW && OMNI_NO_TERMINATE are defined then neither std::terminate is called nor are any
    exceptions thrown. All error handling is left to external validation (i.e. false/null values being returned
    or functions returning early [quick fail]). This is only recommended in the event that you're compiler does
    not support any exception handling mechanism or the library used does not support any standard functions
    (like terminate or abort), even in this case it is advised to change the std::terminate call below to whatever
    error mechanism your platform does support.
*/

#if defined(OMNI_NO_EXCEPT) && defined(OMNI_NO_THROW)
    #if defined(OMNI_NO_TERMINATE)
        // WARNING: UNDEFINED BEHAVIOUR WITHOUT ERROR HANDLING OF ANY KIND IN THE FRAMEWORK
        #if !defined(OMNI_ALLOW_UB)
            #error "WARNING: UNDEFINED BEHAVIOUR DETECTED! Specify OMNI_ALLOW_UB to disable this message."
        #endif
    #else
        #error "Cannot define OMNI_NO_EXCEPT and OMNI_NO_THROW without defining OMNI_NO_TERMINATE"
    #endif
#endif

// define OMNI_NO_EXCEPT if you do not wish to include these
#if !defined(OMNI_NO_EXCEPT)
    #include <exception>
    #include <stdexcept>
#endif
#include <omni/defs/debug.hpp>
// default of 'throw omni::exception' on error
#if !defined(OMNI_THROW)
    #define OMNI_THROW
#endif
// if no_throw, use std::terminate
#if defined(OMNI_NO_THROW)
    // DEV_NOTE: exceptions (i.e. the try {} catch block) only really 'cost' more if there's an actual exception
    #if defined(OMNI_THROW)
        #undef OMNI_THROW
    #endif
#endif
#if !defined(OMNI_TERMINATE)
    #define OMNI_TERMINATE std::terminate()
#endif
// if no_terminate, then default to undefined behaviour (unless otherwise specified)
#if defined(OMNI_NO_TERMINATE) && defined(OMNI_TERMINATE)
    #undef OMNI_TERMINATE
#endif

#if defined(OMNI_THROW)
    #define OMNI_THROW_FW(ex) throw ex;
    #define OMNI_EX_RET_FW(ret)
#else
    #if defined(OMNI_TERMINATE)
        #define OMNI_THROW_FW(ex) OMNI_TERMINATE;
        #define OMNI_EX_RET_FW(ret)
    #else
        #define OMNI_THROW_FW(ex)
        #define OMNI_EX_RET_FW(ret) return ret;
    #endif
#endif

// OMNI_TERMINATE_FW("debug error string")
// OMNI_TERMINATEV_FW("debug error string", ret)
#if defined(OMNI_TERMINATE)
    #define OMNI_TERMINATE_FW(str) OMNI_DBGE(str) OMNI_TERMINATE;
    #define OMNI_TERMINATEV_FW(str, val) OMNI_DBGEV(str, val) OMNI_TERMINATE;
#else
    /*
        DEV_NOTE: if std::terminate is not defined/used, then std::abort WILL be used here; this is because
        the OMNI_TERMINATE_FW macro is specifically to abort/terminate the process due to an unhandled error or
        a specific framework exception, such as the omni::sync::mutex destructor: it is undefined behaviour to
        leave a mutex locked on destruction, that is, you MUST unlock a mutex before it is destroyed. In these
        instances we want to make the 'undefined behaviour' defined, to which we will instigate an exception
        which will crash the program if not caught. However, it's not good to throw exceptions in the destructor
        of objects (due to stack unwinding), as such, we still want the program to NOT continue since that could
        lead to other issues, calling terminate/abort allows the user to handle these instances vs. calling
        std::exit which one would assume the program is terminating normally (vs. abnormally through an exception).
    */
    #include <cstdlib> // std::abort
    #define OMNI_TERMINATE_FW(str) OMNI_DBGE(str) std::abort();
    #define OMNI_TERMINATEV_FW(str, val) OMNI_DBGEV(str, val) std::abort();
#endif

// OMNI_ERR_FW("debug error string", omni::execption())
// OMNI_ERRV_FW("debug error string: ", err, omni::execption())
#define OMNI_ERR_FW(str, ex) OMNI_DBGE(str) OMNI_THROW_FW(ex)
#define OMNI_ERRV_FW(str, val, ex) OMNI_DBGEV(str, val) OMNI_THROW_FW(ex)

// OMNI_ERR_RET_FW("debug error string", omni::execption())
// OMNI_ERRV_RET_FW("debug error string: ", err, omni::execption())
#define OMNI_ERR_RET_FW(str, ex) OMNI_DBGE(str) OMNI_THROW_FW(ex)
#define OMNI_ERRV_RET_FW(str, val, ex) OMNI_DBGEV(str, val) OMNI_THROW_FW(ex)

// OMNI_ERR_RETV_FW("debug error string", omni::execption(), default_return)
// OMNI_ERRV_RETV_FW("debug error string: ", err, omni::execption(), default_return)
#define OMNI_ERR_RETV_FW(str, ex, ret) OMNI_DBGE(str) OMNI_THROW_FW(ex) OMNI_EX_RET_FW(ret)
#define OMNI_ERRV_RETV_FW(str, val, ex, ret) OMNI_DBGEV(str, val) OMNI_THROW_FW(ex) OMNI_EX_RET_FW(ret)

#if defined(OMNI_THROW)
    #define OMNI_TRY_FW try {
    #define OMNI_CATCH_FW } catch (omni::exception ex) { OMNI_TERMINATE_FW(ex.what()) } catch (...) { OMNI_TERMINATE_FW("Unknown exception") }
#else
    #define OMNI_TRY_FW 
    #define OMNI_CATCH_FW 
#endif

#endif // OMNI_EXCEPT_DEF_HPP
