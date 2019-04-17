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
#if !defined(OMNI_DEBUG_HPP)
#define OMNI_DEBUG_HPP 1
#include <iostream>

#define omnidbg(msg)
#define omnidbgval(msg, val)
#define OMNI_D1_FW(msg)
#define OMNI_D2_FW(msg)
#define OMNI_D3_FW(msg)
#define OMNI_D4_FW(msg)
#define OMNI_D5_FW(msg)
#define OMNI_DV1_FW(msg, val)
#define OMNI_DV2_FW(msg, val)
#define OMNI_DV3_FW(msg, val)
#define OMNI_DV4_FW(msg, val)
#define OMNI_DV5_FW(msg, val)

#define OMNI_DBGE(msg)
#define OMNI_DBGEV(msg, val)

#define OMNI_PRINTL(msg) std::cout << msg << std::endl
#define OMNI_PRINT(msg) std::cout << msg
#define OMNI_WPRINTL(msg) std::wcout << msg << std::endl
#define OMNI_WPRINT(msg) std::wcout << msg

#if defined(OMNI_SHOW_DEBUG) || defined(OMNI_SHOW_DEBUG_ERR)
    #if !defined(OMNI_SHOW_DEBUG_ERR)
        #define OMNI_SHOW_DEBUG_ERR
    #endif
    #undef OMNI_DBGE
    #undef OMNI_DBGEV
    
    #define OMNI_DFL_FW
    #define OMNI_DFN_FW
    #define OMNI_DLN_FW
    #if defined(OMNI_SHOW_DEBUG_FILE) || defined(OMNI_SHOW_DEBUG_FUNC) || defined(OMNI_SHOW_DEBUG_LINE)
        #if defined(OMNI_SHOW_DEBUG_FILE)
            #undef OMNI_DFL_FW
            #define OMNI_DFL_FW << __FILE__
        #endif
        #if defined(OMNI_SHOW_DEBUG_FUNC)
            #undef OMNI_DFN_FW
            #define OMNI_DFN_FW << "::" << __FUNCTION__
        #endif
        #if defined(OMNI_SHOW_DEBUG_LINE)
            #undef OMNI_DLN_FW
            #define OMNI_DLN_FW << "(" << __LINE__ << ")"
        #endif
    #endif
    
    #if defined(OMNI_UNICODE)
        #define OMNI_DCER_FW std::wcerr
        #define OMNI_DCLG_FW std::wclog
        #define OMNI_DCT_FW std::wcout
    #else
        #define OMNI_DCER_FW std::cerr
        #define OMNI_DCLG_FW std::clog
        #define OMNI_DCT_FW std::cout
    #endif
    
    #define OMNI_DFMT_FW OMNI_DCER_FW OMNI_DFL_FW OMNI_DFN_FW OMNI_DLN_FW << "ERR_OMNI# "
    #define OMNI_DBGE_FW(msg) OMNI_DFMT_FW << msg << std::endl
    #define OMNI_DBGEV_FW(msg, val) OMNI_DFMT_FW << msg << val << std::endl
    #define OMNI_DBGE(msg) OMNI_DBGE_FW(msg);
    #define OMNI_DBGEV(msg, val) OMNI_DBGEV_FW(msg, val);
    
    #if defined(OMNI_SHOW_DEBUG)
        #undef omnidbg
        #undef omnidbgval
        #undef OMNI_D1_FW
        #undef OMNI_DV1_FW
        
        #define OMNI_DEBUG
        #define OMNI_DBG_L1
        
        #define OMNI_DOUTFMT_FW OMNI_DCT_FW OMNI_DFL_FW OMNI_DFN_FW OMNI_DLN_FW << "omni_dbg# "
        #define omnidbg(msg) OMNI_DOUTFMT_FW << msg << std::endl
        #define omnidbgval(msg, val) OMNI_DOUTFMT_FW << msg << val << std::endl
        
        #define OMNI_D1_FW(msg) omnidbg(msg)
        #define OMNI_DV1_FW(msg, val) omnidbgval(msg, val)
        #define OMNI_DSW_FW(v) case v: omnidbg(#v); break
    
        #if OMNI_SHOW_DEBUG > 1
            #define OMNI_DBG_L2
            #undef OMNI_D2_FW
            #undef OMNI_DV2_FW
            #define OMNI_D2_FW(msg) omnidbg(msg)
            #define OMNI_DV2_FW(msg, val) omnidbgval(msg, val)
            #if OMNI_SHOW_DEBUG > 2
                #define OMNI_DBG_L3
                #undef OMNI_D3_FW
                #undef OMNI_DV3_FW
                #define OMNI_D3_FW(msg) omnidbg(msg)
                #define OMNI_DV3_FW(msg, val) omnidbgval(msg, val)
                #if OMNI_SHOW_DEBUG > 3
                    #define OMNI_DBG_L4
                    #undef OMNI_D4_FW
                    #undef OMNI_DV4_FW
                    #define OMNI_D4_FW(msg) omnidbg(msg)
                    #define OMNI_DV4_FW(msg, val) omnidbgval(msg, val)
                    #if OMNI_SHOW_DEBUG > 4
                        #define OMNI_DBG_L5
                        #undef OMNI_D5_FW
                        #undef OMNI_DV5_FW
                        #define OMNI_D5_FW(msg) omnidbg(msg)
                        #define OMNI_DV5_FW(msg, val) omnidbgval(msg, val)
                    #endif
                #endif
            #endif
        #endif
    
    #endif // OMNI_SHOW_DEBUG
#endif // OMNI_SHOW_DEBUG || OMNI_SHOW_DEBUG_ERR

#endif // OMNI_DEBUG_HPP
