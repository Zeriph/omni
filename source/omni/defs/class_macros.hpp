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
#if !defined(OMNI_CLASSDEFS_HPP)
#define OMNI_CLASSDEFS_HPP 1
#include <omni/defs/global.hpp>
#include <omni/types/ostream_t.hpp>

#define OMNI_OSTREAM_FW(cls) OMNI_OSTREAM_OPERATOR(cls, to_string()) \
                             OMNI_WOSTREAM_OPERATOR(cls, to_wstring())

#define OMNI_OSTREAM_STR_FW(cls) OMNI_FOSTREAM_OPC2T_FW(cls, to_string_t()) \
                                 OMNI_FOSTREAM_OPW2T_FW(cls, to_string_t())
                                 
#if defined(OMNI_OBJ_CTV1_FW)
    #undef OMNI_OBJ_CTV1_FW
#endif
#if defined(OMNI_OBJ_CTV2_FW)
    #undef OMNI_OBJ_CTV2_FW
    #undef OMNI_OBJ_CCTV2_FW
    #undef OMNI_OBJ_ETV2_FW
#endif
#if defined(OMNI_OBJ_CTV3_FW)
    #undef OMNI_OBJ_CTV3_FW
    #undef OMNI_OBJ_CCTV3_FW
    #undef OMNI_OBJ_ETV3_FW
#endif
#if defined(OMNI_OBJ_CTV4_FW)
    #undef OMNI_OBJ_CTV4_FW
    #undef OMNI_OBJ_CCTV4_FW
    #undef OMNI_OBJ_ETV4_FW
#endif

#if defined(OMNI_DISPOSE_EVENT)
    #include <omni/delegate/1.hpp>
    /* DEV_NOTE: if defined, the disposing event is the first call on destruction, so an object's
    state is still valid before being disposed of */
    #define OMNI_MDE_DTOR_FW if (this->disposing) { this->disposing(*this); }
    #define OMNI_MDE_MBRT_FW(T) omni::event1<void, const T& > disposing;
    #define OMNI_MDE_CTOR_FW  disposing()
    #define OMNI_MDE_CP_FW(cp) disposing(cp.disposing)
    #define OMNI_MDE_SETCP_FW(val) this->disposing = val.disposing;
    #define OMNI_MDE_EQU_FW(val) (this->disposing == val.disposing)
    
    #define OMNI_OBJ_CTV1_FW
    #define OMNI_OBJ_CTV2_FW OMNI_MDE_CTOR_FW
    #define OMNI_OBJ_CCTV2_FW(cp) OMNI_MDE_CP_FW(cp)
    #define OMNI_OBJ_ETV2_FW(val) OMNI_MDE_EQU_FW(val)
#else
    #define OMNI_MDE_DTOR_FW 
    #define OMNI_MDE_MBRT_FW(T)
    #define OMNI_MDE_CTOR_FW
    #define OMNI_MDE_CP_FW(cp)
    #define OMNI_MDE_SETCP_FW(val)
    #define OMNI_MDE_EQU_FW(val)    
#endif

#if defined(OMNI_OBJECT_NAME)
    //#include <string>
    //#define OMNI_MNM_MBRT_FW std::string name;
    #include <omni/types/string_t.hpp>
    // A property that allows you to assign a name to this object
    #define OMNI_MNM_MBRT_FW omni::string_t name;
    #define OMNI_MNM_CTOR_FW(val)  name(OMNI_STRW(OMNI_DEF2STR(val)))
    #define OMNI_MNM_CP_FW(cp) name(cp.name)
    #define OMNI_MNM_SETCP_FW(val) this->name = val.name;
    #define OMNI_MNM_EQU_FW(val) (this->name == val.name)
    
    #if !defined(OMNI_OBJ_CTV1_FW)
        #define OMNI_OBJ_CTV1_FW
        #define OMNI_OBJ_CTV3_FW(cls) OMNI_MNM_CTOR_FW(cls)
        #define OMNI_OBJ_CCTV3_FW(cp) OMNI_MNM_CP_FW(cp)
        #define OMNI_OBJ_ETV3_FW(val) OMNI_MNM_EQU_FW(val)
    #else
        #define OMNI_OBJ_CTV3_FW(cls) , OMNI_MNM_CTOR_FW(cls)
        #define OMNI_OBJ_CCTV3_FW(cp) , OMNI_MNM_CP_FW(cp)
        #define OMNI_OBJ_ETV3_FW(val) && OMNI_MNM_EQU_FW(val)
    #endif
#else
    #define OMNI_MNM_MBRT_FW
    #define OMNI_MNM_CTOR_FW(val)
    #define OMNI_MNM_CP_FW(cp)
    #define OMNI_MNM_SETCP_FW(val)
    #define OMNI_MNM_EQU_FW(val)
#endif

#if defined(OMNI_TYPE_INFO)
    #include <omni/type.hpp>
    #define OMNI_MTI_MBRT_FW(cls) const omni::type<cls>& type() const { return this->m_type; } \
            std::size_t hash() const { return this->m_type.hash(); }
    #define OMNI_MTI_CTOR_FW   m_type()
    #define OMNI_MTI_SETCP_FW(val)  //this->m_type = val.m_type;
    #define OMNI_MTI_EQU_FW(val)    (this->m_type == val.m_type)
    
    #if !defined(OMNI_OBJ_CTV1_FW)
        #define OMNI_OBJ_CTV1_FW
        #define OMNI_OBJ_CTV4_FW OMNI_MTI_CTOR_FW
        #define OMNI_OBJ_CCTV4_FW OMNI_MTI_CTOR_FW
        #define OMNI_OBJ_ETV4_FW(val) OMNI_MTI_EQU_FW(val)
    #else
        #define OMNI_OBJ_CTV4_FW , OMNI_MTI_CTOR_FW
        #define OMNI_OBJ_CCTV4_FW , OMNI_MTI_CTOR_FW
        #define OMNI_OBJ_ETV4_FW(val) && OMNI_MTI_EQU_FW(val)
    #endif
#else
    #define OMNI_MTI_MBRT_FW(cls)
    #define OMNI_MTI_CTOR_FW(cls)
    #define OMNI_MTI_SETCP_FW(val)
    #define OMNI_MTI_EQU_FW(val)
#endif

#if defined(OMNI_OBJ_CTV1_FW)
    #if !defined(OMNI_OBJ_CTV2_FW)
        #define OMNI_OBJ_CTV2_FW
        #define OMNI_OBJ_CCTV2_FW(cp)
        #define OMNI_OBJ_ETV2_FW(val)
    #endif
    #if !defined(OMNI_OBJ_CTV3_FW)
        #define OMNI_OBJ_CTV3_FW(cls)
        #define OMNI_OBJ_CCTV3_FW(cp)
        #define OMNI_OBJ_ETV3_FW(val)
    #endif
    #if !defined(OMNI_OBJ_CTV4_FW)
        #define OMNI_OBJ_CTV4_FW
        #define OMNI_OBJ_CCTV4_FW
        #define OMNI_OBJ_ETV4_FW(val)
    #endif
    #define OMNI_CTOR_FW(cls) OMNI_OBJ_CTV2_FW OMNI_OBJ_CTV3_FW(cls) OMNI_OBJ_CTV4_FW ,
    #define OMNI_OCTOR_FW(cls) : OMNI_OBJ_CTV2_FW OMNI_OBJ_CTV3_FW(cls) OMNI_OBJ_CTV4_FW
    #define OMNI_CPCTOR_FW(cp) OMNI_OBJ_CCTV2_FW(cp) OMNI_OBJ_CCTV3_FW(cp) OMNI_OBJ_CCTV4_FW ,
    #define OMNI_OCPCTOR_FW(cp) : OMNI_OBJ_CCTV2_FW(cp) OMNI_OBJ_CCTV3_FW(cp) OMNI_OBJ_CCTV4_FW
    #define OMNI_EQUAL_FW(val) && OMNI_OBJ_ETV2_FW(val) OMNI_OBJ_ETV3_FW(val) OMNI_OBJ_ETV4_FW(val)
#else
    #define OMNI_CTOR_FW(cls)
    #define OMNI_OCTOR_FW(cls)
    #define OMNI_CPCTOR_FW(cp)
    #define OMNI_OCPCTOR_FW(cp)
    #define OMNI_EQUAL_FW(val)
#endif

#define OMNI_MEMBERS_FW(T) OMNI_MTI_MBRT_FW(T) OMNI_MDE_MBRT_FW(T) OMNI_MNM_MBRT_FW 
#define OMNI_DTOR_FW OMNI_MDE_DTOR_FW
#define OMNI_ASSIGN_FW(T) OMNI_MTI_SETCP_FW(T) OMNI_MDE_SETCP_FW(T) OMNI_MNM_SETCP_FW(T)

/*
DEV_NOTE: we can't undef these since these def's are referenced in other def's that get called
after this header; since we're wrapping def's instead of types, we need these def's to be
left alone, otherwise we'll get errors (or logic errors).
#undef OMNI_OBJ_CTV1_FW
#undef OMNI_OBJ_CTV2_FW
#undef OMNI_OBJ_CCTV2_FW
#undef OMNI_OBJ_CTV3_FW
#undef OMNI_OBJ_CCTV3_FW
#undef OMNI_OBJ_CTV4_FW
#undef OMNI_OBJ_CCTV4_FW
*/

#endif // OMNI_CLASSDEFS_HPP
