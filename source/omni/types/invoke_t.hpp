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
#if !defined(OMNI_INVOKE_T_HPP)
#define OMNI_INVOKE_T_HPP 1

// DEV_NOTE: this enum does not follow the rest of the enum types since this is specifically for delegates

namespace omni {
    /** Defines the values for the invocation type a delegate object will have */
    typedef struct invoke_type {
        /** The underlying enum type for the invocation types */
        typedef enum enum_t {
            /** No methods have been assigned for invocation */
            NONE = 0,
            /** A non-member function or static function has been assigned for invocation */
            ANONYMOUS = 1,
            /** A member function of a class or struct has been assigned for invocation */
            MEMBER_FUNC = 2
        } enum_t;
    } invoke_type;
    
    typedef omni::invoke_type::enum_t invoke_t;
} // namespace omni

#endif // OMNI_INVOKE_T_HPP
