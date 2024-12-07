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
#if !defined(OMNI_CONVERT_HPP)
#define OMNI_CONVERT_HPP 1
#include <omni/crypto/base64.hpp>

namespace omni {
    /*
        This namespace is really only here as an homage to porting C# to Omni.
        Most of what the System.Convert class does in C#, C++ can do with a cast,
        either static_cast, reinterpret_cast, or dynamic_cast (if you're feeling
        frisky). To that, there's also a `to_t` helper function in omni/helper.hpp
        that's a shortened version of static_cast. Additionally, you can use the
        omni::chrono::date_time class to do  conversions to/from that. There's
        also the omni::crypto::base64 namespace with encode/decode functions available.
        
        This namespace is purely for posterity.
    */
    namespace convert {
        namespace base64 = omni::crypto::base64;
    }
}

#endif // OMNI_CONVERT_HPP
