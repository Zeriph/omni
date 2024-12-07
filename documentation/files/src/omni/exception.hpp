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
#if !defined(OMNI_EXCEPTIONS_HPP)
#define OMNI_EXCEPTIONS_HPP 1

#include <omni/defs/global.hpp>
// for the order of exception handling, see the following header
#include <omni/defs/except_def.hpp>

#if defined(OMNI_THROW)
    #include <iostream>
    #include <string>
    #include <sstream>
    #include <omni/defs/consts.hpp>
    
    // DEV_NOTE: If you wish to have something other than std::terminate be called below, define OMNI_EXCEPTION_TERMINATE
    #if !defined(OMNI_EXCEPTION_TERMINATE)
        // std::terminate is called when an exception happens within an exception (i.e. a null pointer reference)
        #define OMNI_EXCEPTION_TERMINATE OMNI_TERMINATE;
    #endif
    #define OMNI_ERR_APPEND_FW(val) std::stringstream cval; cval << val; this->m_what.append(cval.str())

    // DEV_NOTE: the exception specification for throw() is an implicit noexcept(false)
    // DEV_NOTE: all exceptions in Omni will be explicit for single parameter ctor's to avoid any collision
    
    namespace omni {
        /** exception is used to facilitate Omni Library specific exceptions */
        class exception : virtual public std::exception
        {
            public:
                exception() OMNI_FUNC_NO_THROW : m_what(OMNI_GENERAL_EXCEPTION_STR) {}

                explicit exception(const char* reason) OMNI_FUNC_NO_THROW : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                
                explicit exception(const std::string& reason) OMNI_FUNC_NO_THROW : m_what(reason) {}
                
                exception(const char* reason, const char* extra) OMNI_FUNC_NO_THROW : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    if (extra) { this->m_what.append(extra); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                
                exception(const char* reason, const char* extra, int errnum) OMNI_FUNC_NO_THROW : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR)
                        OMNI_EXCEPTION_TERMINATE
                    }
                    if (extra) { this->m_what.append(extra); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR)
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                exception(const char* reason, const char* extra, long errnum) OMNI_FUNC_NO_THROW : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    if (extra) { this->m_what.append(extra); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }

                exception(const char* reason, const char* extra, std::size_t errnum) OMNI_FUNC_NO_THROW : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    if (extra) { this->m_what.append(extra); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }

                exception(const std::string& reason, const std::string& extra) OMNI_FUNC_NO_THROW : m_what(reason)
                {
                    this->m_what.append(extra);
                }
                
                exception(const std::string& reason, const std::string& extra, int errnum) OMNI_FUNC_NO_THROW : m_what(reason)
                {
                    this->m_what.append(extra);
                    OMNI_ERR_APPEND_FW(errnum);
                }

                exception(const std::string& reason, const std::string& extra, long errnum) OMNI_FUNC_NO_THROW : m_what(reason)
                {
                    this->m_what.append(extra);
                    OMNI_ERR_APPEND_FW(errnum);
                }

                exception(const std::string& reason, const std::string& extra, std::size_t errnum) OMNI_FUNC_NO_THROW : m_what(reason)
                {
                    this->m_what.append(extra);
                    OMNI_ERR_APPEND_FW(errnum);
                }

                exception(const char* reason, int errnum) OMNI_FUNC_NO_THROW : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                exception(const std::string& reason, int errnum) OMNI_FUNC_NO_THROW : m_what(reason)
                {
                    OMNI_ERR_APPEND_FW(errnum);
                }

                exception(const char* reason, long errnum) OMNI_FUNC_NO_THROW : m_what("") 
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                exception(const std::string& reason, long errnum) OMNI_FUNC_NO_THROW : m_what(reason)
                {
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                exception(const char* reason, std::size_t errnum) OMNI_FUNC_NO_THROW : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                exception(const std::string& reason, std::size_t errnum) OMNI_FUNC_NO_THROW : m_what(reason)
                {
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual ~exception() OMNI_DTOR_NO_THROW
                {

                }
                
                virtual void append(const char* ex)
                {
                    if (ex) { this->m_what.append(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                
                virtual void append(const std::string& ex)
                {
                    this->m_what.append(ex);
                }
                
                virtual void append(const char* ex, int errnum)
                {
                    if (ex) { this->m_what.append(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual void append(const std::string& ex, int errnum)
                {
                    this->m_what.append(ex);
                    OMNI_ERR_APPEND_FW(errnum);
                }

                virtual void append(const char* ex, long errnum)
                {
                    if (ex) { this->m_what.append(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual void append(const std::string& ex, long errnum)
                {
                    this->m_what.append(ex);
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual void append(const char* ex, std::size_t errnum)
                {
                    if (ex) { this->m_what.append(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual void append(const std::string& ex, std::size_t errnum)
                {
                    this->m_what.append(ex);
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual const char* what() const throw() { return this->m_what.c_str(); }
                
                virtual void seterr(const char* ex)
                {
                    if (ex) { this->m_what = std::string(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                
                virtual void seterr(const std::string& ex) { this->m_what = ex; }
                
                virtual void seterr(const char* ex, int errnum)
                {
                    if (ex) { this->m_what = std::string(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual void seterr(const std::string& ex, int errnum)
                {
                    this->m_what = ex;
                    OMNI_ERR_APPEND_FW(errnum);
                }

                virtual void seterr(const char* ex, long errnum)
                {
                    if (ex) { this->m_what = std::string(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual void seterr(const std::string& ex, long errnum)
                {
                    this->m_what = ex;
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual void seterr(const char* ex, std::size_t errnum)
                {
                    if (ex) { this->m_what = std::string(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(errnum);
                }
                
                virtual void seterr(const std::string& ex, std::size_t errnum)
                {
                    std::stringstream cval(ex);
                    cval << errnum;
                    this->m_what = cval.str();
                }
                
                operator std::string() const
                {
                    return this->m_what;
                }
                
                operator std::wstring() const
                {
                    std::wstringstream o;
                    o << this->m_what.c_str();
                    return o.str();
                }
                
                friend std::ostream& operator<<(std::ostream& s, const omni::exception& e)
                {
                    s << e.m_what;
                    return s;
                }
                
                friend std::wostream& operator<<(std::wostream& s, const omni::exception& e)
                {
                    s << e.m_what.c_str();
                    return s;
                }
                
            protected:
                std::string m_what;
        };
    }
    
    // include the omni::exceptions namespace and it is exceptions
    #include <omni/xx/exceptions.hxx>
    #undef OMNI_ERR_APPEND_FW
#endif // OMNI_THROW
#endif // OMNI_EXCEPTIONS_HPP
