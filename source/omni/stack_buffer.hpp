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
#if !defined(OMNI_STACK_BUFFER_HPP)
#define OMNI_STACK_BUFFER_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/string/util.hpp>
#include <cstdarg>

namespace omni {
    template < typename T, uint16_t SZ >
    class stack_buffer
    {
        public:
            typedef const T* const_iterator;
            typedef T* iterator;
            typedef T value_type;

            stack_buffer() : 
                OMNI_CTOR_FW(omni::stack_buffer)
                m_data()
            {
                if (SZ == 0) {
                    OMNI_ERR_FW(OMNI_INDEX_OOR_STR, omni::exceptions::index_out_of_range())
                }
                std::memset(this->m_data, 0, SZ);
            }

            stack_buffer(const T (&data)[SZ]) : 
                OMNI_CTOR_FW(omni::stack_buffer)
                m_data()
            {
                if (SZ == 0) {
                    OMNI_ERR_FW(OMNI_INDEX_OOR_STR, omni::exceptions::index_out_of_range())
                }
                std::memcpy(this->m_data, data, SZ);
            }

            stack_buffer(T val1, ...) : 
                OMNI_CTOR_FW(omni::stack_buffer)
                m_data()
            {
                if (SZ == 0) {
                    OMNI_ERR_FW(OMNI_INDEX_OOR_STR, omni::exceptions::index_out_of_range())
                }
                va_list args;
                va_start(args, val1);
                this->m_data[0] = val1;
                for (size_t i = 1; i < SZ; ++i) {
                    this->m_data[i] = va_arg(args, value_type);
                }
                va_end(args);
            }

            template < uint16_t OTHER_SZ >
            stack_buffer(const T (&data)[OTHER_SZ]) : 
                OMNI_CTOR_FW(omni::stack_buffer)
                m_data()
            {
                if ((OTHER_SZ == 0) || (OTHER_SZ > SZ)) {
                    OMNI_ERR_FW(OMNI_INDEX_OOR_STR, omni::exceptions::index_out_of_range())
                }
                std::memset(this->m_data, 0, SZ);
                std::memcpy(this->m_data, data, OTHER_SZ);
            }
            
            stack_buffer(const stack_buffer& cp) :
                OMNI_CTOR_FW(omni::stack_buffer)
                m_data()
            {
                if (SZ == 0) {
                    OMNI_ERR_FW(OMNI_INDEX_OOR_STR, omni::exceptions::index_out_of_range())
                }
                std::memcpy(this->m_data, cp.m_data, SZ);
            }

            ~stack_buffer()
            {
                OMNI_TRY_FW
                std::memset(this->m_data, 0, SZ);
                OMNI_DTOR_FW
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            T& at(uint16_t index)
            {
                if (index > SZ) {
                    OMNI_ERRV_RETV_FW(OMNI_INDEX_OOR_STR, index, omni::exceptions::index_out_of_range(index), T())
                }
                return this->m_data[index];
            }

            T* back()
            {
                return this->m_data + SZ;
            }

            iterator begin()
            {
                return this->m_data;
            }

            const_iterator begin() const
            {
                return const_cast<const T*>(&this->m_data[0]);
            }

            size_t capacity() const
            {
                return SZ * sizeof(T);
            }

            T* data()
            {
                return this->m_data;
            }

            const T *const data() const
            {
                return this->m_data;
            }
            
            iterator end()
            {
                return this->m_data + SZ;
            }

            const_iterator end() const
            {
                return this->m_data + SZ;
            }

            T* front()
            {
                return this->m_data;
            }

            void swap(stack_buffer& other)
            {
                if (this != &other) {
                    std::swap(this->m_data, other.m_data);
                }
            }

            void swap(T (&data)[SZ])
            {
                if (&this->m_data != &data) {
                    std::swap(this->m_data, data);
                }
            }

            uint16_t size() const
            {
                return SZ;
            }

            void zeroize()
            {
                std::memset(this->m_data, 0, sizeof(T)*SZ);
            }

            omni::string_t to_string_t() const
            {
                omni::sstream_t s;
                s << this->m_data;
                return s.str();
            }

            std::string to_string() const
            {
                std::stringstream s;
                s << this->m_data;
                return s.str();
            }

            std::wstring to_wstring() const
            {
                std::wstringstream s;
                s << this->m_data;
                return s.str();
            }           

            stack_buffer& operator=(const stack_buffer& other)
            {
                if (this != &other) {
                    OMNI_ASSIGN_FW(other)
                    std::memcpy(this->m_data, other.m_data, SZ);
                }
                return *this;
            }

            stack_buffer& operator=(const T (&data)[SZ])
            {
                if (&this->m_data != &data) {
                    std::memcpy(this->m_data, data, SZ);
                }
                return *this;
            }

            template < uint16_t OTHER_SZ >
            stack_buffer& operator=(const T (&data)[OTHER_SZ])
            {
                if ((OTHER_SZ == 0) || (OTHER_SZ > SZ)) {
                    OMNI_ERR_FW(OMNI_INDEX_OOR_STR, omni::exceptions::index_out_of_range())
                }
                std::memset(this->m_data, 0, SZ);
                std::memcpy(this->m_data, data, OTHER_SZ);
                return *this;
            }

            bool operator==(const stack_buffer& other) const
            {
                if (this != &other) {
                    return (std::memcmp(this->m_data, other.m_data, SZ) == 0);
                }
                return true;
            }

            bool operator==(const T (&data)[SZ]) const
            {
                return (std::memcmp(this->m_data, data, SZ) == 0);
            }

            inline bool operator!=(const stack_buffer& other) const
            {
                return !(*this == other);
            }

            inline bool operator!=(const T (&data)[SZ]) const
            {
                return !(*this == data);
            }

            bool operator<(const stack_buffer& other) const
            {
                if (this == &other) { return false; }
                for (uint16_t i = 0; i < SZ; ++i) {
                    if (this->m_data[i] >= other.m_data[i]) {
                        return false;
                    }
                }
                return true;
            }

            bool operator<(const T (&data)[SZ]) const
            {
                if (&this->m_data != &data) { return false; }
                for (uint16_t i = 0; i < SZ; ++i) {
                    if (this->m_data[i] >= data[i]) {
                        return false;
                    }
                }
                return true;
            }

            bool operator>(const stack_buffer& other) const
            {
                if (this == &other) { return false; }
                for (uint16_t i = 0; i < SZ; ++i) {
                    if (this->m_data[i] <= other.m_data[i]) {
                        return false;
                    }
                }
                return true;
            }

            bool operator>(const T (&data)[SZ]) const
            {
                if (&this->m_data != &data) { return false; }
                for (uint16_t i = 0; i < SZ; ++i) {
                    if (this->m_data[i] <= data[i]) {
                        return false;
                    }
                }
                return true;
            }

            bool operator<=(const stack_buffer& other) const
            {
                if (this == &other) { return true; }
                for (uint16_t i = 0; i < SZ; ++i) {
                    if (this->m_data[i] > other.m_data[i]) {
                        return false;
                    }
                }
                return true;
            }

            bool operator<=(const T (&data)[SZ]) const
            {
                if (&this->m_data != &data) { return true; }
                for (uint16_t i = 0; i < SZ; ++i) {
                    if (this->m_data[i] > data[i]) {
                        return false;
                    }
                }
                return true;
            }

            bool operator>=(const stack_buffer& other) const
            {
                if (this == &other) { return true; }
                for (uint16_t i = 0; i < SZ; ++i) {
                    if (this->m_data[i] < other.m_data[i]) {
                        return false;
                    }
                }
                return true;
            }

            bool operator>=(const T (&data)[SZ]) const
            {
                if (&this->m_data != &data) { return true; }
                for (uint16_t i = 0; i < SZ; ++i) {
                    if (this->m_data[i] < data[i]) {
                        return false;
                    }
                }
                return true;
            }

            operator std::string() const
            {
                return this->to_string();
            }

            operator std::wstring() const
            {
                return this->to_wstring();
            }

            template < template < class, class > class std_seq_t, typename std_allocator_t >
            operator std_seq_t < T, std_allocator_t >() const
            {
                return std_seq_t < T, std_allocator_t >(this->begin(), this->end());
            }

            template < template < class, class > class std_seq_t >
            operator std_seq_t < T, std::allocator<T> >() const
            {
                return std_seq_t < T, std::allocator<T> >(this->begin(), this->end());
            }

            T operator[](std::size_t index) const
            {
                return this->m_data[index];
            }

            T& operator[](std::size_t index)
            {
                return this->m_data[index];
            }

            operator const T *const() const
            {
                return this->m_data;
            }

            operator T *const()
            {
                return this->m_data;
            }

            OMNI_MEMBERS_FW(omni::stack_buffer<T, SZ>) // disposing,name,type(),hash()

            OMNI_OSTREAM_FW(omni::stack_buffer<T, SZ>)

            static uint32_t max_size()
            {
                return std::numeric_limits<uint16_t>::max();
            }

        private:
            T m_data[SZ];
    };
}

namespace std {
    template < typename T, uint16_t SZ >
    inline void swap(omni::stack_buffer<T, SZ>& o1, omni::stack_buffer<T, SZ>& o2)
    {
        o1.swap(o2);
    }

    template < typename T, uint16_t SZ >
    inline void swap(omni::stack_buffer<T, SZ>& o1, T (&data)[SZ])
    {
        o1.swap(data);
    }

    template < typename T, uint16_t SZ >
    inline void swap(T (&data)[SZ], omni::stack_buffer<T, SZ>& o1)
    {
        o1.swap(data);
    }
}

#endif // OMNI_STACK_BUFFER_HPP
