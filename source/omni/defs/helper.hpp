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
#if !defined(OMNI_HELPER_HPP)
#define OMNI_HELPER_HPP 1

// macro helper functions

// string-izes a macro: e.g. OMNI_DEF2STR(X) prints "X"
#define OMNI_DEF2STR_FW(x) #x
#define OMNI_DEF2STR(x) OMNI_DEF2STR_FW(x)

#define OMNI_DEFCONCAT_FW(A, B) A ## B
#define OMNI_DEFCONCAT(A, B) OMNI_DEFCONCAT_FW(A, B)

#define OMNI_BOOL2STR(bval) (bval ? "true" : "false")
#define OMNI_BOOL2WSTR(bval) (bval ? L"true" : L"false")
#define OMNI_B2S(bval) OMNI_BOOL2STR(bval)
#define OMNI_B2WS(bval) OMNI_BOOL2WSTR(bval)

#define OMNI_UNUSED(val) (static_cast<void>(val))

#define OMNI_WSTR(v) L ## v
#define OMNI_DWSTR(v) L # v

#if !defined(OMNI_DATE) && defined(__DATE__)
    #undef OMNI_DATE
    #define OMNI_DATE __DATE__
#endif
#if !defined(OMNI_TIME) && defined(__TIME__)
    #undef OMNI_TIME
    #define OMNI_TIME __TIME__
#endif

#if !defined(OMNI_DATE)
    #define OMNI_DATE Jan 1 1970
#endif
#if !defined(OMNI_TIME)
    #define OMNI_TIME 00:00:00
#endif

#define OMNI_BIND_EX(DelegateType, Class, Function, Obj) DelegateType::bind<Class, &Class::Function>(obj)
#define OMNI_BIND_CONST_EX(DelegateType, Class, Function, Obj) DelegateType::bind_const<Class, &Class::Function>(obj)

#define OMNI_S2E_FW(v) if (val == OMNI_DEF2STR(v)) { out = v; return true; }
#define OMNI_E2SS_FW(v) case v: ss << OMNI_DEF2STR(v); break

#define OMNI_MAX_PATH_FW 32767 // 32,767 - 1 for '\0'

// #define OMNI_E2S_FW(v) case v: return OMNI_DEF2STR(v)
// #define OMNI_E2WS_FW(v) case v: return OMNI_WSTR(v)

#endif // OMNI_HELPER_HPP
