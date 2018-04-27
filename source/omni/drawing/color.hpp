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
#if !defined(OMNI_COLOR_HPP)
#define OMNI_COLOR_HPP 1
#include <omni/defs/global.hpp>

namespace omni {
    namespace drawing {
        // https://msdn.microsoft.com/en-us/library/system.drawing.color(v=vs.110).aspx
        class color {
            public:
                // TODO: finish the color enum class

                /*friend std::ostream& operator<<(std::ostream& s, const color& c)
                { s << to_string(c.m_val); return s; }
                friend std::wostream& operator<<(std::wostream& s, const color& c)
                { s << to_wstring(c.m_val); return s; }

                color() :
                    OMNI_CTOR_FW(omni::drawing::color)
                    m_val(static_cast<enum_t>(0))
                { }

                color(const color& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                color(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::color)
                    m_val(val)
                { }

                ~color()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                const std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                const std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const color& val) const
                {
                    return !(*this == val);
                }
                
                color& operator=(const color& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                bool operator<(const color& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator>(const color& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator==(const color& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(const enum_t& val) const
                {
                    return this->m_val == val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }*/

                OMNI_MEMBERS_FW(omni::drawing::color) // disposing,name,type(),hash()

            private:
                unsigned char m_r; // red
                unsigned char m_g; // green
                unsigned char m_b; // blue
                unsigned char m_a; // alpha

                // TODO: m_name??
        };
    }
}

#endif // OMNI_COLOR_HPP
