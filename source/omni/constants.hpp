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
                const unsigned int KB = OMNI_KIB_IVAL;
                const unsigned int MB = OMNI_MIB_IVAL;
                const unsigned int GB = OMNI_GIB_IVAL;
            }
            namespace decimal {
                namespace string = OMNI_CONSTS_NS_FW::size::decimal::string;
                const unsigned int KB = OMNI_KB_IVAL; 
                const unsigned int MB = OMNI_MB_IVAL;
                const unsigned int GB = OMNI_GB_IVAL;
            }
        }
    }
}

#undef OMNI_CONSTS_NS_FW

#endif // OMNI_CONSTANTS_HPP
