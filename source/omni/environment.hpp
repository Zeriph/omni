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
#if !defined(OMNI_ENVIRONMENT_HPP)
#define OMNI_ENVIRONMENT_HPP 1
#if !defined(OMNI_OS_WIN)
    #if defined(OMNI_ENV_WORDEXP)
        /* DEV_NOTE: these functions, if used improperly (not validating
        user input) will open your software to security holes!!!
        
        DEV_NOTE: the wordexp function is not available on all systems 
        to wit, it does not "work" portably on all systems either,
        to this effect, the current way of expanding an env. string
        is via popen (pipes) and the "echo" shell command. If you wish
        to use the wordexp function on your system, compile with the
        OMNI_ENV_WORDEXP preprocessor flag */
        #include <wordexp.h>
    #endif
#endif
#include <omni/string/util.hpp> // has cstdlib
#include <omni/exception.hpp>

/*
    DEV_NOTE: while we could implement an enum with the OS's from os.h, this isn't C# and the need to determine OS
    at runtime won't be something that will happen. We build C++ for a target, even if cross-compiling, we specify
    which OS/toolchain we're targeting and thus we can "bake in" features or specifics based on the target using
    the defined macro's in os.h, instead of determining at run time. As such, we won't be implementing any of the
    C# System.OperatingSystem functionality via run-time code (e.g. function calls).

    Additionally, version checking can be done at compile time as well, to avoid run-time calls to deprecated API.
*/

namespace omni {
    namespace environment {
        #if !defined(OMNI_NO_CONSTS)
            OMNI_CONSTEXT_FW const omni::char_t NEW_LINE[] OMNI_EXT_ASSN_FW(OMNI_STRW(OMNI_NEW_LINE));
        #endif
        
        bool create_var(const std::string& name);
        bool create_var(const std::wstring& name);
        
        inline bool create_var(const char* name)
        {
            if (!name) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            return omni::environment::create_var(std::string(name));
        }
        
        inline bool create_var(const wchar_t* name)
        {
            if (!name) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            return omni::environment::create_var(std::wstring(name));
        }
        
        bool delete_var(const std::string& name);
        bool delete_var(const std::wstring& name);
        
        inline bool delete_var(const char* name)
        {
            if (!name) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::delete_var(std::string(name));
        }
        
        inline bool delete_var(const wchar_t* name)
        {
            if (!name) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::delete_var(std::wstring(name));
        }
        
        std::string expand_vars(const std::string& vars);
        std::wstring expand_vars(const std::wstring& vars);
        
        inline std::string expand_vars(const char* vars)
        {
            if (!vars) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::expand_vars(std::string(vars));
        }
        
        inline std::wstring expand_vars(const wchar_t* vars)
        {
            if (!vars) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::expand_vars(std::wstring(vars));
        }
        
        std::string get_var(const std::string& name);
        std::wstring get_var(const std::wstring& name);
        
        inline std::string get_var(const char* name)
        {
            if (!name) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::get_var(std::string(name));
        }
        
        inline std::wstring get_var(const wchar_t* name)
        {
            if (!name) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::get_var(std::wstring(name));
        }
        
        bool set_var(const std::string& name, const std::string& val);
        bool set_var(const std::wstring& name, const std::wstring& val);
        
        inline bool set_var(const char* name, const char* val)
        {
            if (name == OMNI_NULL_PTR || val == OMNI_NULL_PTR) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::set_var(std::string(name), std::string(val));
        }
        
        inline bool set_var(const wchar_t* name, const wchar_t* val)
        {
            if (name == OMNI_NULL_PTR || val == OMNI_NULL_PTR) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::set_var(std::wstring(name), std::wstring(val));
        }
        
        bool var_exists(const std::string& name);
        bool var_exists(const std::wstring& name);
        
        inline bool var_exists(const char* name)
        {
            if (!name) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::var_exists(std::string(name));
        }
        
        inline bool var_exists(const wchar_t* name)
        {
            if (!name) {
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
            }
            return omni::environment::var_exists(std::wstring(name));
        }
    }
}

#endif // OMNI_ENVIRONMENT_HPP
