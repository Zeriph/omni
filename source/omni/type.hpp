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
#if !defined(OMNI_TYPE_HPP)
#define OMNI_TYPE_HPP 1
#include <omni/defs/global.hpp>

#define omni_typeid(T) omni::type_id<T>()

namespace omni {
    template < typename T >
    uint64_t type_id()
    {
        static char tid;
        return reinterpret_cast<uint64_t>(&tid);
    }
    
    template < typename T >
    inline uint64_t type_id(const T& t)
    {
        OMNI_UNUSED(t);
        return omni::type_id<T>();
    }
    
    template < typename T >
    inline uint64_t type_id(const T *const t)
    {
        OMNI_UNUSED(t);
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
        OMNI_UNUSED(c);
        return omni::type_of<T, C>();
    }
    
    template < typename T, typename C >
    inline bool type_of(const C *const c)
    {
        OMNI_UNUSED(c);
        return omni::type_of<T, C>();
    }
    
    template < typename T, typename C >
    inline bool type_of(const T& t, const C& c)
    {
        OMNI_UNUSED(t);
        OMNI_UNUSED(c);
        return omni::type_of<T, C>();
    }
    
    template < typename T, typename C >
    inline bool type_of(const T *const t, const C *const c)
    {
        OMNI_UNUSED(t);
        OMNI_UNUSED(c);
        return omni::type_of<T, C>();
    }
}

#endif // OMNI_TYPE_HPP
