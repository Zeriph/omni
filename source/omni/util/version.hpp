/*
 * This file is part of the Omni C++ framework
 * 
 * Copyright 2015, Zeriph Enterprises, LLC
 * 
 * PERMISSION TO USE, COPY, MODIFY, AND/OR DISTRIBUTE THIS SOFTWARE FOR ANY
 * PURPOSE WITH OR WITHOUT FEE IS HEREBY GRANTED, PROVIDED THAT THE ABOVE
 * COPYRIGHT NOTICE AND THIS PERMISSION NOTICE APPEAR IN ALL COPIES.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 * 
 * ZERIPH DOES NOT MAKE ANY ASSURANCES WITH REGARD TO THE ACCURACY OF THE RESULTS
 * OR OUTPUT THAT DERIVES FROM SUCH USE OF ANY SOFTWARE.
 */
#if !defined(OMNI_VERSION_HPP)
#define OMNI_VERSION_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/string_t.hpp>
#include <omni/types/seq_t.hpp>
#include <omni/ostream.hpp>
#include <omni/exception.hpp>

namespace omni {
    namespace util {
        class version
        {
            public:
                version();
                version(unsigned int mj);
                version(unsigned int mj, unsigned int mn);
                version(unsigned int mj, unsigned int mn, unsigned int bld);
                version(unsigned int mj, unsigned int mn, unsigned int bld, unsigned int rv);
                explicit version(const std::string& str);
                explicit version(const std::wstring& str);
                version(const omni::util::version& cp);
                
                virtual ~version()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                }
                
                static inline omni::util::version parse(const std::string& str)
                {
                    return omni::util::version::_parse(str);
                }
                
                static inline bool tryparse(const std::string& str, omni::util::version& out)
                {
                    return omni::util::version::_tryparse(str, out);
                }
                
                // maj/major can't be used as a name (some compilers complain)
                inline unsigned int maj_value() const
                {
                    return this->m_maj;
                }
                
                // min/minor can't be used as a name (some compilers complain)
                inline unsigned int min_value() const
                {
                    return this->m_min;
                }
                
                inline unsigned int build() const
                {
                    return this->m_bld;
                }
                
                inline unsigned int revision() const
                {
                    return this->m_rev;
                }
                
                inline const omni::string_t to_string_t() const
                {
                    omni::sstream_t o;
                    o << this->m_maj << "." << this->m_min << "." <<
                         this->m_bld << "." << this->m_rev;
                    return o.str();
                }
                
                inline const std::string to_string() const
                {
                    std::stringstream o;
                    o << this->m_maj << "." << this->m_min << "." <<
                         this->m_bld << "." << this->m_rev;
                    return o.str();
                }
                
                inline const std::wstring to_wstring() const
                {
                    std::wstringstream o;
                    o << this->m_maj << "." << this->m_min << "." <<
                         this->m_bld << "." << this->m_rev;
                    return o.str();
                }
                
                operator std::string() const
                {
                    return this->to_string();
                }
                
                operator std::wstring() const
                {
                    return this->to_wstring();
                }
                
                omni::util::version& operator=(const omni::util::version& o)
                {
                    OMNI_ASSIGN_FW(o)
                    this->_copy(o);
                    return *this;
                }

                omni::util::version& operator=(const std::string& str)
                {
                    this->_copy(omni::util::version::_parse(str));
                    return *this;
                }

                omni::util::version& operator=(const std::wstring& str)
                {
                    this->_copy(omni::util::version::_parse(str));
                    return *this;
                }

                bool operator==(const std::string& str) const
                {
                    omni::util::version t;
                    if (!omni::util::version::_tryparse(str, t)) { return false; }
                    return (*this == t);
                }

                bool operator==(const std::wstring& str) const
                {
                    omni::util::version t;
                    if (!omni::util::version::_tryparse(str, t)) { return false; }
                    return (*this == t);
                }

                bool operator==(const omni::util::version& o) const
                {
                    if (this == &o) { return true; }
                    return (this->m_maj == o.m_maj &&
                            this->m_min == o.m_min &&
                            this->m_bld == o.m_bld &&
                            this->m_rev == o.m_rev)
                            OMNI_EQUAL_FW(o);
                }

                bool operator!=(const omni::util::version &o) const
                {
                    return !(*this == o);
                }
                
                OMNI_MEMBERS_FW(omni::util::version) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::util::version)
                
            private:
                static omni::util::version _parse(const std::string& v);
                static omni::util::version _parse(const std::wstring& v);
                static bool _tryparse(const std::string& v, omni::util::version& _out);
                static bool _tryparse(const std::wstring& v, omni::util::version& _out);
                
                void _copy(const omni::util::version& o)
                {
                    this->m_maj = o.m_maj;
                    this->m_min = o.m_min;
                    this->m_bld = o.m_bld;
                    this->m_rev = o.m_rev;
                }
            
                #if defined(OMNI_TYPE_INFO)
                    omni::type<omni::util::version> m_type;
                #endif
                /** The major version number */
                unsigned int m_maj; // g++ doesn't like major/minor as member names???
                /** The minor version number */
                unsigned int m_min;
                /** The build version number */
                unsigned int m_bld;
                /** The revision number */
                unsigned int m_rev;
        };
    }
}

#endif // OMNI_VERSION_HPP
