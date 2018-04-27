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
#if !defined(OMNI_TIME_HPP)
#define OMNI_TIME_HPP 1
#include <ctime>
#include <omni/defs/class_macros.hpp>
#include <omni/types/tick_t.hpp>
#include <omni/ostream.hpp>

namespace omni {
    namespace chrono {
        /** Undocumented: not finished */
        class time
        {
            public:
                time();
                time(const omni::chrono::time& cp);
                virtual ~time();
                const omni::string_t to_string_t() const;
                omni::chrono::time& operator=(const omni::chrono::time& ap);
                bool operator==(const omni::chrono::time& o) const;
                bool operator!=(const omni::chrono::time& o) const;
                
                // TODO: implement, verify and document
                /*operator std::string() const;
                operator std::wstring() const;*/
                
                OMNI_MEMBERS_FW(omni::chrono::time) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_STR_FW(omni::chrono::time)
                //OMNI_OSTREAM_FW(omni::chrono::time)
                
            //private:
        };
        omni::chrono::time now();
    } // namespace chrono
} // namespace omni

#endif // OMNI_TIME_HPP
