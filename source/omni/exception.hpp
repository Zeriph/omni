/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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

// for the order of exception handling, see the following header
#include <omni/defs/except_def.hpp>

#if defined(OMNI_THROW)
    #include <iostream>
    #include <string>
    #include <sstream>
    #include <omni/defs/consts.hpp>
    
    /* DEV_NOTE: If you wish to have something other than std::terminate be called below, define OMNI_EXCEPTION_TERMINATE */
    #if !defined(OMNI_EXCEPTION_TERMINATE)
        // std::terminate is called when an exception happens within an exception (i.e. a null pointer reference)
        #define OMNI_EXCEPTION_TERMINATE OMNI_TERMINATE;
    #endif
    #define OMNI_ERR_APPEND_FW(val) std::stringstream cval; cval << val; this->m_what.append(cval.str())
    /* DEV_NOTE: the exception specification for 'throw()' is an implicit 'noexcept(false)' */
    
    namespace omni {
        /** exception is used to facilitate Omni Framework specific exceptions */
        class exception : virtual public std::exception
        {
            public:
                exception() throw() : m_what(OMNI_GENERAL_EXCEPTION_STR) {}
                
                explicit exception(const char* reason) throw() : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                
                explicit exception(const std::string& reason) throw() : m_what(reason) {}
                
                exception(const char* reason, const char* extra) throw() : m_what("")
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
                
                exception(const char* reason, const char* extra, int err) throw() : m_what("")
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
                    OMNI_ERR_APPEND_FW(err);
                }
                
                exception(const char* reason, const char* extra, long err) throw() : m_what("")
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
                    OMNI_ERR_APPEND_FW(err);
                }

                exception(const char* reason, const char* extra, std::size_t err) throw() : m_what("")
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
                    OMNI_ERR_APPEND_FW(err);
                }

                exception(const std::string& reason, const std::string& extra) throw() : m_what(reason)
                {
                    this->m_what.append(extra);
                }
                
                exception(const std::string& reason, const std::string& extra, int err) throw() : m_what(reason)
                {
                    this->m_what.append(extra);
                    OMNI_ERR_APPEND_FW(err);
                }

                exception(const std::string& reason, const std::string& extra, long err) throw() : m_what(reason)
                {
                    this->m_what.append(extra);
                    OMNI_ERR_APPEND_FW(err);
                }

                exception(const std::string& reason, const std::string& extra, std::size_t err) throw() : m_what(reason)
                {
                    this->m_what.append(extra);
                    OMNI_ERR_APPEND_FW(err);
                }

                exception(const char* reason, int err) throw() : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                exception(const std::string& reason, int err) throw() : m_what(reason)
                {
                    OMNI_ERR_APPEND_FW(err);
                }

                exception(const char* reason, long err) throw() : m_what("") 
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                exception(const std::string& reason, long err) throw() : m_what(reason)
                {
                    OMNI_ERR_APPEND_FW(err);
                }
                
                exception(const char* reason, std::size_t err) throw() : m_what("")
                {
                    if (reason) { this->m_what.append(reason); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                exception(const std::string& reason, std::size_t err) throw() : m_what(reason)
                {
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual ~exception() throw() {}
                
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
                
                virtual void append(const char* ex, int err)
                {
                    if (ex) { this->m_what.append(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual void append(const std::string& ex, int err)
                {
                    this->m_what.append(ex);
                    OMNI_ERR_APPEND_FW(err);
                }

                virtual void append(const char* ex, long err)
                {
                    if (ex) { this->m_what.append(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual void append(const std::string& ex, long err)
                {
                    this->m_what.append(ex);
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual void append(const char* ex, std::size_t err)
                {
                    if (ex) { this->m_what.append(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual void append(const std::string& ex, std::size_t err)
                {
                    this->m_what.append(ex);
                    OMNI_ERR_APPEND_FW(err);
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
                
                virtual void seterr(const char* ex, int err)
                {
                    if (ex) { this->m_what = std::string(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual void seterr(const std::string& ex, int err)
                {
                    this->m_what = ex;
                    OMNI_ERR_APPEND_FW(err);
                }

                virtual void seterr(const char* ex, long err)
                {
                    if (ex) { this->m_what = std::string(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual void seterr(const std::string& ex, long err)
                {
                    this->m_what = ex;
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual void seterr(const char* ex, std::size_t err)
                {
                    if (ex) { this->m_what = std::string(ex); }
                    else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                    OMNI_ERR_APPEND_FW(err);
                }
                
                virtual void seterr(const std::string& ex, std::size_t err)
                {
                    std::stringstream cval(ex);
                    cval << err;
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
    
    // include the omni::exceptions namespace and it's exceptions
    #include <omni/xx/exceptions.hxx>
    #undef OMNI_ERR_APPEND_FW
#endif // OMNI_NO_THROW
#endif // OMNI_EXCEPTIONS_HPP
