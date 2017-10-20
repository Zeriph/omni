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
#if !defined(OMNI_TYPE_VALUE_HPP)
#define OMNI_TYPE_VALUE_HPP 1
#include <omni/type.hpp>

namespace omni {
    class type_value
    {
        public:
            type_value() : m_id() {}
            type_value(const omni::type_value& cp) : m_id(cp.m_id) {}
            type_value(std::size_t id) : m_id(id) {} // implicit create from hash
            
            template < typename T >
            type_value(const omni::type<T>& cp) : m_id(cp.hash()) {} // implicit create from omni::type
            
            ~type_value() {}
            
            template < typename T >
            inline bool after(const omni::type<T>& o) const
            {
                return this->m_id > o.hash();
            }
            
            inline bool after(const omni::type_value& o) const
            {
                return this->m_id > o.m_id;
            }
            
            inline bool after(std::size_t id) const
            {
                return this->m_id > id;
            }
            
            template < typename T >
            inline bool before(const omni::type<T>& o) const
            {
                return this->m_id < o.hash();
            }
            
            inline bool before(const omni::type_value& o) const
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
            
            template < typename T >
            omni::type_value& operator=(const omni::type<T>& o)
            {
                this->m_id = o.hash();
                return *this;
            }
            
            omni::type_value& operator=(const omni::type_value& o)
            {
                this->m_id = o.m_id;
                return *this;
            }
            
            omni::type_value& operator=(std::size_t id)
            {
                this->m_id = id;
                return *this;
            }
            
            template < typename T >
            bool operator<(const omni::type<T>& o) const
            {
                return this->m_id < o.hash();
            }
            
            bool operator<(const omni::type_value& o) const
            {
                return this->m_id < o.m_id;
            }
            
            bool operator<(std::size_t id) const
            {
                return this->m_id < id;
            }
            
            template < typename T >
            bool operator>(const omni::type<T>& o) const
            {
                return this->m_id > o.hash();
            }
            
            bool operator>(const omni::type_value& o) const
            {
                return this->m_id > o.m_id;
            }
            
            bool operator>(std::size_t id) const
            {
                return this->m_id > id;
            }
            
            template < typename T >
            bool operator==(const omni::type<T>& o) const
            {
                return this->m_id == o.hash();
            }
            
            bool operator==(const omni::type_value& o) const
            {
                return this->m_id == o.m_id;
            }
            
            bool operator==(std::size_t id) const
            {
                return this->m_id == id;
            }
            
            template < typename T >
            bool operator!=(const omni::type<T>& o) const
            {
                return !(this->m_id == o.hash());
            }
            
            bool operator!=(const omni::type_value& o) const
            {
                return !(this->m_id == o.m_id);
            }
            
            bool operator!=(std::size_t id) const
            {
                return !(this->m_id == id);
            }
            
        private:
            std::size_t m_id;
    };
}

#endif // OMNI_TYPE_VALUE_HPP
