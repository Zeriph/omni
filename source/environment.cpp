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
#include <omni/environment.hpp>

bool omni::environment::create_var(const std::string& name)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error creating environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    #if defined(OMNI_OS_WIN)
        #if !defined(OMNI_WIN_API)
            // sending an empty string to this function deletes the variable
            return (::_putenv_s(name.c_str(), "") == 0);
        #else
            return (::SetEnvironmentVariableA(name.c_str(), "") != 0);
        #endif
    #else
        return (::setenv(name.c_str(), "", 1) == 0);
    #endif
}

bool omni::environment::create_var(const std::wstring& name)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error creating environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    #if defined(OMNI_OS_WIN)
        #if !defined(OMNI_WIN_API)
            // sending an empty string to this function deletes the variable
            return (::_wputenv_s(name.c_str(), L"") == 0);
        #else
            return (::SetEnvironmentVariableW(name.c_str(), L"") != 0);
        #endif
    #else
        return (::setenv(omni::string::util::to_string(name).c_str(), "", 1) == 0);
    #endif
}

bool omni::environment::delete_var(const std::string& name)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error deleting environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    #if defined(OMNI_OS_WIN)
        #if !defined(OMNI_WIN_API)
            // sending an empty string to this function deletes the variable
            return (::_putenv_s(name.c_str(), "") == 0);
        #else
            return (::SetEnvironmentVariableA(name.c_str(), NULL) != 0);
        #endif
    #else
        return (::unsetenv(name.c_str()) == 0);
    #endif
}

bool omni::environment::delete_var(const std::wstring& name)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error deleting environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    #if defined(OMNI_OS_WIN)
        #if !defined(OMNI_WIN_API)
            // sending an empty string to this function deletes the variable
            return (::_wputenv_s(name.c_str(), L"") == 0);
        #else
            return (::SetEnvironmentVariableW(name.c_str(), NULL) != 0);
        #endif
    #else
        std::string n = omni::string::util::to_string(name);
        return (::unsetenv(n.c_str()) == 0);
    #endif
}

std::string omni::environment::expand_vars(const std::string& vars)
{
    if (vars.empty()) {
        OMNI_ERR_RETV_FW("Error expanding environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    #if defined(OMNI_OS_WIN)
        // #if defined(OMNI_WIN_API) // not applicable here
        // The size of the lpSrc and lpDst buffers is limited to 32k.
        char* cval = new char[OMNI_MAX_PATH_FW+1]();
        if (::ExpandEnvironmentStringsA(vars.c_str(), cval, OMNI_MAX_PATH_FW) != 0) {
            std::string ret(cval);
            delete[] cval;
            return ret;
        }
        delete[] cval;
    #else
        #if !defined(OMNI_ENV_WORDEXP) // default
            /* DEV_NOTE: some platforms do not implement the GLIBC wordexp (like OpenBSD)
            for many security reasons. As such it's not really a good idea to call this function
            without validating the user input; this is here for a convenience function. */
            std::string cmd = "echo \"" + vars + "\"";
            FILE *fp = ::popen(cmd.c_str(), "r");
            if (fp == NULL) {
                OMNI_ERR_RETV_FW("Error expanding environment variable: failed to open pipe", omni::exceptions::pipe_exception(), omni::string_t())
            }
            char* cval = new char[FILENAME_MAX]();
            std::string ret;
            while (std::fgets(cval, FILENAME_MAX-1, fp) != NULL) { ret.append(cval); }
            ::pclose(fp);
            delete[] cval;
            return ret;
        #else
            wordexp_t env;
            if (::wordexp(vars.c_str(), &env, 0) == 0) {
                std::string ret;
                char **w = env.we_wordv;
                for (unsigned int i = 0; i < env.we_wordc; ++i) { ret.append(w[i]); }
                ::wordfree(&env);
                return ret;
            }
            ::wordfree(&env);
        #endif
    #endif
    OMNI_ERRV_RETV_FW("Error expanding environment variable: ", OMNI_GLE_PRNT, omni::exceptions::environment_exception(OMNI_GLE), omni::string_t())
}

std::wstring omni::environment::expand_vars(const std::wstring& vars)
{
    if (vars.empty()) {
        OMNI_ERR_RETV_FW("Error expanding environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), omni::string_t())
    }
    #if defined(OMNI_OS_WIN)
        // #if defined(OMNI_WIN_API) // not applicable here
        // The size of the lpSrc and lpDst buffers is limited to 32k.
        wchar_t* cval = new wchar_t[OMNI_MAX_PATH_FW+1]();
        if (::ExpandEnvironmentStringsW(vars.c_str(), cval, OMNI_MAX_PATH_FW) != 0) {
            std::wstring ret(cval);
            delete[] cval;
            return ret;
        }
        delete[] cval;
    #else
        #if !defined(OMNI_ENV_WORDEXP) // default
            /* DEV_NOTE: some platforms do not implement the GLIBC wordexp (like OpenBSD)
            for many security reasons. As such it's not really a good idea to call this function
            without validating the user input; this is here for a convenience function. */
            std::string cmd = "echo \"" + omni::string::util::to_string(vars) + "\"";
            FILE *fp = ::popen(cmd.c_str(), "r");
            if (fp == NULL) {
                OMNI_ERR_RETV_FW("Error expanding environment variable: failed to open pipe", omni::exceptions::pipe_exception(), omni::string_t())
            }
            char* cval = new char[FILENAME_MAX]();
            std::string ret;
            while (std::fgets(cval, FILENAME_MAX-1, fp) != NULL) { ret.append(cval); }
            ::pclose(fp);
            delete[] cval;
            return omni::string::util::to_wstring(ret);
        #else
            std::string v = omni::string::util::to_string(vars);
            ::wordexp_t env;
            if (::wordexp(v.c_str(), &env, 0) == 0) {
                std::string ret;
                char **w = env.we_wordv;
                for (unsigned int i = 0; i < env.we_wordc; ++i) { ret.append(w[i]); }
                ::wordfree(&env);
                return omni::string::util::to_wstring(ret);
            }
            ::wordfree(&env);
        #endif
    #endif
    OMNI_ERRV_RETV_FW("Error expanding environment variable: ", OMNI_GLE_PRNT, omni::exceptions::environment_exception(OMNI_GLE), omni::string_t())
}

std::string omni::environment::get_var(const std::string& name)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error getting environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), omni::string_t())
    }
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_API)
            // The size of the lpSrc and lpDst buffers is limited to 32k.
            char* cval = new char[OMNI_MAX_PATH_FW+1]();
            if (::GetEnvironmentVariableA(name.c_str(), cval, OMNI_MAX_PATH_FW) != 0) {
                std::string ret(cval);
                delete[] cval;
                return ret;
            }
            delete[] cval;
        #else
            std::size_t sz;
            if (::getenv_s(&sz, NULL, 0, name.c_str()) == 0) {
                if (sz != 0) {
                    char* rval = new char[sz]();
                    std::string ret;
                    if (::getenv_s(&sz, rval, sz, name.c_str()) == 0) {
                        ret = std::string(rval);
                    }
                    delete[] rval;
                    return ret;
                }
            }
        #endif
    #else
        char* r = std::getenv(name.c_str());
        if (r != NULL) { return std::string(r); }
    #endif
    OMNI_ERRV_RETV_FW("Error retrieving environment variable: ", OMNI_GLE_PRNT, omni::exceptions::environment_exception(OMNI_GLE), omni::string_t())
}

std::wstring omni::environment::get_var(const std::wstring& name)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error getting environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), omni::string_t())
    }
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_API)
            // The size of the lpSrc and lpDst buffers is limited to 32k.
            wchar_t* cval = new wchar_t[OMNI_MAX_PATH_FW+1]();
            if (::GetEnvironmentVariableW(name.c_str(), cval, OMNI_MAX_PATH_FW) != 0) {
                std::wstring ret(cval);
                delete[] cval;
                return ret;
            }
            delete[] cval;
        #else
            std::size_t sz;
            if (::_wgetenv_s(&sz, NULL, 0, name.c_str()) == 0) {
                if (sz != 0) {
                    wchar_t* rval = new wchar_t[sz]();
                    std::wstring ret;
                    if (::_wgetenv_s(&sz, rval, sz, name.c_str()) == 0) {
                        ret = std::wstring(rval);
                    }
                    delete[] rval;
                    return ret;
                }
            }
        #endif
    #else
        std::string v = omni::string::util::to_string(name);
        char* r = std::getenv(v.c_str());
        if (r != NULL) { return omni::string::util::to_string_t(r); }
    #endif
    OMNI_ERRV_RETV_FW("Error retrieving environment variable: ", OMNI_GLE_PRNT, omni::exceptions::environment_exception(OMNI_GLE), omni::string_t())
}

bool omni::environment::set_var(const std::string& name, const std::string& val)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error setting environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    if (val.empty()) {
        OMNI_ERR_RETV_FW("Error setting environment variable: value cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    if (val.size() > OMNI_MAX_PATH_FW) {
        OMNI_ERR_RETV_FW("Error setting environment variable: value cannot be greater than 32,767 characters", omni::exceptions::invalid_environment_variable(), false)
    }
    #if defined(OMNI_OS_WIN)
        #if !defined(OMNI_WIN_API)
            // sending an empty string to this function deletes the variable
            return (::_putenv_s(name.c_str(), val.c_str()) == 0);
        #else
            return (::SetEnvironmentVariableA(name.c_str(), val.c_str()) != 0);
        #endif
    #else
        // always overwrite
        return (::setenv(name.c_str(), val.c_str(), 1) == 0);
    #endif
}

bool omni::environment::set_var(const std::wstring& name, const std::wstring& val)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error setting environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    if (val.empty()) {
        OMNI_ERR_RETV_FW("Error setting environment variable: value cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    if (val.size() > OMNI_MAX_PATH_FW) {
        OMNI_ERR_RETV_FW("Error setting environment variable: value cannot be greater than 32,767 characters", omni::exceptions::invalid_environment_variable(), false)
    }
    #if defined(OMNI_OS_WIN)
        #if !defined(OMNI_WIN_API)
            // sending an empty string to this function deletes the variable
            return (::_wputenv_s(name.c_str(), val.c_str()) == 0);
        #else
            return (::SetEnvironmentVariableW(name.c_str(), val.c_str()) != 0);
        #endif
    #else
        std::string n = omni::string::util::to_string(name);
        std::string v = omni::string::util::to_string(val);
        // always overwrite
        return (::setenv(n.c_str(), v.c_str(), 1) == 0);
    #endif
}

bool omni::environment::var_exists(const std::string& name)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error getting environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    bool ret = false;
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_API)
            // The size of the lpSrc and lpDst buffers is limited to 32k.
            char* cval = new char[OMNI_MAX_PATH_FW+1]();
            if (::GetEnvironmentVariableA(name.c_str(), cval, OMNI_MAX_PATH_FW) != 0) { ret = true; }
            delete[] cval;
        #else
            std::size_t sz;
            if (::getenv_s(&sz, NULL, 0, name.c_str()) == 0) {
                ret = (sz != 0);
            }
        #endif
    #else
        char* r = std::getenv(name.c_str());
        if (r != NULL) { ret = true; }
    #endif
    return ret;
}

bool omni::environment::var_exists(const std::wstring& name)
{
    if (name.empty()) {
        OMNI_ERR_RETV_FW("Error getting environment variable: name cannot be empty", omni::exceptions::invalid_environment_variable(), false)
    }
    bool ret = false;
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_API)
            // The size of the lpSrc and lpDst buffers is limited to 32k.
            wchar_t* cval = new wchar_t[OMNI_MAX_PATH_FW+1]();
            if (::GetEnvironmentVariableW(name.c_str(), cval, OMNI_MAX_PATH_FW) != 0) { ret = true; }
            delete[] cval;
        #else
            std::size_t sz;
            if (::_wgetenv_s(&sz, NULL, 0, name.c_str()) == 0) {
                ret = (sz != 0);
            }
        #endif
    #else
        std::string v = omni::string::util::to_string(name);
        char* r = std::getenv(v.c_str());
        if (r != NULL) { ret = true; }
    #endif
    return ret;
}
