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
#if !defined(OMNI_SPAN_HPP)
#define OMNI_SPAN_HPP 1
#include <ctime>
#include <omni/defs/class_macros.hpp>
#include <omni/types/tick_t.hpp>
#include <omni/ostream.hpp>

namespace omni {
    namespace chrono {        
        /** Undocumented: not finished */
        class span
        {
            public:
                span();
                span(const omni::chrono::span& cp);
                virtual ~span();
                const omni::string_t to_string_t() const;
                omni::chrono::span& operator=(const omni::chrono::span& ap);
                bool operator==(const omni::chrono::span& o) const;
                bool operator!=(const omni::chrono::span& o) const;
                
                OMNI_MEMBERS_FW(omni::chrono::span) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_STR_FW(omni::chrono::span)
                //OMNI_OSTREAM_FW(omni::chrono::span)
                
            private:
                #if defined(OMNI_TYPE_INFO)
                    omni::type<omni::chrono::span> m_type;
                #endif
        };
    } // namespace chrono
} // namespace omni

#endif // OMNI_SPAN_HPP
