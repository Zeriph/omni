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
#if !defined(OMNI_TYPE_HPP)
#define OMNI_TYPE_HPP 1
#include <cstddef>

#define omni_typeid(T) omni::type_id<T>()
namespace omni {
    template < typename T >
    std::size_t type_id()
    {
        static char tid;
        return reinterpret_cast<std::size_t>(&tid);
    }
    
    template < typename T >
    inline std::size_t type_id(const T& t)
    {
        return omni::type_id<T>();
    }
    
    template < typename T >
    inline std::size_t type_id(const T *const t)
    {
        return omni::type_id<T>();
    }
    
    template < typename T, typename C >
    inline bool type_of()
    {
        return omni::type_id<T>() == omni::type_id<C>();
    }
    
    template < typename T, typename C >
    inline bool type_of(const C& c)
    {
        return omni::type_of<T, C>();
    }
    
    template < typename T, typename C >
    inline bool type_of(const C *const c)
    {
        return omni::type_of<T, C>();
    }
    
    template < typename T, typename C >
    inline bool type_of(const T& t, const C& c)
    {
        return omni::type_of<T, C>();
    }
    
    template < typename T, typename C >
    inline bool type_of(const T *const t, const C *const c)
    {
        return omni::type_of<T, C>();
    }
    
    // type represents an immutable basic id type
    template < typename T >
    class type
    {
        public:
            type() : m_id(omni::type_id<T>()) {}
            type(const omni::type<T>& cp) : m_id(cp.m_id) {} // same types
            ~type() {}
            
            template < typename C >
            inline bool after(const omni::type<C>& o) const
            {
                return this->m_id > o.m_id;
            }
            
            inline bool after(const omni::type<T>& o) const
            {
                return this->m_id > o.m_id;
            }
            
            inline bool after(std::size_t id) const
            {
                return this->m_id > id;
            }
            
            template < typename C >
            inline bool before(const omni::type<C>& o) const
            {
                return this->m_id < o.m_id;
            }
            
            inline bool before(const omni::type<T>& o) const
            {
                return this->m_id < o.m_id;
            }
            
            inline bool before(std::size_t id) const
            {
                return this->m_id < id;
            }
            
            inline std::size_t hash() const
            {
                return this->m_id;
            }
            
            omni::type<T>& operator=(const omni::type<T>& other)
            {
                /* no need to set this->m_id = other.m_id;
                these are the same types and thus have the same ID.
                so just return this */
                return *this;
            }
            
            template < typename C >
            bool operator<(const omni::type<C>& o) const
            {
                return this->m_id < o.m_id;
            }
            
            bool operator<(const omni::type<T>& o) const
            {
                return this->m_id < o.m_id;
            }
            
            bool operator<(std::size_t id) const
            {
                return this->m_id < id;
            }
            
            template < typename C >
            bool operator>(const omni::type<C>& o) const
            {
                return this->m_id > o.m_id;
            }
            
            bool operator>(const omni::type<T>& o) const
            {
                return this->m_id > o.m_id;
            }
            
            bool operator>(std::size_t id) const
            {
                return this->m_id > id;
            }
            
            template < typename C >
            bool operator==(const omni::type<C>& o) const
            {
                return this->m_id == o.m_id;
            }
            
            bool operator==(const omni::type<T>& o) const
            {
                return this->m_id == o.m_id;
            }
            
            bool operator==(std::size_t id) const
            {
                return this->m_id == id;
            }
            
            template < typename C >
            bool operator!=(const omni::type<C>& o) const
            {
                return !(this->m_id == o.m_id);
            }
            
            bool operator!=(const omni::type<T>& o) const
            {
                return !(this->m_id == o.m_id);
            }
            
            bool operator!=(std::size_t id) const
            {
                return !(this->m_id == id);
            }
            
        private:
            template < typename C >
            type(const omni::type<C>& cp); // = delete
            template < typename C >
            omni::type<T>& operator=(const omni::type<C>& other); // = delete
            
            std::size_t m_id;
    };
}

#endif // OMNI_TYPE_HPP
