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
#if !defined(OMNI_CONSTANTS_HPP)
#define OMNI_CONSTANTS_HPP
#include <omni/defs/global.hpp>

#include <omni/consts/cconsts.hpp>
#include <omni/consts/wconsts.hpp>

#if !defined(OMNI_NO_CONSTS)

#if defined(OMNI_UNICODE)
    #define OMNI_CONSTS_NS_FW omni::wconsts
#else
    #define OMNI_CONSTS_NS_FW omni::cconsts
#endif

namespace omni {
    namespace consts {
        namespace err = OMNI_CONSTS_NS_FW::err;
        namespace misc = OMNI_CONSTS_NS_FW::misc;
        namespace size {
            namespace binary {
                namespace string = OMNI_CONSTS_NS_FW::size::binary::string;
                OMNI_CONSTEXT_FW const uint64_t KB OMNI_EXT_ASSN_FW(OMNI_KIB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t MB OMNI_EXT_ASSN_FW(OMNI_MIB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t GB OMNI_EXT_ASSN_FW(OMNI_GIB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t TB OMNI_EXT_ASSN_FW(OMNI_TIB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t PB OMNI_EXT_ASSN_FW(OMNI_PIB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t EB OMNI_EXT_ASSN_FW(OMNI_EIB_IVAL);
            }
            namespace decimal {
                namespace string = OMNI_CONSTS_NS_FW::size::decimal::string;
                OMNI_CONSTEXT_FW const uint64_t KB OMNI_EXT_ASSN_FW(OMNI_KB_IVAL); 
                OMNI_CONSTEXT_FW const uint64_t MB OMNI_EXT_ASSN_FW(OMNI_MB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t GB OMNI_EXT_ASSN_FW(OMNI_GB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t TB OMNI_EXT_ASSN_FW(OMNI_TB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t PB OMNI_EXT_ASSN_FW(OMNI_PB_IVAL);
                OMNI_CONSTEXT_FW const uint64_t EB OMNI_EXT_ASSN_FW(OMNI_EB_IVAL);
            }
        }
    }
}

#undef OMNI_CONSTS_NS_FW

#endif

#endif // OMNI_CONSTANTS_HPP
