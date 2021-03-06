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
#if !defined(OMNI_RUNNABLE_T_HPP)
#define OMNI_RUNNABLE_T_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/thread_t.hpp>
#include <omni/chrono/span.hpp>

namespace omni {
    namespace sync {
        class runnable
        {
            public:
                runnable()
                    OMNI_OCTOR_FW(omni::sync::runnable)
                {}
                
                runnable(const omni::sync::runnable& cp)
                    OMNI_OCPCTOR_FW(cp)
                {
                    #if !defined(OMNI_OBJ_CTV1_FW)
                        OMNI_UNUSED(cp);
                    #endif
                }
                
                omni::sync::runnable& operator=(omni::sync::runnable& o)
                {
                    #if !defined(OMNI_DISPOSE_EVENT) && !defined(OMNI_OBJECT_NAME)
                        OMNI_UNUSED(o);
                    #else
                        OMNI_ASSIGN_FW(o)
                    #endif
                    return *this;
                }
                
                virtual ~runnable() OMNI_DTOR_THROWS
                {
                    OMNI_DTOR_FW
                }
                
                virtual void run(omni::sync::thread_arg_t parm) = 0;
                
                virtual bool operator==(const omni::sync::runnable& o)
                {
                    return (this == &o)
                           OMNI_EQUAL_FW(o);
                }
                
                virtual bool operator!=(const omni::sync::runnable& o)
                {
                    return !(*this == o);
                }
                
                OMNI_MEMBERS_FW(omni::sync::runnable) // disposing,name,type(),hash()
        };
    }
} // namespace omni

#endif // OMNI_RUNNABLE_T_HPP
