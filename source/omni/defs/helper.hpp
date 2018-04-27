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

#define OMNI_DEF2STR_FW(x) #x
#define OMNI_DEF2STR(x) OMNI_DEF2STR_FW(x)

#define OMNI_DEFCONCAT_FW(A, B) A ## B
#define OMNI_DEFCONCAT(A, B) OMNI_DEFCONCAT_FW(A, B)

#define OMNI_BOOL2STR(bval) (bval ? "true" : "false")
#define OMNI_BOOL2WSTR(bval) (bval ? L"true" : L"false")
#define OMNI_B2S(bval) OMNI_BOOL2STR(bval)
#define OMNI_B2WS(bval) OMNI_BOOL2WSTR(bval)

#define OMNI_UNUSED(val) (static_cast<void>(val))

#if !defined(OMNI_WSTR)
    #define OMNI_WSTR(v) L##v
    #define OMNI_DWSTR(v) L#v
#endif

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

#define OMNI_E2S_FW(v) case v: return OMNI_DEF2STR(v)
#define OMNI_E2WS_FW(v) case v: return omni::string::util::to_wstring(OMNI_DEF2STR(v))

#define OMNI_MAX_PATH_FW 32767 // 32,767 - 1 for '\0'

// TODO: can this be brought into the framework anywhere that won't sacrifice comprehension?
/*
#define SW1(a) swtich (v) { OMNI_E2S_FW(a); default: break; }
#define SW2(a,b) swtich (v) { OMNI_E2S_FW(a); default: break; }
#define SW3(a,b,c) swtich (v) { OMNI_E2S_FW(a); default: break; }
#define SW4(a,b,c,d) swtich (v) { OMNI_E2S_FW(a); default: break; }
#define SW5(a,b,c,d,e) swtich (v) { OMNI_E2S_FW(a); default: break; }
#define SW6(a,b,c,d,e,f) swtich (v) { OMNI_E2S_FW(a); default: break; }
#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,NAME,...) NAME
#define SW_DEF(...) GET_MACRO(__VA_ARGS__, SW11, SW10, SW9, SW8, SW7, SW6, SW5, SW4, SW3, SW2, SW1)(__VA_ARGS__)
#define ENUM_DEF(NM, ...) typedef struct NM { \
                            typedef enum enum_t { __VA_ARGS__ } enum_t; \
                            static const std::string to_string(const enum_t& v) { \
                                SW_DEF(__VA_ARGS__) \
                                return "UNKNOWN"; \
                            } \
                            friend std::ostream& operator<<(std::ostream& s, const enum_t& c) \
                            { s << to_string(c); return s; } \
                          } NM
*/

#endif // OMNI_HELPER_HPP
